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
    car = IMG_LoadTexture(renderer, blue_car.c_str());
    if( car == nullptr){
        IMGError_Prinft("Blue Car loading failed: ");
    }
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

void Set_Classic_Map(SDL_Texture* &map, SDL_Renderer* renderer){
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
void Set_Menu(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, menu.c_str());
    if( map == nullptr){
        IMGError_Prinft("Menu loading failed: ");
    }
}
void Set_Begin(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, Begin.c_str());
    if( map == nullptr){
        IMGError_Prinft("Begin loading failed: ");
    }
}
void Set_Mute(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, mute.c_str());
    if( map == nullptr){
        IMGError_Prinft("mute loading failed: ");
    }
}
void Set_Unmute(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, unmute.c_str());
    if( map == nullptr){
        IMGError_Prinft("unmute loading failed: ");
    }
}
void Set_Play(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, play.c_str());
    if( map == nullptr){
        IMGError_Prinft("play loading failed: ");
    }
}
void Set_Playagain(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, playagain.c_str());
    if( map == nullptr){
        IMGError_Prinft("playagain loading failed: ");
    }
}
void Set_Home(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, home.c_str());
    if( map == nullptr){
        IMGError_Prinft("home loading failed: ");
    }
}
void Set_Help(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, help.c_str());
    if( map == nullptr){
        IMGError_Prinft("help loading failed: ");
    }
}
void Set_Musicon(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, musicon.c_str());
    if( map == nullptr){
        IMGError_Prinft("musicon loading failed: ");
    }
}
void Set_Musicoff(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, musicoff.c_str());
    if( map == nullptr){
        IMGError_Prinft("musicoff loading failed: ");
    }
}
void Set_Quitgame(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, Quitgame.c_str());
    if( map == nullptr){
        IMGError_Prinft("Quitgame loading failed: ");
    }
}
void Set_Tutorial(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, tutorial.c_str());
    if( map == nullptr){
        IMGError_Prinft("Tutortial loading failed: ");
    }
}
void Set_Back(SDL_Texture* &map, SDL_Renderer* renderer){
    map = IMG_LoadTexture(renderer, back.c_str());
    if( map == nullptr){
        IMGError_Prinft("Back loading failed: ");
    }
}
void Set_Background( Mix_Music *&gMusic  ){
    gMusic = Mix_LoadMUS( Sbackground.c_str());
    if( gMusic == NULL ){
        printf( "Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}
void Set_Lose( Mix_Chunk *& chunk  ){
    chunk = Mix_LoadWAV( Slose.c_str());
    if( chunk == NULL ){
        printf( "Failed to load lose chunk! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}
void Set_Hit_Score( Mix_Chunk *& chunk  ){
    chunk = Mix_LoadWAV( Sscore.c_str());
    if( chunk == NULL ){
        printf( "Failed to load hit score chunk! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}
void Set_Click( Mix_Chunk *& chunk  ){
    chunk = Mix_LoadWAV( Sclick.c_str());
    if( chunk == NULL ){
        printf( "Failed to load click chunk! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}





