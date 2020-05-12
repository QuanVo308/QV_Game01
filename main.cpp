#include "Create_Object.hpp"

using namespace std;

bool die;
int score = 0;
bool quit = false;
bool quitgame = false, pause = false;
bool music = true;
Object Blue_Score[Obj_Quantity], Red_Score[Obj_Quantity];
Object Blue_Obs[Obj_Quantity], Red_Obs[Obj_Quantity];
Car Blue_Car(55,650), Red_Car(250,650);
SDL_Texture* map = nullptr;
Text text;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int Random(int a, int b);
void Set_Rect(SDL_Rect &rect, int x, int y, int w, int h);
void Play_Game();
void KEY_FREEMOVE_ACTION( SDL_Event &e, bool &quit, bool &l, bool &r, bool &u, bool &dw, bool &s, bool &a, bool &d, bool &w);
void draw();
void Object_move(bool &appearR , bool &appearB);
void Car_move(SDL_Event &e, bool &quit);
bool check_collision(SDL_Rect a, SDL_Rect b);
void Set_Object();
void print_text(int size_text, Uint8 r, Uint8 g, Uint8 b , string gText, int x, int y, double zoom );
void fix_Bposition_collision(Object Blue_Obs);
void fix_Rposition_collision(Object Red_Obs);
void Mouse_Event(SDL_Event e, int &x, int &y);
void draw_begin();
void draw_menu();

