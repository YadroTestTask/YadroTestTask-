/// \file tape.сpp
/// \author Ашмаров Ефим
/// \date 6.2023
/// \brief Реализация взаимодействий с лентой

#include <tape.hpp>
#include <fstream>
#include <filesystem>
#include <thread>

namespace tape {

tape::tape(const std::string &src_path, const tape_config &cfg, std::size_t init_size)
    : read_delay_(cfg.get_read_delay( ))
    , write_delay_(cfg.get_write_delay( ))
    , move_delay_(cfg.get_move_delay( ))
    , current_pos_(0) {

    // инициализируем файл, если требуется
    if (init_size != 0) {
        auto tmp_f = std::ofstream(src_path, std::ios_base::out | std::ios_base::binary);
        uint8_t fil = 0;
        for (int i = 0; i < init_size * 4; i++) {
            tmp_f.write((char*)&fil, 1);
        }
        tmp_f.close( );
    }
    
    tape_file_ = std::fstream(src_path, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    if (!tape_file_.is_open( )) {
        return;
    }
}

tape::~tape( ) {
    tape_file_.close( );
}

void tape::move_left( ) {
    if (current_pos_ != 0) {
        current_pos_--;
        std::this_thread::sleep_for(move_delay_);
    }
}

void tape::move_right( ) {
    current_pos_++;
    std::this_thread::sleep_for(move_delay_);
}

uint32_t tape::read( ) {
    tape_file_.seekg(current_pos_ * sizeof(uint32_t), std::ios_base::beg);
    uint32_t res;
    tape_file_.read((char*)(&res), sizeof(res));

    std::this_thread::sleep_for(read_delay_);
    return res;
}

void tape::write(uint32_t elem) {
    tape_file_.seekp(current_pos_ * sizeof(uint32_t), std::ios_base::beg);
    tape_file_.write((const char*)(&elem), sizeof(elem));
    tape_file_.flush();

    std::this_thread::sleep_for(write_delay_);
}

std::size_t tape::get_current_pos() const {
    return current_pos_;
}

} // tape
