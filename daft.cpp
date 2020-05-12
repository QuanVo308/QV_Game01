
/*while(!pause){
       //pause
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
   while (!quit){
     while(!pause){
           //pause
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
    //pause menu
   }*/
/*
 #include <iostream>
 #include "SetSDL.hpp"
 SDL_Window* window = nullptr;
 SDL_Renderer* renderer = nullptr;
 int main() {
     SDL_Rect t;
     initSDL(window, renderer);
     SDL_SetRenderDrawColor(renderer, 255,0, 0, 255);
     t.x = SCREEN_WIDTH/4;
     t.y = SCREEN_HEIGHT/4;
     t.w = SCREEN_WIDTH/2;
     t.h = SCREEN_HEIGHT/2;
     SDL_RenderFillRect(renderer, &t);
     SDL_SetRenderDrawColor(renderer, 0,0, 0, 50);
     
     t.x = 0;
     t.y = 0;
     t.w = SCREEN_WIDTH/2;
     t.h = SCREEN_HEIGHT/2;
     SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
     SDL_RenderFillRect(renderer, &t);
     SDL_RenderPresent(renderer);
     waitUntilKeyPressed();
     quitSDL(window, renderer);
 }

 */
