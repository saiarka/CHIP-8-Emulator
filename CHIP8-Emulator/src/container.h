#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>

#include <SDL3/SDL.h>

class SDL_Container {

    public:
        
        //TODO: Temporary hard-coded scale --> change to user input
        const int SCREEN_WIDTH = 64 * 10;
        const int SCREEN_HEIGHT = 32 * 10;

        std::vector<uint8_t> pixel_screen;

        SDL_Window* window;
        SDL_Renderer* renderer;
        
        SDL_Container();
        ~SDL_Container();

};

#endif
