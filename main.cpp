#include "Create_Object.hpp"

using namespace std;

enum Button{
    PLAYAGAIN,
    PLAY,
    MUSIC,
    SOUND,
    HELP,
    HOME,
    QUITGAME,
    BACK,
    PAUSE,
    NOTHING,
};
Button button;
bool die, chose;
int score = 0, mouse_x, mouse_y, highscore = 1000;
bool quit = false;
bool quitgame = false, pause = false;
bool music = true;
bool sound = true;
Object Blue_Score[Obj_Quantity], Red_Score[Obj_Quantity];
Object Blue_Obs[Obj_Quantity], Red_Obs[Obj_Quantity];
Car Blue_Car(RB_Line,Car_y), Red_Car(LR_Line,Car_y);
SDL_Texture* map = nullptr;
Text text;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect  Rmute = {390,660,100,100},Rhelp = {110,660,100,100}, RSound = {260,660,100,100}, RQuitGame = {20,20, 40, 40}, RBack = {240, 660, 100, 100};
Mix_Chunk *lose = nullptr, *click = nullptr, *Hit_Score = nullptr;
Mix_Music *background = nullptr;

int Random(int a, int b);
void Set_Rect(SDL_Rect &rect, int x, int y, int w, int h);
void Play_Game();
void KEY_FREEMOVE_ACTION( SDL_Event &e, bool &quit, bool &l, bool &r, bool &u, bool &dw, bool &s, bool &a, bool &d, bool &w);
void draw();
void draw_without_present();
void Object_move(bool &appearR , bool &appearB);
void Car_move(SDL_Event &e);
bool check_collision(SDL_Rect a, SDL_Rect b);
void Set_Object();
void print_text(int size_text, Uint8 r, Uint8 g, Uint8 b , string gText, int x, int y, double zoom );
void fix_Bposition_collision(Object Blue_Obs);
void fix_Rposition_collision(Object Red_Obs);
void Mouse_Event(SDL_Event e);
void draw_tutorial();
void check_click_basic_button();
void draw_menu_basic_option();
void draw_begin();
void draw_menu();
void draw_menu_pause();
void draw_menu_lose();
bool check_click_mouse(SDL_Rect s);
void quit_mixer();
void quitObj();
void Set_mixer();
void click_sound();
void hit_score_sound();
void lose_sound();
void set_highscore();
int get_highscore();

