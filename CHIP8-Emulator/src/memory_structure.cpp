
#include "memory_structure.h"
#include <fstream>

Memory_Structure::Memory_Structure(std::ifstream& rom_stream, int rom_size) {
    mcode_chunk = std::vector<uint16_t>(rom_size);

    rom_stream.read(reinterpret_cast<char*>(mcode_chunk.data()), static_cast<std::streamsize>(rom_size));

}







