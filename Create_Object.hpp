//
//  Create_Object.hpp
//  QV_Game02
//
//  Created by Võ Minh Quân on 4/8/20.
//  Copyright © 2020 Võ Minh Quân. All rights reserved.
//

#ifndef Create_Object_hpp
#define Create_Object_hpp

#include <iostream>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

const string classic_map = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/MAP/Classic_Map2.png";
const string blue_car = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/Blue.png";
const string red_car = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/Red.png";
const string blue_score = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/BlueScore.png";
const string red_score = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/RedScore.png";
const string red_obs = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/RedObs.png";
const string blue_obs = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/BlueObs.png";
const int Obj_Quantity = 10;
void initIMG();
void IMGError_Prinft(string error);
void Set_Red_Car(SDL_Texture* &car, SDL_Renderer* renderer);
void Set_Clasic_Map(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Blue_Score(SDL_Texture* &score, SDL_Renderer* renderer);
void Set_Red_Score(SDL_Texture* &score, SDL_Renderer* renderer);
void Set_Blue_Car(SDL_Texture* &car, SDL_Renderer* renderer);
void Set_Blue_Obs(SDL_Texture* &score, SDL_Renderer* renderer);
void Set_Red_Obs(SDL_Texture* &score, SDL_Renderer* renderer);
#endif 
