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
#include <SDL2/SDL.h>
using namespace std;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;
const int CAR_WIDTH = 50;
const int CAR_HEIGHT = 100;
const string WINDOW_TITLE = "Two Cars";
void waitUntilKeyPressed();
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void logSDLError(ostream& os, const string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

#endif /* SetSDL_hpp */
