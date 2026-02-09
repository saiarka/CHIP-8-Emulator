// main.cpp : Defines the entry point for the application.

#include "emulator_exceptions.h"
#include "emulator.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <chrono>
#include <thread>


#include <SDL3/SDL_main.h>

//TODO: Make variable / input
//500 Hz Clock Frequency
#define FREQUENCY 500

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
    
    auto last_cycle_time = std::chrono::steady_clock().now();
    float accumulator = 0.0; 
    float delta = 0.0;
    //TODO: Future improvement
    //Typical emulator designs use error codes to quit out of emulation loop rather than relying on try catch exceptions --> not great for running ROM games
    while (quit == false) {
        while (SDL_PollEvent( &e ) == true) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            auto cur_cycle_time = std::chrono::steady_clock().now();
            delta = std::chrono::duration<float , std::chrono::milliseconds::period>(cur_cycle_time - last_cycle_time).count();
            accumulator += delta;
            while (accumulator > 1.0 / FREQUENCY) {
                last_cycle_time = cur_cycle_time;
                try {
                    emulator.decode_execute();
                }catch(const CHIP_8_Emulator::CPU_Exception& e) {
                    quit = true;  
                }
                accumulator -= (1.0 / FREQUENCY);
            }

            SDL_RenderPresent(emulator.mcontainer.renderer);
        }
    }

	return 0;
}
