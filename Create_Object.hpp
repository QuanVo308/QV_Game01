//
//  Create_Object.hpp
//  QV_Game02
//
//  Created by Võ Minh Quân on 4/8/20.
//  Copyright © 2020 Võ Minh Quân. All rights reserved.
//

#ifndef Create_Object_hpp
#define Create_Object_hpp

#include "SetSDL.hpp"

using namespace std;

const int CAR_WIDTH = 50;
const int CAR_HEIGHT = 100;

struct Car{
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;
    double angle;
    void Texture_Destroy() const{
        SDL_DestroyTexture(texture);
    }
    Car(){
        rect.w = CAR_WIDTH;
        rect.h = CAR_HEIGHT;
    };
    Car(int _x, int _y){
        rect.w = CAR_WIDTH;
        rect.h = CAR_HEIGHT;
        rect.x = _x;
        rect.y = _y;
    }
};
struct Object{
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;
    int x, y;
    bool run = false;
    void Texture_Destroy() const{
        SDL_DestroyTexture(texture);
    }
    Object(){
        rect.w = CAR_WIDTH;
        rect.h = CAR_WIDTH;
    };
    Object(int _x, int _y){
        rect.w = CAR_WIDTH;
        rect.h = CAR_WIDTH;
        rect.x = _x;
        rect.y = _y;
    }
};
const string classic_map = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/MAP/Classic_Map2.png";
const string menu = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/MAP/menu.jpg";
const string Begin = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/MAP/begin.jpg";
const string blue_car = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/Blue.png";
const string red_car = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/Red.png";
const string blue_score = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/BlueScore.png";
const string red_score = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/RedScore.png";
const string red_obs = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/RedObs.png";
const string blue_obs = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Object/BlueObs.png";
const string mute = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/mute.png";
const string home = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/home.png";
const string unmute = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/unmute.png";
const string playagain = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/playagain.png";
const string play = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/play.png";
const string help = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/help.png";
const string musicon = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/music.png";
const string musicoff = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/musicoff.png";
const string Quitgame = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/quit.png";
const string tutorial = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/MAP/help.png";
const string back = "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Button/back.png";

const int Obj_Quantity = 10;
const int Obj_Speed = 7;
const int Car_Angle_Change = 12;
const int Car_x_Change = 15;
const int LR_Line = 250;
const int RR_Line = 340;
const int LB_Line = 55;
const int RB_Line = 150;
const int Car_y = 650;
//Text text;
void initIMG();
void IMGError_Prinft(string error);
void Set_Red_Car(SDL_Texture* &car, SDL_Renderer* renderer);
void Set_Clasic_Map(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Blue_Score(SDL_Texture* &score, SDL_Renderer* renderer);
void Set_Red_Score(SDL_Texture* &score, SDL_Renderer* renderer);
void Set_Blue_Car(SDL_Texture* &car, SDL_Renderer* renderer);
void Set_Blue_Obs(SDL_Texture* &score, SDL_Renderer* renderer);
void Set_Red_Obs(SDL_Texture* &score, SDL_Renderer* renderer);
void Set_Menu(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Begin(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Mute(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Unmute(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Home(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Play(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Playagain(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Help(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Musicon(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Musicoff(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Quitgame(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Tutorial(SDL_Texture* &map, SDL_Renderer* renderer);
void Set_Back(SDL_Texture* &map, SDL_Renderer* renderer);


#endif 
