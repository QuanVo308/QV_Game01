//
//  SetSDL.hpp
//  SDL test
//
//  Created by Võ Minh Quân on 4/2/20.
//  Copyright © 2020 Võ Minh Quân. All rights reserved.
//

#ifndef SetSDL_hpp
#define SetSDL_hpp

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <thread>
#include <ctime>

using namespace std;
struct Text{
    TTF_Font *gFont = nullptr;
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Color color;
    
    void Destroy();
    void free();
    bool loadFromRenderedText(string textureText, SDL_Color color, SDL_Renderer *renderer );
};
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 850;
const int CAR_WIDTH = 50;
const int CAR_HEIGHT = 100;
const string WINDOW_TITLE = "Two Cars";

void waitUntilKeyPressed();
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void logSDLError(ostream& os, const string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void initTTF();

#endif /* SetSDL_hpp */
