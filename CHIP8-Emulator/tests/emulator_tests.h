#ifndef _EMULATOR_TESTS_H_
#define _EMULATOR_TESTS_H_

#include "../src/emulator.h"
#include <gtest/gtest.h>
#include <iostream>
#include <filesystem>

class EmulatorTest : public testing::Test {
   
    protected:
        
        std::unique_ptr<Emulator> test_emulator;

        EmulatorTest() {
            std::filesystem::path test_rom = "../../../test_roms/1-chip8-logo.ch8";
            std::ifstream rom_stream(test_rom, std::ios::binary);

            if (!rom_stream.is_open()) {
                std::cout << "ROM failed to open in Emulator Test Const, recheck location or filename" << std::endl;
            }

            auto rom_size = std::filesystem::file_size(test_rom);
            test_emulator = std::make_unique<Emulator>(Emulator(rom_stream, rom_size));
            
        }
    
};

class EmulatorTest3 : public testing::Test {
    protected:
        std::unique_ptr<Emulator> test_emulator;

        EmulatorTest3() {
            std::string test_rom =  "../../../test_roms/3-corax+.ch8";
            std::ifstream rom_stream(test_rom, std::ios::binary);
 
            if (!rom_stream.is_open()) {
                std::cout << "ROM failed to open in Emulator Test Const, recheck location or filename" << std::endl;
            }

            auto rom_size = std::filesystem::file_size(test_rom);
            test_emulator = std::make_unique<Emulator>(Emulator(rom_stream, rom_size));
        }
};


#endif





