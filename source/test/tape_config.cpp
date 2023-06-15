/// \file tape_config.cpp
/// \author Ашмаров Ефим
/// \date 06.2023
/// \brief Тесты на класс tape_config

#include <fstream>
#include <filesystem>

#include <tape_config.hpp>

#include <CppUTest/TestHarness.h>


namespace tape {

static const char* test_cfg_path = "/tmp/test_config.cfg";

TEST_GROUP(_tape_config) {
    void setup ( ) {
        teardown( );
        std::ofstream test_cfg(test_cfg_path); 
        test_cfg << "{\"write_delay\" : 500,"
                    "\"read_delay\"  : 300,"
                    "\"move_delay\"  : 200,"
                    "\"tmp_path\"    : \"/tmp/\"}";
        test_cfg.close( );
    }

    void teardown( ) {
        if (std::filesystem::exists(test_cfg_path)) {
            std::filesystem::remove(test_cfg_path);
        }
    }

};

TEST(_tape_config, read) {
    auto cfg = tape_config(test_cfg_path);
    CHECK_EQUAL(500, cfg.get_write_delay( ).count( ));
    CHECK_EQUAL(300, cfg.get_read_delay( ).count( ));
    CHECK_EQUAL(200, cfg.get_move_delay( ).count( ));
    CHECK_EQUAL(std::filesystem::path("/tmp/"), cfg.get_tmp_path( ));
}



} // tape