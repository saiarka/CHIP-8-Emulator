#include "container.h"
#include <cassert>
#include <iostream>

void SDL_Container::init() {
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
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
};




