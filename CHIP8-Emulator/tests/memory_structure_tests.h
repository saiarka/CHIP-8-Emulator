#ifndef _MEMORY_STRUCTURE_TESTS_H_
#define _MEMORY_STRUCTURE_TESTS_H_

#include "../src/memory_structure.h" 
#include <string>
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <memory>

class Memory_StructureTest : public testing::Test {
    
    protected:
        
        std::unique_ptr<Memory_Structure> test_memory;

        Memory_StructureTest() {
            std::filesystem::path test_rom = "../../../test_roms/1-chip8-logo.ch8";
            std::ifstream rom_stream(test_rom, std::ios::binary);
            auto rom_size = std::filesystem::file_size(test_rom);
            test_memory = std::make_unique<Memory_Structure>(rom_stream, std::filesystem::file_size(test_rom));
        }

};

#endif
