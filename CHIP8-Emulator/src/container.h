#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>

#include <SDL3/SDL.h>

class SDL_Container {

    public:
        
        const int SCREEN_WIDTH = 64;
        const int SCREEN_HEIGHT = 32;

        std::vector<uint8_t> pixel_screen;

        SDL_Window* window;
        SDL_Renderer* renderer;
        
        SDL_Container();
        ~SDL_Container();

};

#endif
