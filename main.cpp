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

Object Blue_Score[Obj_Quantity], Red_Score[Obj_Quantity];
Object Blue_Obs[Obj_Quantity], Red_Obs[Obj_Quantity];
Car Blue_Car(55,650), Red_Car(250,650);
SDL_Texture* map = nullptr;

int Random(int a, int b);
void Set_Rect(SDL_Rect &rect, int x, int y, int w, int h);
void Play_Game(SDL_Window* window, SDL_Renderer* renderer/*, SDL_Texture* map*/);
void KEY_FREEMOVE_ACTION( SDL_Event &e, bool &quit, bool &l, bool &r, bool &u, bool &dw, bool &s, bool &a, bool &d, bool &w);
void draw(SDL_Renderer* &renderer);
void Object_move(bool &appearR , bool &appearB);
void Car_move(SDL_Event &e, bool &quit);
bool check_collision(SDL_Rect a, SDL_Rect b);
void Set_Object( SDL_Renderer * renderer);

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    initSDL(window, renderer);
    initIMG();
    Play_Game(window, renderer);
    //end game
    //waitUntilKeyPressed();
    quitSDL(window, renderer);
    SDL_DestroyTexture(map);
    IMG_Quit();
}
int Random(int a, int b){
    static int c=4;
    srand(c );
    c+=rand()%100+7;
    if(c>=9999999){
        c = rand()%100+1;
    }
    return rand()%b+a;
}
void Play_Game(SDL_Window* window, SDL_Renderer* renderer/*,SDL_Texture* map*/){
    bool quit = false;
    SDL_Event e;
    Set_Object(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw(renderer);
    int score = 0;
    while (!quit){
        bool appearRS = true, appearBS = true;
        bool appearRO = true, appearBO = true;
        if(e.type == SDL_QUIT){
            quit = true;
        }
        Car_move(e, quit);
        Object_move(appearRS ,appearBS);
        SDL_Delay(20);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw(renderer);
        if(SDL_PollEvent(&e) == 0) continue;
    }
   // end
    Blue_Car.Texture_Destroy();
    Red_Car.Texture_Destroy();
    for(int i=0; i < Obj_Quantity ;i++){
        Blue_Score[i].Texture_Destroy();
        Red_Score[i].Texture_Destroy();
    
    }
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
void draw(SDL_Renderer* &renderer){
    SDL_RenderCopy(renderer, map, NULL, NULL);
    SDL_RenderCopy(renderer, Red_Car.texture, NULL, &Red_Car.rect);
    SDL_RenderCopy(renderer, Blue_Car.texture, NULL, &Blue_Car.rect);
    for(int i =0; i < Obj_Quantity; i++){
        SDL_RenderCopy(renderer, Red_Score[i].texture, NULL, &Red_Score[i].rect);
        SDL_RenderCopy(renderer, Blue_Score[i].texture, NULL, &Blue_Score[i].rect);
       }
    SDL_RenderPresent(renderer);
}
void Object_move(bool &appearR , bool &appearB){
    int Obj_Speed = 13;
    for(int i =0; i < Obj_Quantity; i++){
        if( check_collision(Blue_Car.rect, Blue_Score[i].rect) ){
                Blue_Score[i].rect.y = SCREEN_HEIGHT;
                Blue_Score[i].run = false;
            }
            if( check_collision(Red_Car.rect, Red_Score[i].rect) ){
                            Red_Score[i].rect.y = SCREEN_HEIGHT;
                            Red_Score[i].run = false;
                        }
            if(Blue_Score[i].run == true){
                Blue_Score[i].rect.y += Obj_Speed;
            }
            if(Red_Score[i].run == true){
                Red_Score[i].rect.y += Obj_Speed;
            }
            if(Red_Score[i].rect.y < SCREEN_HEIGHT/5){
                appearR = false;
            }
            if(Blue_Score[i].rect.y < SCREEN_HEIGHT/5){
                appearB = false;
            }
            if(Blue_Score[i].rect.y > SCREEN_HEIGHT){
                Blue_Score[i].run = false;
            }
            if(Red_Score[i].rect.y > SCREEN_HEIGHT){
                Red_Score[i].run = false;
            }
        }
    if(appearR == true){
        for(int i =0; i < Obj_Quantity; i++){
            if( Red_Score[i].run==false){
                if(Random(1,100)%10 == 3){
                    int n =Random(1,100);
                    Red_Score[i].run =true;
                    cout << n << endl;
                    Red_Score[i].rect.x = Random(1,300)%2==0  ? 250 : 340;
                    Red_Score[i].rect.y = 0;
                }
                break;
            }
        }
    }
    if(appearB == true){
        for(int i =0; i < Obj_Quantity; i++){
            if( Blue_Score[i].run==false){
                int n =(Random(1,3000));
                if(Random(1,100)%10 == 7){
                    Blue_Score[i].run =true;
                    Blue_Score[i].rect.x = n%2==0  ? 55 : 150;
                    Blue_Score[i].rect.y = 0;
                }
                break;
            }
        }
    }
}

void Car_move(SDL_Event &e, bool &quit){
    static bool l = false, r = false, u = false, dw = false;
    static bool s = false, a = false, d = false, w = false;
    static int dw_check_right = -1;
    static bool check_dw = true;
    static int s_check_right = -1;
    static bool check_s = true;
    if(dw){
               if(check_dw == true){
                   dw_check_right = dw_check_right == -1 ? 1:-1;
               }
                   check_dw = false;
           } else {
               check_dw = true;
           }
           if(check_dw == true){
               if(dw_check_right == 1 && Red_Car.rect.x <340){
                   Red_Car.rect.x += 20;
                   if(Red_Car.rect.x >340){
                       Red_Car.rect.x = 340;
                   }
               } else if( Red_Car.rect.x > 250 && dw_check_right == -1) {
                   Red_Car.rect.x -= 20;
                   if(Red_Car.rect.x <250){
                       Red_Car.rect.x = 250;
                   }
               }
           }
           if(s){
               if(check_s == true){
                   s_check_right = s_check_right == -1 ? 1:-1;
               }
                   check_s = false;
           } else {
               check_s = true;
           }
           if(check_s == true){
               if(s_check_right == 1 && Blue_Car.rect.x <340){
                   Blue_Car.rect.x += 20;
                   if(Blue_Car.rect.x >150){
                       Blue_Car.rect.x = 150;
                   }
               } else if( Blue_Car.rect.x > 55 && s_check_right == -1) {
                   Blue_Car.rect.x -= 20;
                   if(Blue_Car.rect.x <55){
                       Blue_Car.rect.x = 55;
                   }
               }
           }
    KEY_FREEMOVE_ACTION(e, quit, l, r, u, dw, s, a, d, w);
}

bool check_collision(SDL_Rect a, SDL_Rect b){
    if((a.x < b.x+b.w)&&(a.x + a.w > b.x) &&(a.y < b.y+b.h)&&(a.y + a.h > b.y)){
        return true;
    } else {
        return false;
    }
}

void Set_Object( SDL_Renderer * renderer){
    Set_Red_Car(Red_Car.texture, renderer);
    Set_Blue_Car(Blue_Car.texture, renderer);
    Set_Clasic_Map(map, renderer);
    for(int i=0;i < Obj_Quantity; i++){
        Set_Blue_Score(Blue_Score[i].texture, renderer);
        Set_Red_Score(Red_Score[i].texture, renderer);
        Set_Blue_Obs(Blue_Obs[i].texture, renderer);
        Set_Red_Obs(Red_Obs[i].texture, renderer);
    }
    for(int i =0; i < Obj_Quantity; i++){
        Set_Rect(Red_Score[i].rect, 250, SCREEN_HEIGHT, CAR_WIDTH, CAR_WIDTH);  // x1 250 x2 340
        Set_Rect(Blue_Score[i].rect, 55, SCREEN_HEIGHT, CAR_WIDTH, CAR_WIDTH); //  x1 55  x2 150
        Set_Rect(Red_Obs[i].rect, 250, SCREEN_HEIGHT, CAR_WIDTH, CAR_WIDTH);  // x1 250 x2 340
        Set_Rect(Blue_Obs[i].rect, 55, SCREEN_HEIGHT, CAR_WIDTH, CAR_WIDTH); //  x1 55  x2 150
        
    }
}
