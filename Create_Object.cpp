//
//  Create_Object.cpp
//  QV_Game02
//
//  Created by Võ Minh Quân on 4/8/20.
//  Copyright © 2020 Võ Minh Quân. All rights reserved.
//

#include "Create_Object.hpp"
#include "SetSDL.hpp"

using namespace std;
//Text text;
void initIMG(){
    int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
    }
}
void IMGError_Prinft(string error){
    cout << error << IMG_GetError() << endl;
}
void Set_Red_Car(SDL_Texture* &car, SDL_Renderer* renderer){
    car = IMG_LoadTexture(renderer, red_car.c_str());
    if( car == nullptr){
        IMGError_Prinft("Red Car loading failed: ");
    }
}
void Set_Blue_Car(SDL_Texture* &car, SDL_Renderer* renderer){
    //SDL_Surface* surface = nullptr;
    //surface = IMG_Load(blue_car.c_str());
    //car = SDL_CreateTextureFromSurface(renderer, surface);
    car = IMG_LoadTexture(renderer, blue_car.c_str());
    if( car == nullptr){
        IMGError_Prinft("Blue Car loading failed: ");
    }
    //SDL_FreeSurface(surface);
}

void Set_Red_Score(SDL_Texture* &score, SDL_Renderer* renderer){
    score = IMG_LoadTexture(renderer, red_score.c_str());
    if( score == nullptr){
        IMGError_Prinft("Red Score loading failed: ");
    }
}

void Set_Blue_Score(SDL_Texture* &score, SDL_Renderer* renderer){
    score = IMG_LoadTexture(renderer, blue_score.c_str());
    if( score == nullptr){
        IMGError_Prinft("Blue Score loading failed: ");
    }
}

void Set_Clasic_Map(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, classic_map.c_str());
    if( map == nullptr){
        IMGError_Prinft("Classic Map loading failed: ");
    }
}

void Set_Blue_Obs(SDL_Texture* &score, SDL_Renderer* renderer){
    score = IMG_LoadTexture(renderer, blue_obs.c_str());
    if( score == nullptr){
        IMGError_Prinft("Blue Obstacle loading failed: ");
    }
}

void Set_Red_Obs(SDL_Texture* &score, SDL_Renderer* renderer){
    score = IMG_LoadTexture(renderer, red_obs.c_str());
    if( score == nullptr){
        IMGError_Prinft("Red Obstacle loading failed: ");
    }
}
/*void print_text(int size, Uint8 r, Uint8 g, Uint8 b   ){
    text.gFont = TTF_OpenFont( "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Font/VNARIALB.ttf", size );
    if( text.gFont == NULL )
       {
           printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
       }
       else
       {
           //Render text
           text.color= { r, g, b };
           if( !gTextTexture.loadFromRenderedText( "The quick brown fox jumps over the lazy dog ", textColor ) )
           {
               printf( "Failed to render text texture!\n" );
               success = false;
           }
       }
    
} */

