// CHIP8-Emulator.cpp : Defines the entry point for the application.
//

#include "emulator.h"
#include "memory_structure.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

//TODO: Temp width, height values
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

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

    SDL_Window* win = nullptr;
    SDL_Renderer* renderer = nullptr;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0) {
        std::cout << "SDL COULD NOT BE INIT!! SDL_Error:  " << SDL_GetError() << std::endl; 
    }else {
        win = SDL_CreateWindow("CHIP-8 Emulator", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if (win == NULL)  {
            std::cout << "SDL COULD NOT MAKE WINDOW!! SDL_Error: " << SDL_GetError() << std::endl;
        }else {
            renderer = SDL_CreateRenderer(win, nullptr);
            if (renderer == NULL) {
                std::cout << "SDL COULD NOT MAKE RENDERER!! SDL_Error: " << SDL_GetError() << std::endl;
            }else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);

                bool quit = false;
                SDL_Event e;
                SDL_zero(e);

                while (quit == false) {
                    while (SDL_PollEvent( &e ) == true) {
                        if (e.type == SDL_EVENT_QUIT) {
                            quit = true;
                        }

                        //Main will pass in string argument for respective file location of ch8 ROM
                        //ROM read in --> given to Emulator class
                        //ROM loaded into Memory class code chunk
                        //PC can iterate through and fetch instructions --> fetch, decode, execute all within respective 'op code functions'
                        Emulator emulator(rom_stream, rom_size);
                        // Try Catch block for loop or run() function which acts as loop (try every loop expensive?)

                    }
                }
            }
        }

    }

	return 0;

}