int main() {
    initSDL(window, renderer);
    initIMG();
    initTTF();
    init_mixer();
    Set_Object();
    Set_mixer();
    draw_begin();
    Mix_PlayMusic( background, -1 );
    waitUntilKeyPressed();
    while(!quitgame){
        draw_menu();
        switch(button){
            case PLAY:
                die = false;
                quit = false;
                Play_Game();
                break;
            case QUITGAME:
                quitgame = true;
                break;
            default: break;
        }
    }
    
    //end game
    text.Destroy();
    SDL_DestroyTexture(map);
    quitObj();
    quitSDL(window, renderer);
    quit_mixer();
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
    Set_Object();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw();
    SDL_RenderPresent(renderer);
    score = 0;
    while(!quit && !quitgame){
        while(button != PAUSE && !quit && !quitgame){
            bool appearRS = true, appearBS = true;
                if(e.type == SDL_QUIT){
                    quit = true;
                }
                Car_move(e);
                Object_move(appearRS ,appearBS);
                SDL_Delay(10);
                draw();
                if(SDL_PollEvent(&e) == 0) continue;
                cout << "Score: " << score << endl;
        }
        if(button == PAUSE){
            button = NOTHING;
            draw_menu_pause();
        }
        if(die){
            waitUntilKeyPressed();
            draw_menu_lose();
        }
    }
    if(die) {
        Set_Object();
    }
}
void quit_mixer(){
    Mix_FreeChunk( lose);
    Mix_FreeChunk( Hit_Score );
    Mix_FreeChunk( click );
    lose = NULL;
    Hit_Score = NULL;
    click = NULL;
    Mix_FreeMusic( background );
    background = NULL;
    Mix_Quit();
}
void quitObj(){
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
            case SDLK_p: button = PAUSE; break;
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
           // case SDLK_p: button = PAUSE; break;
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
    SDL_RenderCopy(renderer, map, NULL, NULL);
}
void draw_without_present(){
    SDL_RenderCopy(renderer, map, NULL, NULL);
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
}
void Object_move(bool &appearR , bool &appearB){
    for(int i =0; i < Obj_Quantity; i++){
        if( SDL_HasIntersection(&Blue_Car.rect, &Blue_Score[i].rect) ){
            hit_score_sound();
            Blue_Score[i].rect.y = SCREEN_HEIGHT;
            Blue_Score[i].run = false;
            score++;
        }
        if( check_collision(Red_Car.rect, Red_Score[i].rect) ){
            hit_score_sound();
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
        // Blue car collision
        Blue_Car.rect.x-=3;
        Blue_Car.rect.h-=30;
        Blue_Car.rect.w+=6;
        if( SDL_HasIntersection(&Blue_Car.rect, &Blue_Obs[i].rect) ){
            lose_sound();
            Blue_Obs[i].run = false;
            die = true;
            quit = true;
            fix_Bposition_collision(Blue_Obs[i]);
        } else {
            Blue_Car.rect.h+=30;
            Blue_Car.rect.w-=6;
        }
        Blue_Car.rect.x+=3;
        // Red car collision
        Red_Car.rect.x-=3;
        Red_Car.rect.h-=30;
        Red_Car.rect.w+=6;
        if( SDL_HasIntersection(&Red_Car.rect, &Red_Obs[i].rect) ){
            lose_sound();
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
                        Red_Score[i].rect.x = Random(1,300)%2==0  ? LR_Line : RR_Line;
                        Red_Score[i].rect.y = 0;
                    }
                    break;
                }
            } else {
                if( Red_Obs[i].run==false){
                    if(Random(1,100)%10 == 3){
                        Red_Obs[i].run =true;
                        Red_Obs[i].rect.x = Random(1,300)%2==0  ? LR_Line : RR_Line;
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
                        Blue_Score[i].rect.x = Random(1,300)%2==0  ? LB_Line : RB_Line;
                        Blue_Score[i].rect.y = 0;
                    }
                    break;
                }
            } else {
                if( Blue_Obs[i].run==false){
                    if(Random(1,100)%10 == 7){
                        Blue_Obs[i].run =true;
                        Blue_Obs[i].rect.x = Random(1,300)%2==0  ? LB_Line : RB_Line;
                        Blue_Obs[i].rect.y = 0;
                    }
                    break;
                }
            }
        }
    }
}

