/// \file tape_config.cpp
/// \author Ашмаров Ефим
/// \date 06.2023
/// \brief Реализация класса для чтения конфигурационного файла ленты

#include <fstream>

#include <nlohmann/json.hpp>

#include <tape_config.hpp>

namespace tape {

using json = nlohmann::json;

tape_config::tape_config() 
    : move_delay_(std::chrono::milliseconds(0))
    , read_delay_(std::chrono::milliseconds(0))
    , write_delay_(std::chrono::milliseconds(0))
    , tmp_path_("/tmp/") {
}

tape_config::tape_config(const std::string &config_path)
    : move_delay_(std::chrono::milliseconds(0))
    , read_delay_(std::chrono::milliseconds(0))
    , write_delay_(std::chrono::milliseconds(0))
    , tmp_path_("/tmp/") {
    
    if (config_path == "") {
        return;
    }
    if (!std::filesystem::exists(config_path)) {
        return;
    }

    // Парсим json файл
    json cfg;
    std::ifstream cfg_f(config_path);
    if (!cfg_f) {
        return;
    }
    cfg = json::parse(cfg_f);
    cfg_f.close( );

    // Читаем конфиг
    const char* write_delay_lable = "write_delay";
    if (cfg.contains(write_delay_lable)) {
        write_delay_ = std::chrono::milliseconds(cfg[write_delay_lable]);
    }
    const char* read_delay_lable = "read_delay";
    if (cfg.contains(read_delay_lable)) {
        read_delay_ = std::chrono::milliseconds(cfg[read_delay_lable]);
    }
    const char* move_delay_label = "move_delay";
    if (cfg.contains(move_delay_label)) {
        move_delay_ = std::chrono::milliseconds(cfg[move_delay_label]);
    }
    const char* tmp_path_lable = "tmp_path";
    if (cfg.contains(tmp_path_lable)) {
        tmp_path_ = std::filesystem::path(std::string(cfg[tmp_path_lable]));
    }
}

tape_config::~tape_config( ) {
}

std::chrono::milliseconds tape_config::get_read_delay( ) const {
    return read_delay_;
}

std::chrono::milliseconds tape_config::get_write_delay( ) const {
    return write_delay_;
}

std::chrono::milliseconds tape_config::get_move_delay( ) const {
    return move_delay_;
}

std::filesystem::path tape_config::get_tmp_path() const {
    return tmp_path_;
}

} // tape