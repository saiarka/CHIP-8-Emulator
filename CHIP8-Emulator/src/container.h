#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <SDL3/SDL.h>

class SDL_Container {

    public:
        
        //TODO: Temp Screen h, w
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 720;

        SDL_Window* window;
        SDL_Renderer* renderer;
        
        void init();

};

#endif
