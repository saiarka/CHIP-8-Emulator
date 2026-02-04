// main.cpp : Defines the entry point for the application.

#include "emulator.h"
#include "container.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>


#include <SDL3/SDL_main.h>

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

    //Determine if ROM size is greater than available for hardware (3600 bytes)
    auto rom_size = std::filesystem::file_size(argv[1]);
    if (rom_size > 3600) {
        std::cout << "ROM size too large for current CHIP-8 Emu Specification" << std::endl;
        return 0;
    }
    
    Emulator emulator(rom_stream, rom_size);

    bool quit = false;
    SDL_Event e;
    SDL_zero(e);

    while (quit == false) {
        while (SDL_PollEvent( &e ) == true) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }

        }
    }

	return 0;

}
