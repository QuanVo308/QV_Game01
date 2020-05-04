#include "Create_Object.hpp"

using namespace std;
bool die;
int score = 0;
bool quit = false;
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

int main() {
    initSDL(window, renderer);
    initIMG();
    initTTF();
    Play_Game();
    //end game
    print_text(20, 255, 255, 255, "SCORE", 20, 20, 1);
    if(die){
        waitUntilKeyPressed();
    }
    SDL_DestroyTexture(map);
    quitSDL(window, renderer);
    IMG_Quit();
    TTF_Quit();
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
void Play_Game(){
    quit = false;
    SDL_Event e;
    Set_Object();
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw();
         
        if(SDL_PollEvent(&e) == 0) continue;
        cout << score << endl;
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
    SDL_RenderCopy(renderer, map, NULL, NULL);
    SDL_RenderCopy(renderer, Red_Car.texture, NULL, &Red_Car.rect);
    SDL_RenderCopy(renderer, Blue_Car.texture, NULL, &Blue_Car.rect);
    
    for(int i =0; i < Obj_Quantity; i++){
        SDL_RenderCopy(renderer, Red_Score[i].texture, NULL, &Red_Score[i].rect);
        SDL_RenderCopy(renderer, Blue_Score[i].texture, NULL, &Blue_Score[i].rect);
        SDL_RenderCopy(renderer, Red_Obs[i].texture, NULL, &Red_Obs[i].rect);
        SDL_RenderCopy(renderer, Blue_Obs[i].texture, NULL, &Blue_Obs[i].rect);
       }
    print_text(20, 255, 255, 255, "SCORE", 420, 360, 1.5);
    SDL_RenderPresent(renderer);
}
void Object_move(bool &appearR , bool &appearB){
    for(int i =0; i < Obj_Quantity; i++){
        if( check_collision(Blue_Car.rect, Blue_Score[i].rect) ){
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
        if( check_collision(Blue_Car.rect, Blue_Obs[i].rect) ){
            Blue_Obs[i].run = false;
            die = true;
            quit = true;
            if(Blue_Car.rect.x != Blue_Obs[i].rect.x && Blue_Obs[i].rect.x == 150){
                Blue_Car.rect.x = Blue_Obs[i].rect.x - CAR_WIDTH+2;
            } else if(Blue_Car.rect.x != Blue_Obs[i].rect.x && Blue_Obs[i].rect.x == 55){
                Blue_Car.rect.x = Blue_Obs[i].rect.x + CAR_WIDTH-3;
            }
        }
        if( check_collision(Red_Car.rect, Red_Obs[i].rect) ){
            Red_Obs[i].run = false;
            die = true;
            quit = true;
            if(Red_Car.rect.x != Red_Obs[i].rect.x && Red_Obs[i].rect.x == 340){
                Red_Car.rect.x = Red_Obs[i].rect.x - CAR_WIDTH+5;
            } else if(Red_Car.rect.x != Red_Obs[i].rect.x && Red_Obs[i].rect.x == 250){
                Red_Car.rect.x = Red_Obs[i].rect.x + CAR_WIDTH-3;
            }
        }
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
    text.gFont = TTF_OpenFont( "/Users/QuanVo/Documents/Xcode/QV_Game01/QV_Game01/Font/VNARIALB.ttf", size_text );
    if( text.gFont == NULL )
       {
           printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
       }
       else
       {
           //Render text
           text.color= { r, g, b };
           if( text.loadFromRenderedText( gText, text.color, renderer ) )
           {
               printf( "Failed to render text texture!\n" );
           }
       }
    text.rect.w*=zoom;
    text.rect.h*=zoom;
    text.rect.x=x;
    text.rect.y=y;
    SDL_RenderCopy(renderer, text.texture, nullptr, &text.rect);
   // SDL_RenderPresent(renderer);
}
