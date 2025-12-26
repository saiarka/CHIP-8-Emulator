
#include "emulator.h"


Emulator::Emulator(std::ifstream& rom_stream, int rom_size) : 
    mMemory(rom_stream, rom_size){};