void Car_move(SDL_Event &e){
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
        if(dw_check_right == 1 && Red_Car.rect.x <RR_Line){
            Red_Car.rect.x += Car_x_Change;
            if(Red_Car.angle <=45 && Red_Car.rect.x <= (RR_Line+LR_Line)/2){
                Red_Car.angle +=Car_Angle_Change;
            } else {
                Red_Car.angle -=Car_Angle_Change;
            }
            if(Red_Car.rect.x >=RR_Line){
                Red_Car.rect.x = RR_Line;
                Red_Car.angle =0;
            }
        } else if( Red_Car.rect.x > LR_Line && dw_check_right == -1) {
            Red_Car.rect.x -= Car_x_Change;
            if(Red_Car.angle >=-45 && Red_Car.rect.x >= (RR_Line+LR_Line)/2){
                Red_Car.angle -=Car_Angle_Change;
            } else {
                Red_Car.angle +=Car_Angle_Change;
            }
            if(Red_Car.rect.x <=LR_Line){
                Red_Car.rect.x = LR_Line;
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
        if(s_check_right == 1 && Blue_Car.rect.x <RB_Line){
            Blue_Car.rect.x += Car_x_Change;
            if(Blue_Car.angle <=45 && Blue_Car.rect.x < (LB_Line+RB_Line)/2){
                Blue_Car.angle +=Car_Angle_Change;
            } else {
                Blue_Car.angle -=Car_Angle_Change;
            }
            if(Blue_Car.rect.x >=RB_Line){
                Blue_Car.rect.x = RB_Line;
                Blue_Car.angle =0;
            }
            //cout << Blue_Car.angle << endl;
        } else if( Blue_Car.rect.x > LB_Line && s_check_right == -1) {
            Blue_Car.rect.x -= Car_x_Change;
            if(Blue_Car.angle >=-45 && Blue_Car.rect.x > (LB_Line+RB_Line)/2){
                Blue_Car.angle -=Car_Angle_Change;
            } else {
                Blue_Car.angle +=Car_Angle_Change;
            }

            if(Blue_Car.rect.x <=LB_Line){
                Blue_Car.rect.x = LB_Line;
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
    Blue_Car.rect.y = Car_y;
    Red_Car.rect.y = Car_y;
    Set_Classic_Map(map, renderer);
    for(int i=0;i < Obj_Quantity; i++){
        Set_Blue_Score(Blue_Score[i].texture, renderer);
        Set_Red_Score(Red_Score[i].texture, renderer);
        Set_Blue_Obs(Blue_Obs[i].texture, renderer);
        Set_Red_Obs(Red_Obs[i].texture, renderer);
    }
    for(int i =0; i < Obj_Quantity; i++){
        Set_Rect(Red_Score[i].rect, LR_Line, SCREEN_HEIGHT, CAR_WIDTH, CAR_WIDTH);  // x1 250 x2 340
        Set_Rect(Blue_Score[i].rect, LB_Line, SCREEN_HEIGHT, CAR_WIDTH, CAR_WIDTH); //  x1 55  x2 150
        Set_Rect(Red_Obs[i].rect, LR_Line, SCREEN_HEIGHT, CAR_WIDTH, CAR_WIDTH);  // x1 250 x2 340
        Set_Rect(Blue_Obs[i].rect, LB_Line, SCREEN_HEIGHT, CAR_WIDTH, CAR_WIDTH); //  x1 55  x2 150
    }
}
void print_text(int size_text, Uint8 r, Uint8 g, Uint8 b , string gText, int x, int y, double zoom ){
    TTF_Font *t = TTF_OpenFont( TFFfont.c_str(), size_text );
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
    text.rect.x=x;
    text.rect.y=y;
    SDL_RenderCopy(renderer, text.texture, nullptr, &text.rect);
    TTF_CloseFont( t );
    t  = nullptr;
    text.gFont  = nullptr;
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
            cout << "collision1r" << endl;
        } else if(Blue_Car.rect.y < Blue_Obs.rect.y + CAR_WIDTH && Blue_Car.rect.y > Blue_Obs.rect.y-15){
            SDL_Point t;
            Blue_Car.rect.y +=13;
            Blue_Car.rect.x += 11;
            t.x = CAR_WIDTH;
            t.y = 0;
           // cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle-Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision2r" << endl;
        } else {
            SDL_Point t;
            Blue_Car.rect.y +=20;
            Blue_Car.rect.x += 8;
            t.x = CAR_WIDTH - (Blue_Car.rect.x+CAR_WIDTH - Blue_Obs.rect.x);
            t.y = Blue_Obs.rect.y - Blue_Car.rect.y;
            //cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle-Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision3r" << endl;
        }
    } else {
       if(Blue_Car.rect.y >= Blue_Obs.rect.y + CAR_WIDTH-10){
            SDL_Point t;
            Blue_Car.rect.y +=2;
            Blue_Car.rect.x -= 10;
            t.x = -Blue_Car.rect.x + Blue_Obs.rect.x + CAR_WIDTH-3;
            t.y = 0;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle+Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision1" << endl;
        } else if(Blue_Car.rect.y < Blue_Obs.rect.y + CAR_WIDTH && Blue_Car.rect.y > Blue_Obs.rect.y-15){
            SDL_Point t;
            Blue_Car.rect.y +=13;
            Blue_Car.rect.x -= 7;
            t.x = 0;
            t.y = 0;
            //cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle+Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision2" << endl;
        } else {
            SDL_Point t;
            Blue_Car.rect.y +=13;
            Blue_Car.rect.x -= 3;
            t.x = -Blue_Car.rect.x+CAR_WIDTH + Blue_Obs.rect.x;
            t.y = Blue_Obs.rect.y - Blue_Car.rect.y ;
            //cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle+Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision3" << endl;
        }
    }
    SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle, nullptr, SDL_FLIP_NONE);
}
void fix_Rposition_collision(Object Red_Obs){
    Red_Car.rect.h+=30;
    Red_Car.rect.w-=6;
    if(Red_Car.angle == 0 && (Red_Car.rect.x == LR_Line -3|| Red_Car.rect.x == RR_Line-3)){
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
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle-Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision1r" << endl;
        } else if(Red_Car.rect.y < Red_Obs.rect.y + CAR_WIDTH && Red_Car.rect.y > Red_Obs.rect.y-10){
            SDL_Point t;
            Red_Car.rect.y +=13;
            Red_Car.rect.x += 9;
            t.x = CAR_WIDTH;
            t.y = 0;
            //cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle-Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision2r" << endl;
        } else {
            SDL_Point t;
            Red_Car.rect.y +=5;
            Red_Car.rect.x += 1;
            t.x = CAR_WIDTH - (Red_Car.rect.x+CAR_WIDTH - Red_Obs.rect.x);
            t.y = Red_Obs.rect.y - Red_Car.rect.y;
           // cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle-Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision3r" << endl;
        }
    } else {
       if(Red_Car.rect.y >= Red_Obs.rect.y + CAR_WIDTH-10){
            SDL_Point t;
            Red_Car.rect.y +=5;
            Red_Car.rect.x -= 16;
            t.x = -Red_Car.rect.x + Red_Obs.rect.x + CAR_WIDTH-3;
            t.y = 0;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle+Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision1" << endl;
        } else if(Red_Car.rect.y < Red_Obs.rect.y + CAR_WIDTH && Red_Car.rect.y > Red_Obs.rect.y-10){
            SDL_Point t;
            Red_Car.rect.y +=13;
            Red_Car.rect.x -= 2;
            t.x = 0;
            t.y = 0;
            //cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle+Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision2" << endl;
        } else {
            SDL_Point t;
            Red_Car.rect.y +=12;
            Red_Car.rect.x += 3;
            t.x = -Red_Car.rect.x+CAR_WIDTH + Red_Obs.rect.x;
            t.y = Red_Obs.rect.y - Red_Car.rect.y ;
            //cout << t.x << " " << t.y << endl;
            SDL_RenderCopyEx(renderer, Red_Car.texture, NULL, &Red_Car.rect, Red_Car.angle+Car_Angle_Change, &t, SDL_FLIP_NONE);
            cout << "collision3" << endl;
        }
    }
    SDL_RenderCopyEx(renderer, Blue_Car.texture, NULL, &Blue_Car.rect, Blue_Car.angle, nullptr, SDL_FLIP_NONE);
}
void Mouse_Event(SDL_Event e){
    bool check = false;
    mouse_x = 0;
    mouse_y = 0;
    while(!check){
        if(SDL_WaitEvent(&e)){
            if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_QUIT){
            mouse_x = e.motion.x;
            mouse_y = e.motion.y;
              check = true;
                 cout << "Mouse: " << mouse_x << " " << mouse_y << endl;
            }
            }
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
    SDL_Rect s;
    SDL_Event e;
    chose = false;
    Set_Classic_Map(t, renderer);
    SDL_RenderCopy(renderer, t, NULL, NULL);
    SDL_RenderCopy(renderer, Red_Car.texture, NULL, &Red_Car.rect);
    SDL_RenderCopy(renderer, Blue_Car.texture, NULL, &Blue_Car.rect);
    s.x = 0;
    s.y = 0;
    s.w = SCREEN_WIDTH;
    s.h = SCREEN_HEIGHT;
    SDL_SetRenderDrawColor(renderer, 0,0, 0, 140);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &s);
    SDL_Rect play = {180,250,250,250};
    Set_Play(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, &play);
    SDL_DestroyTexture(t);
    draw_menu_basic_option();
    print_text(20, 255, 255, 255, "HIGHSCORE:", 155, 140, 2);
    print_text(20, 255, 255, 255, to_string(get_highscore()), 415, 140, 2);
    SDL_RenderPresent(renderer);
    while(chose != true){
        button = NOTHING;
        chose = false;
        Mouse_Event(e);
        if(check_click_mouse(play)){
            click_sound();
            chose = true;
            button = PLAY;
        }
        Set_Classic_Map(t, renderer);
        SDL_RenderCopy(renderer, t, NULL, NULL);
        SDL_RenderCopy(renderer, Red_Car.texture, NULL, &Red_Car.rect);
        SDL_RenderCopy(renderer, Blue_Car.texture, NULL, &Blue_Car.rect);
        SDL_SetRenderDrawColor(renderer, 0,0, 0, 140);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(renderer, &s);
        SDL_Rect play = {180,250,250,250};
        Set_Play(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &play);
        SDL_DestroyTexture(t);
    
        check_click_basic_button();
        draw_menu_basic_option();
        print_text(20, 255, 255, 255, "HIGHSCORE:", 155, 140, 2);
        print_text(20, 255, 255, 255, to_string(get_highscore()), 415, 140, 2);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(t);
    SDL_RenderClear(renderer);
}
void draw_menu_pause(){
    SDL_Texture* t;
    SDL_Rect s;
    SDL_Event e;
    s.x = 0;
    s.y = 0;
    s.w = SCREEN_WIDTH;
    s.h = SCREEN_HEIGHT;
    draw_without_present();
    SDL_SetRenderDrawColor(renderer, 0,0, 0, 140);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &s);
    SDL_Rect playagain = {205,430,200,200}, play = {205,200,200,200};
    Set_Playagain(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, &playagain);
    SDL_DestroyTexture(t);
    Set_Play(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, &play);
    SDL_DestroyTexture(t);
    draw_menu_basic_option();
    SDL_RenderPresent(renderer);
    chose = false;
    while(chose != true){
        button = NOTHING;
        Mouse_Event(e);
        if(check_click_mouse(play)){
            click_sound();
            chose = true;
            quit = false;
        }
        if(check_click_mouse(playagain)){
            if(score > get_highscore()){
                set_highscore();
            }
            click_sound();
            chose = true;
            Set_Object();
            score = 0;
        }
        draw_without_present();
        SDL_SetRenderDrawColor(renderer, 0,0, 0, 140);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(renderer, &s);
        SDL_Rect playagain = {205,430,200,200}, play = {205,200,200,200};
        Set_Playagain(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &playagain);
        SDL_DestroyTexture(t);
        Set_Play(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &play);
        SDL_DestroyTexture(t);
        check_click_basic_button();
        draw_menu_basic_option();
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyTexture(t);
    SDL_RenderClear(renderer);
}
void draw_menu_lose(){
    SDL_Texture* t;
    SDL_Rect s;
    SDL_Event e;
    s.x = 0;
    s.y = 0;
    s.w = SCREEN_WIDTH;
    s.h = SCREEN_HEIGHT;
    draw_without_present();
    SDL_SetRenderDrawColor(renderer, 0,0, 0, 140);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &s);
    SDL_Rect playagain = {205,430,200,200}, home = {205,200,200,200};
    Set_Playagain(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, &playagain);
    SDL_DestroyTexture(t);
    Set_Home(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, &home);
    SDL_DestroyTexture(t);
    draw_menu_basic_option();
    if(score <= get_highscore()){
        print_text(20, 255, 255, 255, "SCORE:", 205, 110, 2);
        print_text(20, 255, 255, 255, to_string(score), 365, 110, 2);
        print_text(20, 255, 255, 255, "HIGHSCORE:", 220, 160, 1);
        print_text(20, 255, 255, 255, to_string(get_highscore()), 350, 160, 1);
    } else {
        print_text(20, 255, 255, 255, "HIGHSCORE:", 155, 120, 2);
        print_text(20, 255, 255, 255, to_string(score), 415, 120, 2);
    }
    SDL_RenderPresent(renderer);
    chose = false;
    while(chose != true){
        button = NOTHING;
        Mouse_Event(e);
        if(check_click_mouse(home)){
            click_sound();
            chose = true;
            quit = true;
        }
        if(check_click_mouse(playagain)){
            click_sound();
            quit = false;
            die = false;
            quitgame = false;
            chose = true;
            Set_Object();
            score = 0;
        }
        draw_without_present();
        SDL_SetRenderDrawColor(renderer, 0,0, 0, 140);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(renderer, &s);
        SDL_Rect playagain = {205,430,200,200}, home = {205,200,200,200};
        Set_Playagain(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &playagain);
        SDL_DestroyTexture(t);
        Set_Home(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &home);
        SDL_DestroyTexture(t);
        check_click_basic_button();
        draw_menu_basic_option();
        if(score <= get_highscore()){
            print_text(20, 255, 255, 255, "SCORE:", 205, 120, 2);
            print_text(20, 255, 255, 255, to_string(score), 365, 120, 2);
            print_text(20, 255, 255, 255, "HIGHSCORE:", 220, 160, 1);
            print_text(20, 255, 255, 255, to_string(get_highscore()), 350, 160, 1);
        } else {
            print_text(20, 255, 255, 255, "HIGHSCORE:", 155, 120, 2);
            print_text(20, 255, 255, 255, to_string(score), 415, 120, 2);
        }
        SDL_RenderPresent(renderer);
    }
    if(score > get_highscore()){
        set_highscore();
    }
    SDL_DestroyTexture(t);
    SDL_RenderClear(renderer);
}
void draw_menu_basic_option(){
    SDL_Texture* t;
    if(music){
        Set_Musicon(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &Rmute);
        SDL_DestroyTexture(t);
    } else {
        Set_Musicoff(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &Rmute);
        SDL_DestroyTexture(t);
    }
    if(sound){
        Set_Unmute(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &RSound);
        SDL_DestroyTexture(t);
    } else {
        Set_Mute(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &RSound);
        SDL_DestroyTexture(t);
    }
    Set_Help(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, &Rhelp);
    SDL_DestroyTexture(t);
    Set_Quitgame(t, renderer);
    SDL_RenderCopy(renderer, t, nullptr, &RQuitGame);
    SDL_DestroyTexture(t);
}
bool check_click_mouse(SDL_Rect s){
    if(s.x > mouse_x){
        return false;
    }
    if(s.x + s.w < mouse_x){
        return false;
    }
    if(s.y > mouse_y){
        return false;
    }
    if(s.y + s.h < mouse_y){
        return false;
    }
    return true;
}
void check_click_basic_button(){
    if(check_click_mouse(Rmute)){
        //music = music == true? false : true;
        if(music == true){
            music = false;
            click_sound();
            Mix_PauseMusic();
        } else {
            music = true;
            click_sound();
            Mix_ResumeMusic();
        }
    }
    if(check_click_mouse(RSound)){
        sound = sound == true? false : true;
        click_sound();
    }
    if(check_click_mouse(Rhelp)){
        click_sound();
        draw_tutorial();
        click_sound();
    }
    if(check_click_mouse(RQuitGame)){
        click_sound();
        chose = true;
        quitgame = true;
    }
}
void draw_tutorial(){
    SDL_Texture* t;
    SDL_Event e;
    SDL_Rect s;
    s.x = 0;
    s.y = 0;
    s.w = SCREEN_WIDTH;
    s.h = SCREEN_HEIGHT;
    while(button != BACK){
        button = NOTHING;
        draw_without_present();
        SDL_SetRenderDrawColor(renderer, 0,0, 0, 140);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(renderer, &s);
        Set_Tutorial(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, nullptr);
        SDL_DestroyTexture(t);
        Set_Back(t, renderer);
        SDL_RenderCopy(renderer, t, nullptr, &RBack);
        SDL_DestroyTexture(t);
        SDL_RenderPresent(renderer);
        if(button!=BACK) Mouse_Event(e);
        if(check_click_mouse(RBack)){
            button = BACK;
        }
    }
}
void Set_mixer(){
    Set_Click(click);
    Set_Hit_Score(Hit_Score);
    Set_Background(background);
    Set_Lose(lose);
}
void click_sound(){
    if(sound == true){
        Mix_PlayChannel( -1, click, 0 );
    }
}
void hit_score_sound(){
    if(sound == true){
        Mix_PlayChannel( -1, Hit_Score, 0 );
    }
}
void lose_sound(){
    if(sound == true){
        Mix_PlayChannel( -1, lose, 0 );
    }
}
int get_highscore(){
    int n;
    fstream a;
    a.open(Highscore, ios::in);
    if(!a.is_open()){
        cout << "Couldn't open Highscore.txt" << endl;
    }
    a >> n;
    a.close();
    return n;
}
void set_highscore(){
    fstream a;
    a.open(Highscore, ios::out);
    if(!a.is_open()){
        cout << "Couldn't open Highscore.txt" << endl;
    }
    a << score;
    a.close();
}

