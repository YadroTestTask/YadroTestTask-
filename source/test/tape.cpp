/// \file tape.cpp
/// \author Ашмаров Ефим
/// \date 06.2023
/// \brief Тесты на класс tape

#include <fstream>
#include <filesystem>

#include <tape.hpp>

#include <CppUTest/TestHarness.h>


namespace tape {

static const char* test_src_tape_path = "/tmp/test_tape.tape";

TEST_GROUP(_tape) {
    void setup ( ) {
        teardown( );
        std::ofstream test_tape(test_src_tape_path, std::ios::binary); 
        for (uint32_t i = 0; i < 50; i++) {
            test_tape.write((char*)(&i), sizeof(i));
        }
        test_tape.close( );
    }

    void teardown( ) {
        if (std::filesystem::exists(test_src_tape_path)) {
            std::filesystem::remove(test_src_tape_path);
        }
    }

};

TEST(_tape, read) {
    auto test_tape = tape(test_src_tape_path, tape_config( ));

    for (uint32_t i = 0; i < 50; i++) {
        CHECK_EQUAL(i, test_tape.read( ))
        test_tape.move_right( );
    }
}


TEST(_tape, write) {
    auto test_tape = tape(test_src_tape_path, tape_config( ));

    for (uint32_t i = 0; i < 50; i++) {
        test_tape.write(49 - i);
        test_tape.move_right( );
    }

    test_tape.move_left( );
    for (uint32_t i = 0; i < 50; i++) {
        CHECK_EQUAL(i, test_tape.read( ))
        test_tape.move_left( );
    }

}



} // tape