int main() {
    initSDL(window, renderer);
    initIMG();
    initTTF();
    Set_Object();
    draw_begin();
    waitUntilKeyPressed();
    draw_menu();
    waitUntilKeyPressed();
   // while(!quitgame){
        
      Play_Game();
   // }
    //start()
   
    //end game
    if(die){
        waitUntilKeyPressed();
    }
    text.Destroy();
    SDL_DestroyTexture(map);
    quitSDL(window, renderer);
    IMG_Quit();
    TTF_Quit();
}
int Random(int a, int b){
    srand(time(0));
    static int c=rand();
    srand(c);
    c+=rand()%100+7;
    if(c>=9999999){
        c = rand()%100+1;
    }
    return rand()%b+a;
}
void Play_Game(){
    quit = false;
    SDL_Event e;
    //Set_Object();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw();
    score = 0;
    while (!quit){
        bool appearRS = true, appearBS = true;
    //    bool appearRO = true, appearBO = true;
        if(e.type == SDL_QUIT){
            quit = true;
        }
        Car_move(e, quit);
        Object_move(appearRS ,appearBS);
        SDL_Delay(10);
        draw();
         
        if(SDL_PollEvent(&e) == 0) continue;
        cout << "Score: " << score << endl;
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
void draw(){
    
    //SDL_RenderCopy(renderer, Red_Car.texture, NULL, &Red_Car.rect);
    //SDL_RenderCopy(renderer, Blue_Car.texture, NULL, &Blue_Car.rect);
    if(!die){
        SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle, nullptr, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle, nullptr, SDL_FLIP_NONE);
    } else {
      // waitUntilKeyPressed();
    }
    
    for(int i =0; i < Obj_Quantity; i++){
        SDL_RenderCopy(renderer, Red_Score[i].texture, NULL, &Red_Score[i].rect);
        SDL_RenderCopy(renderer, Blue_Score[i].texture, NULL, &Blue_Score[i].rect);
        SDL_RenderCopy(renderer, Red_Obs[i].texture, NULL, &Red_Obs[i].rect);
        SDL_RenderCopy(renderer, Blue_Obs[i].texture, NULL, &Blue_Obs[i].rect);
       }
    print_text(20, 255, 255, 255, "SCORE", 420, 360, 1.5);
    print_text(20, 255, 255, 255, to_string(score), 420, 400, 1.5);

    SDL_RenderPresent(renderer);
    //if(die) waitUntilKeyPressed();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, map, NULL, NULL);
}
void Object_move(bool &appearR , bool &appearB){
    for(int i =0; i < Obj_Quantity; i++){
        if( SDL_HasIntersection(&Blue_Car.rect, &Blue_Score[i].rect) ){
            Blue_Score[i].rect.y = SCREEN_HEIGHT;
            Blue_Score[i].run = false;
            score++;
        }
        if( check_collision(Red_Car.rect, Red_Score[i].rect) ){
            Red_Score[i].rect.y = SCREEN_HEIGHT;
            Red_Score[i].run = false;
            score++;
        }
        if(Blue_Score[i].run == true){
            Blue_Score[i].rect.y += Obj_Speed + score/30;
        }
        if(Red_Score[i].run == true){
            Red_Score[i].rect.y += Obj_Speed + score/30;
        }
        if(Red_Score[i].rect.y < 2*SCREEN_HEIGHT/7){
            appearR = false;
        }
        if(Blue_Score[i].rect.y < 2*SCREEN_HEIGHT/7){
            appearB = false;
        }
        if(Blue_Score[i].rect.y > SCREEN_HEIGHT){
            Blue_Score[i].run = false;
        }
        if(Red_Score[i].rect.y > SCREEN_HEIGHT){
            Red_Score[i].run = false;
        }
        Blue_Car.rect.x-=3;
        Blue_Car.rect.h-=30;
        Blue_Car.rect.w+=6;
        if( SDL_HasIntersection(&Blue_Car.rect, &Blue_Obs[i].rect) ){
            Blue_Obs[i].run = false;
            die = true;
            quit = true;
            fix_Bposition_collision(Blue_Obs[i]);
        } else {
            Blue_Car.rect.h+=30;
            Blue_Car.rect.w-=6;
        }
        Blue_Car.rect.x+=3;
        Red_Car.rect.x-=3;
        Red_Car.rect.h-=30;
        Red_Car.rect.w+=6;
        if( SDL_HasIntersection(&Red_Car.rect, &Red_Obs[i].rect) ){
            Red_Obs[i].run = false;
            die = true;
            quit = true;
            fix_Rposition_collision(Red_Obs[i]);
        } else {
            Red_Car.rect.h+=30;
            Red_Car.rect.w-=6;
        }
        Red_Car.rect.x+=3;
        if(Blue_Obs[i].run == true){
            Blue_Obs[i].rect.y += Obj_Speed + score/30;
        }
        if(Red_Obs[i].run == true){
            Red_Obs[i].rect.y += Obj_Speed + score/30;
        }
        if(Red_Obs[i].rect.y < 2*SCREEN_HEIGHT/7){
            appearR = false;
        }
        if(Blue_Obs[i].rect.y < 2*SCREEN_HEIGHT/7){
            appearB = false;
        }
        if(Blue_Obs[i].rect.y > SCREEN_HEIGHT){
            Blue_Obs[i].run = false;
        }
        if(Red_Obs[i].rect.y > SCREEN_HEIGHT){
            Red_Obs[i].run = false;
        }
    }
    if(appearR == true){
        for(int i =0; i < Obj_Quantity; i++){
            if(Random(1,3000)%2==0){
                if( Red_Score[i].run==false){
                    if(Random(1,100)%10 == 3){
                        Red_Score[i].run =true;
                        Red_Score[i].rect.x = Random(1,300)%2==0  ? 250 : 340;
                        Red_Score[i].rect.y = 0;
                    }
                    break;
                }
            } else {
                if( Red_Obs[i].run==false){
                    if(Random(1,100)%10 == 3){
                        Red_Obs[i].run =true;
                        Red_Obs[i].rect.x = Random(1,300)%2==0  ? 250 : 340;
                        Red_Obs[i].rect.y = 0;
                    }
                    break;
                }
            }
        }
    }
    if(appearB == true){
        for(int i =0; i < Obj_Quantity; i++){
            if(Random(1,3000)%2==0){
                if( Blue_Score[i].run==false){
                    if(Random(1,100)%10 == 7){
                        Blue_Score[i].run =true;
                        Blue_Score[i].rect.x = Random(1,300)%2==0  ? 55 : 150;
                        Blue_Score[i].rect.y = 0;
                    }
                    break;
                }
            } else {
                if( Blue_Obs[i].run==false){
                    if(Random(1,100)%10 == 7){
                        Blue_Obs[i].run =true;
                        Blue_Obs[i].rect.x = Random(1,300)%2==0  ? 55 : 150;
                        Blue_Obs[i].rect.y = 0;
                    }
                    break;
                }
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
            Red_Car.rect.x += 15;
            if(Red_Car.angle <=45 && Red_Car.rect.x < (340+250)/2){
                Red_Car.angle +=12;
            } else {
                Red_Car.angle -=12;
            }
            if(Red_Car.rect.x >=340){
                Red_Car.rect.x = 340;
                Red_Car.angle =0;
            }
        } else if( Red_Car.rect.x > 250 && dw_check_right == -1) {
            Red_Car.rect.x -= 15;
            if(Red_Car.angle >=-45 && Red_Car.rect.x > (340+250)/2){
                Red_Car.angle -=12;
            } else {
                Red_Car.angle +=12;
            }
            if(Red_Car.rect.x <=250){
                Red_Car.rect.x = 250;
                Red_Car.angle =0;
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
        if(s_check_right == 1 && Blue_Car.rect.x <150){
            Blue_Car.rect.x += 15;
            if(Blue_Car.angle <=45 && Blue_Car.rect.x < (55+150)/2){
                Blue_Car.angle +=12;
            } else {
                Blue_Car.angle -=12;
            }
            if(Blue_Car.rect.x >=150){
                Blue_Car.rect.x = 150;
                Blue_Car.angle =0;
            }
            //cout << Blue_Car.angle << endl;
        } else if( Blue_Car.rect.x > 55 && s_check_right == -1) {
            Blue_Car.rect.x -= 15;
            if(Blue_Car.angle >=-45 && Blue_Car.rect.x > (55+150)/2){
                Blue_Car.angle -=12;
            } else {
                Blue_Car.angle +=12;
            }

            if(Blue_Car.rect.x <=55){
                Blue_Car.rect.x = 55;
                Blue_Car.angle =0;
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

void Set_Object(){
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
void print_text(int size_text, Uint8 r, Uint8 g, Uint8 b , string gText, int x, int y, double zoom ){
    TTF_Font *t = TTF_OpenFont( "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Font/VNARIALB.ttf", size_text );
    text.gFont = t;
    if( text.gFont == NULL )
       {
           printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
       }
       else
       {
           //Render text
           text.color= { r, g, b };
           if( !text.loadFromRenderedText( gText, text.color, renderer ) )
           {
               printf( "Failed to render text texture!\n" );
           }
       }
    text.rect.w*=zoom;
    text.rect.h*=zoom;
    //text.rect.w=33;
     //text.rect.h=28;
    text.rect.x=x;
    text.rect.y=y;
   // cout << text.rect.x << " " << text.rect.y << " " << text.rect.w << " " << text.rect.h << endl;
    
    SDL_RenderCopy(renderer, text.texture, nullptr, &text.rect);
    //TTF_CloseFont( text.gFont );
    TTF_CloseFont( t );
          t  = nullptr;
     text.gFont  = nullptr;
   // SDL_RenderPresent(renderer);
}
void fix_Bposition_collision(Object Blue_Obs){
    Blue_Car.rect.h+=30;
    Blue_Car.rect.w-=6;
    if(Blue_Car.angle == 0){
        Blue_Car.rect.x += 3;
        SDL_RenderCopy(renderer, Blue_Car.texture, NULL, &Blue_Car.rect);
        Blue_Car.rect.x -= 3;
    } else if (Blue_Obs.rect.x > Blue_Car.rect.x) {
        if(Blue_Car.rect.y >= Blue_Obs.rect.y + CAR_WIDTH-10){
            SDL_Point t;
            Blue_Car.rect.y -=1;
            Blue_Car.rect.x += 13;
            t.x = Blue_Obs.rect.x - Blue_Car.rect.x;
            t.y =  0;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle, &t, SDL_FLIP_NONE);
            cout << "collision1" << endl;
        } else if(Blue_Car.rect.y < Blue_Obs.rect.y + CAR_WIDTH && Blue_Car.rect.y > Blue_Obs.rect.y-15){
           // SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle, nullptr, SDL_FLIP_NONE);
           // draw();
           // waitUntilKeyPressed();
            SDL_Point t;
            Blue_Car.rect.y +=13;
            Blue_Car.rect.x += 11;
            t.x = CAR_WIDTH;
            t.y = 0;
            cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle-12, &t, SDL_FLIP_NONE);
            cout << "collision2" << endl;
        } else {
            SDL_Point t;
            Blue_Car.rect.y +=20;
            Blue_Car.rect.x += 8;
            /*t.x = -Blue_Obs.rect.x + 2*Blue_Car.rect.x;
            t.y = (Blue_Obs.rect.y - Blue_Car.rect.y) > 0 ? Blue_Obs.rect.y - Blue_Car.rect.y : 0; */
            t.x = CAR_WIDTH - (Blue_Car.rect.x+CAR_WIDTH - Blue_Obs.rect.x);
            t.y = Blue_Obs.rect.y - Blue_Car.rect.y;
            cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle-12, &t, SDL_FLIP_NONE);
            cout << "collision3" << endl;
        }
    } else {
       if(Blue_Car.rect.y >= Blue_Obs.rect.y + CAR_WIDTH-10){
            SDL_Point t;
            Blue_Car.rect.y +=2;
            Blue_Car.rect.x -= 10;
            t.x = -Blue_Car.rect.x + Blue_Obs.rect.x + CAR_WIDTH-3;
            t.y = 0;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle+12, &t, SDL_FLIP_NONE);
            cout << "collision1" << endl;
        } else if(Blue_Car.rect.y < Blue_Obs.rect.y + CAR_WIDTH && Blue_Car.rect.y > Blue_Obs.rect.y-15){
            SDL_Point t;
            Blue_Car.rect.y +=13;
            Blue_Car.rect.x -= 7;
            t.x = 0;
            t.y = 0;
            cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle+12, &t, SDL_FLIP_NONE);
            cout << "collision2" << endl;
        } else {
            SDL_Point t;
            Blue_Car.rect.y +=13;
            Blue_Car.rect.x -= 3;
            t.x = -Blue_Car.rect.x+CAR_WIDTH + Blue_Obs.rect.x;
            t.y = Blue_Obs.rect.y - Blue_Car.rect.y ;
            cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle+12, &t, SDL_FLIP_NONE);
            cout << "collision3" << endl;
        }
    }
    SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle, nullptr, SDL_FLIP_NONE);
}
void fix_Rposition_collision(Object Red_Obs){
    Red_Car.rect.h+=30;
    Red_Car.rect.w-=6;
    if(Red_Car.angle == 0 && (Red_Car.rect.x == 250 -3|| Red_Car.rect.x == 340-3)){
        cout << "Collision" << endl ;
        Red_Car.rect.x += 3;
        SDL_RenderCopy(renderer, Red_Car.texture, NULL, &Red_Car.rect);
        Red_Car.rect.x -= 3;
    } else if (Red_Obs.rect.x > Red_Car.rect.x) {
        if(Red_Car.rect.y >= Red_Obs.rect.y + CAR_WIDTH-10){
            SDL_Point t;
            Red_Car.rect.y -=3;
            Red_Car.rect.x += 20;
            t.x = Red_Obs.rect.x - Red_Car.rect.x;
            t.y =  0;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle+12, &t, SDL_FLIP_NONE);
            cout << "collision1" << endl;
        } else if(Red_Car.rect.y < Red_Obs.rect.y + CAR_WIDTH && Red_Car.rect.y > Red_Obs.rect.y-10){
           // SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle, nullptr, SDL_FLIP_NONE);
           // draw();
           // waitUntilKeyPressed();
            SDL_Point t;
            Red_Car.rect.y +=13;
            Red_Car.rect.x += 9;
            t.x = CAR_WIDTH;
            t.y = 0;
            cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle+12, &t, SDL_FLIP_NONE);
            cout << "collision2" << endl;
        } else {
            SDL_Point t;
            Red_Car.rect.y +=5;
            Red_Car.rect.x += 1;
            /*t.x = -Red_Obs.rect.x + 2*Red_Car.rect.x;
            t.y = (Red_Obs.rect.y - Red_Car.rect.y) > 0 ? Red_Obs.rect.y - Red_Car.rect.y : 0; */
            t.x = CAR_WIDTH - (Red_Car.rect.x+CAR_WIDTH - Red_Obs.rect.x);
            t.y = Red_Obs.rect.y - Red_Car.rect.y;
            cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle+12, &t, SDL_FLIP_NONE);
            cout << "collision3" << endl;
        }
    } else {
       if(Red_Car.rect.y >= Red_Obs.rect.y + CAR_WIDTH-10){
            SDL_Point t;
            Red_Car.rect.y +=5;
            Red_Car.rect.x -= 16;
            t.x = -Red_Car.rect.x + Red_Obs.rect.x + CAR_WIDTH-3;
            t.y = 0;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle-12, &t, SDL_FLIP_NONE);
            cout << "collision1" << endl;
        } else if(Red_Car.rect.y < Red_Obs.rect.y + CAR_WIDTH && Red_Car.rect.y > Red_Obs.rect.y-10){
            SDL_Point t;
            Red_Car.rect.y +=13;
            Red_Car.rect.x -= 2;
            t.x = 0;
            t.y = 0;
            cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle-12, &t, SDL_FLIP_NONE);
            cout << "collision2" << endl;
        } else {
            SDL_Point t;
            Red_Car.rect.y +=12;
            Red_Car.rect.x += 3;
            t.x = -Red_Car.rect.x+CAR_WIDTH + Red_Obs.rect.x;
            t.y = Red_Obs.rect.y - Red_Car.rect.y ;
            cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle-12, &t, SDL_FLIP_NONE);
            cout << "collision3" << endl;
        }
    }
    SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle, nullptr, SDL_FLIP_NONE);
}
void Mouse_Event(SDL_Event e, int &x, int &y){
    if(e.type == SDL_MOUSEBUTTONDOWN){
        SDL_GetMouseState(&x,&y);
        cout << "Mouse: " << x << " " << y << endl;
    }
}
void draw_begin(){
    SDL_Texture* t;
    Set_Begin(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, nullptr);
    SDL_Rect red, blue;
    blue.w = 100;
    blue.h = 200;
    red.w = 100;
    red.h = 200;
    blue.x = 150;
    blue.y = 405;
    red.x = 350;
    red.y = 400;
    SDL_RenderCopy(renderer, Blue_Car.texture, nullptr, &blue);
    SDL_RenderCopy(renderer, Red_Car.texture, nullptr, &red);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(t);
}
void draw_menu(){
    SDL_Texture* t;
    Set_Menu(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, nullptr);
    SDL_Rect play = {180,350,250,250}, mute = {100,100,100,100}, unmute = {550,800,50,50}, help = {0,800,50,50};
    Set_Play(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, &play);
    t = nullptr;
    Set_Help(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, &help);
    t = nullptr;
    if(music){
        Set_Unmute(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &unmute);
        t = nullptr;
    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(t);
}

