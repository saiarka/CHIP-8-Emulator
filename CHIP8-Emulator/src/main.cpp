// CHIP8-Emulator.cpp : Defines the entry point for the application.
//

#include "emulator.h"
#include "memory_structure.h"

#include <iostream>
#include <fstream>
#include <filesystem>


//500 Hz Clock Frequency --> 2 ms per tick

int main(int argc, char* argv[])
{

    if (argc != 2) {
        std::cout << "Invalid Number of Arguments, Please Include ROM Location" << std::endl;
        return 0;
    }

    std::string rom_name = argv[1];
    std::ifstream rom_stream(rom_name, std::ios::binary);
    if (!rom_stream.is_open()) {
        std::cout << "ROM failed to open, recheck location or filename" << std::endl;
        return 0;
    }

    //Determine if ROM size is greater than available for hardware (3232 bytes)
    
    auto rom_size = std::filesystem::file_size(argv[1]);
    
    if (rom_size > 3232) {
        std::cout << "ROM size too large for current CHIP-8 Emu Specification" << std::endl;
        return 0;
    }

   //Main will pass in string argument for respective file location of ch8 ROM
   //ROM read in --> given to Emulator class
   //ROM loaded into Memory class code chunk
   //PC can iterate through and fetch instructions --> fetch, decode, execute all within respective 'op code functions'
   Emulator emulator(rom_stream, rom_size);


   //Emulator class performs fetch,decode,execute for all op codes
   //Holds memory class --> Holds main memory, stack, register values


	return 0;

}
