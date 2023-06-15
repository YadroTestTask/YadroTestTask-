/// \file tape_sorter.сpp
/// \author Ашмаров Ефим
/// \date 6.2023
/// \brief Реализация класса для сортировки ленты

#include <tape_sorter.hpp>
#include <tape.hpp>


namespace tape {

tape_sorter::tape_sorter(const std::string &path_to_tape_config)
    : cfg_(path_to_tape_config)
    , tmp_tape_path_(cfg_.get_tmp_path( ).concat("__tmp_tape_.tape")) {
}

tape_sorter::~tape_sorter( ) {
    if (std::filesystem::exists(tmp_tape_path_)) {
        std::filesystem::remove(tmp_tape_path_);
    }
}

/// \brief Слить 2 ленты в одну. Девижение справа налево.
///
/// \param[out] output - Лента, в которую следует слить выходные.
/// \param[in] in_1 - Первая лента, подлежщая слиянию.
/// \param[in] in1_size - Длинна первой лентыю.
/// \param[in] in_2  - Вторая лента, подлежающая слиянию.
/// \param[in] in2_size - Длинна второй ленты.
static void merge_tape(tape& output, tape& in_1, std::size_t in1_size, tape& in_2, std::size_t in2_size) {
    uint32_t elem1 = 0;
    if (in1_size != 0) {
        elem1 = in_1.read( );
    }

    uint32_t elem2 = 0;
    if (in2_size != 0) {
        elem2 = in_2.read( );
    }
    do {
        if (((elem1 > elem2) && (in1_size != 0)) || (in2_size == 0)) {
            output.write(elem1);
            if (in1_size != 0) {
                in_1.move_left( );
                elem1 = in_1.read( );
                in1_size--;
            }
        } else {
            output.write(elem2);
            if (in2_size != 0) {
                in_2.move_left( );
                elem2 = in_2.read( );
                in2_size--;
            }
        }
        output.move_left( );
    } while ((in1_size != 0) || (in2_size != 0));
    
}

/// \brief Разделить ленту на две. Движение слева направо
///
/// \param[out] acum_out - Лента, на которую будут записаны чётные отсортированные подпоследовательности
/// \param[out] tmp_out - Лента, на которую будут записаны нечётные отсортированные подпослеовательности.
/// \param[in] input - Лента, подлежащая разделению.
/// \param[in] input_size - Размер входной ленты.
///
/// \return true - если в acum_out получился отсортированный массив, иначе - flase.
static bool split_tape(tape& acum_out,
                       size_t& acum_size,
                       tape& tmp_out,
                       std::size_t& tmp_size,
                       tape& input,
                       std::size_t input_size) {
    bool sorted = true;
    uint32_t prev_elem = 0;
    acum_size = 0;
    tmp_size = 0;

    const uint32_t last_idx = input_size - 1; // номер последнего элемента на ленте
    bool write2acum = true; // флаг, указывающий на какую ленту сейчас следует производить запись
    bool first_acum_write = true; // Первый раз пишем в acum_out?
    bool first_tmp_qrite = true; // Первый раз пишум в tmp_out?
    for (std::size_t i = 0; i < input_size; i++) {
        uint32_t current_elem = input.read( );
        if (i != last_idx) {
            input.move_right( );
        }
        
        // если началась новая отсортированная подпоследовательность - меняем ленту
        if (prev_elem > current_elem) {
            write2acum = !write2acum;
            sorted = false;
        }
        tape* cur_tape = write2acum ? &acum_out : &tmp_out; // лента, в которую следует производить запись
        std::size_t* cur_size = write2acum ? &acum_size : &tmp_size;
        bool* first_flg = write2acum ? &first_acum_write : &first_tmp_qrite;

        if (!(*first_flg)) {
            cur_tape->move_right( );
        }
        cur_tape->write(current_elem);
        (*cur_size)++;
        *first_flg = false;


        prev_elem = current_elem;
    }
    return sorted;
}

int tape_sorter::sort(const std::string &input_fname, const std::string &output_fname) {
    if (!std::filesystem::exists(input_fname)) {
        return -1;
    }
    if (!std::filesystem::is_regular_file(input_fname)) {
        return -2;
    }

    tape input(input_fname, cfg_);
    auto tape_len = std::filesystem::file_size(input_fname) / sizeof(uint32_t);

    tape output(output_fname, cfg_, tape_len);
    size_t out_tape_size = 0;

    tape tmp_tape(tmp_tape_path_, cfg_, tape_len);
    size_t tmp_tape_size = 0;

    while (true) {
        bool sorted = split_tape(output, out_tape_size, tmp_tape, tmp_tape_size, input, tape_len);
        if (sorted) {
            break;
        }
        merge_tape(input, output, out_tape_size, tmp_tape, tmp_tape_size);
    }
    
    return 0;
}


} // tape_sorter