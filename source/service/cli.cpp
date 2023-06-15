/// \file cli.сpp
/// \author Ашмаров Ефим
/// \date 6.2023
/// \brief Реализация консольного интерфейса 

#include <filesystem>
#include <iostream>

#include <getopt.h>

#include <tape_sorter.hpp>


/// \struct consol_option
/// \brief Стуктура, содержащая обработанные аргументы командной строки
typedef struct {
    std::filesystem::path src_path; ///< Путь к ленте, подлежащей сортировке. Обязательный аргумент
    std::filesystem::path res_path; ///< Путь к ленте, куда следует записать результат.
    std::filesystem::path cfg_path; ///< Путь к конфигурационному файлу. Необязательный аргумент. По умолчанию - "".
} consol_option;

/// \brief Обработать аргументы командной строки
///
/// \param[out] options - Обработанные аргементы командой строки.
/// \param[in] argc - Количество аргемнтов командой строки.
/// \param[in] argv - Аргументы командной строки
///
/// \return Код ошибки или 0 в случае успеха.
int parse_options(consol_option& options, int argc, char* argv[]) {
    const std::string usg_msg = std::string("Usage: ") + argv[0] + " <src_file> <res_file> -c <cfg_path=/tmp/>";
    if (argc < 3) {
        std::cout << "Too few arguments. " << usg_msg << std::endl;
        return -1;
    }

    options.src_path = argv[1];
    if (!std::filesystem::exists(options.src_path)) {
        std::cout << "Source file \"" << options.src_path << "\" don't exist. " << usg_msg << std::endl;
        return -2;
    } else if (!std::filesystem::is_regular_file(options.src_path)) {
        std::cout << "Wrong source file \"" << options.src_path << "\" is not regular file" << std::endl;
        return -3;
    }

    options.res_path = argv[2];

    options.cfg_path = "";
    int res;
    while ((res = getopt(argc, argv, "c:")) != -1) {
        switch (res) {
            case 'c':
                options.cfg_path = optarg;
                break;
        }
    }

    if (options.cfg_path != "") {
        if (!std::filesystem::exists(options.cfg_path)) {
            std::cout << "Config file \"" << options.cfg_path << "\" don't exist. " << usg_msg << std::endl;
            return -4;
        } else if (!std::filesystem::is_regular_file(options.cfg_path)) {
            std::cout << "Wrong config file \"" << options.cfg_path << "\" is not regular file" << std::endl;
            return -3;
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    consol_option opt;
    int ok = parse_options(opt, argc, argv);
    if (ok != 0) {
        return -1;
    }

    std::cout << "Sort \"" << opt.src_path << "\" "
              << "to \"" << opt.res_path << "\""
              << std::endl;
    auto ts = tape::tape_sorter(opt.cfg_path);
    ts.sort(opt.src_path, opt.src_path);
    std::cout << "Done; Result in \"" << opt.res_path << "\"" << std::endl;
}