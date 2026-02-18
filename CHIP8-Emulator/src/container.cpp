#include "container.h"
#include <cassert>
#include <iostream>

SDL_Container::SDL_Container() {
    if ( SDL_Init( SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL COULD NOT BE INIT!! SDL_Error:  " << SDL_GetError() << std::endl; 
        assert(0);
    }
    window = SDL_CreateWindow("CHIP-8 Emulator", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == nullptr) {
        std::cout << "SDL COULD NOT MAKE WINDOW!! SDL_Error: " << SDL_GetError() << std::endl;
        assert(0);
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        std::cout << "SDL COULD NOT MAKE RENDERER!! SDL_Error: " << SDL_GetError() << std::endl;
        assert(0);
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    pixel_screen = std::vector<uint8_t>(SCREEN_WIDTH*SCREEN_HEIGHT, 0);
    //TODO: Temporary hard-coded scale --> change to user input
    SDL_SetRenderScale(renderer, 10.0f, 10.0f);
};

SDL_Container::~SDL_Container() {
    std::cout << "SDL_Container Destructor called" << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}




