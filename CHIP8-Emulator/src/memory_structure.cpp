
#include "memory_structure.h"
#include <fstream>
#include <iostream>

//TODO: Check if memory byte truncation is a problem (0x0F) --> (F)
Memory_Structure::Memory_Structure(std::ifstream& rom_stream, int rom_size) {
    mmemory_chunk = std::vector<uint8_t>(4096, 0);
    rom_stream.read(reinterpret_cast<char*>(mmemory_chunk.data() + 512), static_cast<std::streamsize>(rom_size));
    mprogram_counter = mmemory_chunk.data() + 512;

    mstack_chunk = std::vector<uint8_t>(64, 0);
    mstack_pointer = mstack_chunk.data();

    V0 = 0;
    V1 = 0;
    V2 = 0;
    V3 = 0;
    V4 = 0;
    V5 = 0;
    V6 = 0;
    V7 = 0;
    V8 = 0;
    V9 = 0;
    VA = 0;
    VB = 0;
    VC = 0;
    VD = 0;
    VE = 0;
    VF = 0;
};

Memory_Structure::~Memory_Structure() {

    mprogram_counter = nullptr;
    mstack_pointer = nullptr;

};

void Memory_Structure::print_memory() {
    for(int i = 0; i < mmemory_chunk.size(); i++) {
        std::cout << std::hex << static_cast<int>(mmemory_chunk[i]);
        if (i % 10 == 0) {std::cout << std::endl;}
    }
};









