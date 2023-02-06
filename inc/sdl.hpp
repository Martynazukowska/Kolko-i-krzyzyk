#ifndef SDL_HHP
#define SDL_HHP
#include <SDL2/SDL.h>    
 
#include <SDL_ttf.h>
#include "zmienne_globalne.hpp"

SDL_Renderer* renderer;
SDL_Window* window;
TTF_Font* font;
TTF_Font* font2;
SDL_Surface* surface = nullptr;


bool fullscreen, running;
bool tak_nie = true; 
bool build_menu=true;
bool build_menu2=true;
bool jeszcze_raz = true; //wyświetlanie czy chcesz jeszcze raz

// zmienne do wyrownywania ilosci klatek na sekunde
int framecount, timerFPS, lastFrame, fps, lastTime = 0;


// ta funkcja nie dziala dopoki nie zmienimy flagi przy tworzeniu okienka na SDL_WINDOW_RESIZABLE
void update() 
{     
    if(fullscreen){SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);}
    if(!fullscreen){SDL_SetWindowFullscreen(window, 0);}
}

/**
 *  \brief  rysuje w okienku lewa polowe zielona, a prawa czerwona
 */
void drawZielono(){
    int szerokosc_komorki = WIDTH/2; 

    SDL_FRect rect;        
    rect.h = HEIGHT;       
    rect.w = szerokosc_komorki;    
    rect.x = 0;             
    rect.y = 0;            

    //rysujemy ziemony prostokat
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  
    SDL_RenderFillRectF(renderer, &rect);              

    //czerwony prostokat
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  
    rect.x = szerokosc_komorki;                        
    SDL_RenderFillRectF(renderer, &rect);              

    // wyrownanie ilosci klatek na sekunde
    framecount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if(timerFPS<(1000/60))
    {
        SDL_Delay((1000/60)-timerFPS);
    }

    //to co mamy
    SDL_RenderPresent(renderer);  
}

/**
 *  \brief  sprawdza czy w danym okienku zostala kliknieta jego lewa czy prawa strona
 * 
 *  \return kiedy kliknieto lewa strone -> 1, prawa -> 2, klawisz esc -> 2, kiedy nie kliknieto nic -> 3
 */
int inputTak_Nie() 
{ 
    int szerokosc_komorki = WIDTH/2;

    SDL_Event event;                          
    while(SDL_PollEvent(&event))
    {                                     
        if(event.type == SDL_QUIT)
        {
            return 2;
        }                           
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_ESCAPE])
        {
            return 2;
        }              
        
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {                             
            // kiedy klikniemy na zielone                         
            if(event.button.x < szerokosc_komorki)
            {
                return 1; 
            } 
            //kiedy klikniemy na czerwone
            else                       
            {
                return 2; 
            } 
        }
    }
    return 3;
}


#endif