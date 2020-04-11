//
//  main.cpp
//  QV_Game01
//
//  Created by Võ Minh Quân on 4/6/20.
//  Copyright © 2020 Võ Minh Quân. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <thread>
#include <ctime>
#include "SetSDL.hpp"
#include "Create_Object.hpp"

using namespace std;

struct Car{
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;
    int w = CAR_WIDTH;
    int h = CAR_HEIGHT;
    int x, y;
    void Texture_Destroy() const{
        SDL_DestroyTexture(texture);
    }
    Car(){};
    Car(int _x, int _y){
        x = _x;
        y = _y;
    }
};
struct Score{
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;
    int w = CAR_WIDTH;
    int h = CAR_HEIGHT;
    int x, y;
    void Texture_Destroy() const{
        SDL_DestroyTexture(texture);
    }
    Score(){};
    Score(int _x, int _y){
        x = _x;
        y = _y;
    }
};
int Random(int a, int b);
void Set_Rect(SDL_Rect &rect, int x, int y, int w, int h);
void Play_Game(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* map);
void KEY_FREEMOVE_ACTION( SDL_Event &e, bool &quit, bool &l, bool &r, bool &u, bool &dw, bool &s, bool &a, bool &d, bool &w);

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* map = nullptr;
    initSDL(window, renderer);
    initIMG();
    Play_Game(window, renderer, map);
    //end game
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    SDL_DestroyTexture(map);
    IMG_Quit();
}
int Random(int a, int b){
    static int c=0;
    srand(rand()+c);
    c++;
    if(c>=1000){
        c = 0;
    }
    return rand()%a+b;
}
void Play_Game(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* map){
    Car Blue_Car, Red_Car;
    Score Blue_Score[3], Red_Score[3];
    bool quit = false;
    bool l = false, r = false, u = false, dw = false;
    bool s = false, a = false, d = false, w = false;
    SDL_Event e;
    Set_Red_Car(Red_Car.texture, renderer);
    Set_Blue_Car(Blue_Car.texture, renderer);
    Set_Clasic_Map(map, renderer);
    for(int i=0;i < 3; i++){
        Set_Blue_Score(Blue_Score[i].texture, renderer);
        Set_Red_Score(Red_Score[i].texture, renderer);
    }
    Set_Rect(Red_Car.rect, 250, 650, CAR_WIDTH, CAR_HEIGHT); // x2 340  y2 650
    Set_Rect(Blue_Car.rect, 55, 600, CAR_WIDTH, CAR_HEIGHT); // x2 150 y2 650
    for(int i =0; i < 3; i++){
        Set_Rect(Red_Score[i].rect, 250, 300-100*i, CAR_WIDTH, CAR_WIDTH);  // x1 250 x2 340
        Set_Rect(Blue_Score[i].rect, 55, 300-100*i, CAR_WIDTH, CAR_WIDTH); //  x1 55  x2 150
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, map, NULL, NULL);
    SDL_RenderCopy(renderer, Red_Car.texture, NULL, &Red_Car.rect);
    SDL_RenderCopy(renderer, Blue_Car.texture, NULL, &Blue_Car.rect);
    for(int i =0; i < 3; i++){
        SDL_RenderCopy(renderer, Red_Score[i].texture, NULL, &Red_Score[i].rect);
        SDL_RenderCopy(renderer, Blue_Score[i].texture, NULL, &Blue_Score[i].rect);
       }
    SDL_RenderPresent(renderer);
    while (!quit){
        if(e.type == SDL_QUIT){
            quit = true;
        }
        if(l) Red_Car.rect.x-=10;
        if(r) Red_Car.rect.x+=10;
        if(u) Red_Car.rect.y-=10;
        if(dw) Red_Car.rect.y+=10;
        if(a) Blue_Car.rect.x-=10;
        if(d) Blue_Car.rect.x+=10;
        if(w) Blue_Car.rect.y-=10;
        if(s) Blue_Car.rect.y+=10;
        for(int i =0; i < 3; i++){
            Blue_Score[i].rect.y+=10;
            Red_Score[i].rect.y+=10;
            if(Blue_Score[i].rect.y == SCREEN_HEIGHT){
                Blue_Score[i].rect.y=0;
            }
            if(Red_Score[i].rect.y == SCREEN_HEIGHT){
                Red_Score[i].rect.y=0;
            }
              }
        SDL_Delay(20);
        cout << Red_Car.rect.x << " " << Red_Car.rect.y << endl;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, map, NULL, NULL);
        SDL_RenderCopy(renderer, Red_Car.texture, NULL, &Red_Car.rect);
        SDL_RenderCopy(renderer, Blue_Car.texture, NULL, &Blue_Car.rect);
        for(int i =0; i < 3; i++){
            SDL_RenderCopy(renderer, Red_Score[i].texture, NULL, &Red_Score[i].rect);
            SDL_RenderCopy(renderer, Blue_Score[i].texture, NULL, &Blue_Score[i].rect);
            }
        SDL_RenderPresent(renderer);
        if(SDL_PollEvent(&e) == 0) continue;
        KEY_FREEMOVE_ACTION(e, quit, l, r, u, dw, s, a, d, w);
    }
    /*Blue_Car.Texture_Destroy();
    Red_Car.Texture_Destroy();
    for(int i=0; i < 3 ;i++){
        Blue_Score[i].Texture_Destroy();
        Red_Score[i].Texture_Destroy();
    } */
 }
void KEY_FREEMOVE_ACTION( SDL_Event &e, bool &quit, bool &l, bool &r, bool &u, bool &dw, bool &s, bool &a, bool &d, bool &w){
    if(e.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
           // case SDLK_ESCAPE: quit = true; break;
            case SDLK_UP: u = true; break;
            case SDLK_DOWN: dw = true; break;
            case SDLK_RIGHT: r = true; break;
            case SDLK_LEFT: l = true; break;
            case SDLK_w: w = true; break;
            case SDLK_s: s = true; break;
            case SDLK_d: d = true; break;
            case SDLK_a: a = true; break;
            default: break;
        }
    }
    if(e.type == SDL_KEYUP){
        switch(e.key.keysym.sym){
            case SDLK_ESCAPE: quit = true; break;
            case SDLK_UP: u = false; break;
            case SDLK_DOWN: dw = false; break;
            case SDLK_RIGHT: r = false; break;
            case SDLK_LEFT: l = false; break;
            case SDLK_w: w = false; break;
            case SDLK_s: s = false; break;
            case SDLK_d: d = false; break;
            case SDLK_a: a = false; break;
            default: break;
        }
    }
}
void Set_Rect(SDL_Rect &rect, int x, int y, int w, int h){
    rect.x = x;
    rect.y = y;
    if(w != 0){
        rect.w = w;
    }
    if(h != 0){
        rect.h = h;
    }
}
