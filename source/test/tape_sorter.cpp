/// \file tape_sorter.cpp
/// \author Ашмаров Ефим
/// \date 06.2023
/// \brief Тесты на класс tape_sorter

#include <fstream>
#include <filesystem>

#include <tape.hpp>
#include <tape_sorter.hpp>

#include <CppUTest/TestHarness.h>


namespace tape {

static const char* test_src_tape_path = "/tmp/test_src_tape.tape";
static const char* test_tgt_tape_path = "/tmp/test_target_tape.tape";


TEST_GROUP(_tape_sorter) {
    void setup ( ) {
        teardown( );
        std::ofstream test_tape(test_src_tape_path, std::ios::binary); 
        for (uint32_t i = 5; i > 0; i--) {
            test_tape.write((char*)(&i), sizeof(i));
        }
        for (uint32_t i = 10; i > 5; i--) {
            test_tape.write((char*)(&i), sizeof(i));
        }
        test_tape.close( );
    }

    void teardown( ) {
        if (std::filesystem::exists(test_src_tape_path)) {
            std::filesystem::remove(test_src_tape_path);
        }
        if (std::filesystem::exists(test_tgt_tape_path)) {
            std::filesystem::remove(test_tgt_tape_path);
        }
    }

};

TEST(_tape_sorter, sort) {
    auto test_obj = tape_sorter();
    test_obj.sort(test_src_tape_path, test_tgt_tape_path);

    auto tst = tape(test_tgt_tape_path, tape_config( ));

    CHECK_EQUAL(std::filesystem::file_size(test_src_tape_path), std::filesystem::file_size(test_tgt_tape_path))

    uint32_t prev_elem = 0;
    for (int i = 0; i < 10; i++) {
        uint32_t new_elem = tst.read( );
        tst.move_right( );
        CHECK(new_elem > prev_elem);
        prev_elem = new_elem;
    }
    
}



} // tape