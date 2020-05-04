//
//  SetSDL.cpp
//  SDL test
//
//  Created by Võ Minh Quân on 4/2/20.
//  Copyright © 2020 Võ Minh Quân. All rights reserved.
//

#include "SetSDL.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <thread>
#include <ctime>


void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED,
       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    
}

void logSDLError(ostream& os,
                 const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void waitUntilKeyPressed(){
    SDL_Event e;
    while(true){
        if(SDL_WaitEvent(&e)!= 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)){
            return;
        }

        SDL_Delay(100);
    }
}
void initTTF(){
    if( TTF_Init() == -1 ){
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
}
