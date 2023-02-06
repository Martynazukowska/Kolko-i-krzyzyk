#ifndef MENU_HHP
#define MENU_HHP
#include <SDL2/SDL.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "zmienne_globalne.hpp"
#include "sdl.hpp"
#include<iostream>
#include <iostream>
#include <stdio.h>

class menu
{
private:
    int cos;
public:
    void rysuj(int rozmiar);
    int sprawdz_rozmiar();
    int sprawdz_ile();
};


void menu::rysuj(int rozmiar)
{

    int szerokosc_komorki  = WIDTH/6;
    int wysokosc_komorki = HEIGHT/6;

    SDL_FRect rect;        
    rect.h = HEIGHT/6;       
    rect.w = WIDTH/6;    
    rect.x = 0;             
    rect.y = HEIGHT/3;   

    
    SDL_SetRenderDrawColor(renderer,255, 255, 0, 255);
    SDL_RenderFillRectF(renderer, &rect); 

    rect.x = szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer,153, 255, 51, 255);                      
    SDL_RenderFillRectF(renderer, &rect);              

    rect.x = 2*szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer,51, 204, 255, 255);                      
    SDL_RenderFillRectF(renderer, &rect); 

    rect.x = 3*szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer, 204, 102, 255, 255);                      
    SDL_RenderFillRectF(renderer, &rect); 

    rect.x = 4*szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer, 255, 0, 102, 255);                      
    SDL_RenderFillRectF(renderer, &rect); 

    rect.x = 5*szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer,255, 0, 0, 255);                      
    SDL_RenderFillRectF(renderer, &rect); 

    rect.y = HEIGHT*2/3;  
    rect.x = 0; 
    //drugi rzad
    SDL_SetRenderDrawColor(renderer,255, 255, 0, 255);
    SDL_RenderFillRectF(renderer, &rect); 

    rect.x = szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer,153, 255, 51, 255);                      
    SDL_RenderFillRectF(renderer, &rect);              

    rect.x = 2*szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer,51, 204, 255, 255);                      
    SDL_RenderFillRectF(renderer, &rect); 

    rect.x = 3*szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer, 204, 102, 255, 255);                      
    SDL_RenderFillRectF(renderer, &rect); 

    rect.x = 4*szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer, 255, 0, 102, 255);                      
    SDL_RenderFillRectF(renderer, &rect); 

    rect.x = 5*szerokosc_komorki;   
    SDL_SetRenderDrawColor(renderer,255, 0, 0, 255);                      
    SDL_RenderFillRectF(renderer, &rect);

    rect.x = 0;             
    rect.y = HEIGHT/3; 
    switch (rozmiar)
    {
    case 3:
        SDL_SetRenderDrawColor(renderer,255, 255, 255, 255); 
        SDL_RenderFillRectF(renderer, &rect); 
        break;
    case 4:
        rect.x = szerokosc_komorki;   
        SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);                     
        SDL_RenderFillRectF(renderer, &rect);
        break;
    case 5:
        rect.x = 2*szerokosc_komorki;  
        SDL_SetRenderDrawColor(renderer,255, 255, 255, 255); 
        SDL_RenderFillRectF(renderer, &rect); 
        break;
    case 6:
        rect.x = 3*szerokosc_komorki;  
        SDL_SetRenderDrawColor(renderer,255, 255, 255, 255); 
        SDL_RenderFillRectF(renderer, &rect); 
        break;
    case 7:
        rect.x = 4*szerokosc_komorki;  
        SDL_SetRenderDrawColor(renderer,255, 255, 255, 255); 
        SDL_RenderFillRectF(renderer, &rect); 
        break;
    case 8:
        rect.x = 5*szerokosc_komorki;  
        SDL_SetRenderDrawColor(renderer,255, 255, 255, 255); 
        SDL_RenderFillRectF(renderer, &rect); 
        break;
    
    default:
        break;
    }

            SDL_Surface* text;
            // Set color to black
            SDL_Color color = { 0, 0, 0 };

            text = TTF_RenderText_Blended( font, "3x3", color );
            if ( !text ) {
                cout << "Failed to render text: " << TTF_GetError() << endl;
            }
            SDL_Texture* text_texture;
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            int pom;
            pom =HEIGHT/6;
            SDL_Rect dest = { 30, (2*pom+25), 40, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "4x4", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 30+WIDTH/6, (2*pom+25), 45, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "5x5", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 30+WIDTH/3, (2*pom+25), 40, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "6x6", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 30+WIDTH/2, (2*pom+25), 45, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "7x7", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 30+(WIDTH*2/3), (2*pom+25), 45, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "8x8", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 30+(WIDTH*5/6), (2*pom+25), 40, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            pom =HEIGHT/3;


            text = TTF_RenderText_Blended( font, "3", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 40, (2*pom+25), 20, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "4", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 40+WIDTH/6, (2*pom+25), 20, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "5", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 40+WIDTH/3, (2*pom+25), 20, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "6", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 40+WIDTH/2, (2*pom+25), 20, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "7", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 40+(WIDTH*2/3), (2*pom+25), 20, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font, "8", color );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 40+(WIDTH*5/6), (2*pom+25), 20, 30};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            SDL_Color color2 = { 255, 255, 255 };
            
            text = TTF_RenderText_Blended( font2, "Podaj rozmiar planszy: ", color2 );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 20, (2*HEIGHT/6-40),400, 40};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font2, "Podaj ilosc wygranej w rzedzie : ", color2 );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 20, (4*HEIGHT/6-40),450, 40};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);

            text = TTF_RenderText_Blended( font2, "TIC TAC TOE ", color2 );
            text_texture = SDL_CreateTextureFromSurface( renderer, text );
            dest = { 130, 15,400, 80};
            SDL_RenderCopy( renderer, text_texture, NULL, &dest);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);


    framecount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if(timerFPS<(1000/60))
    {
        SDL_Delay((1000/60)-timerFPS);
    }

    SDL_RenderPresent(renderer);

}

/**
 *  \brief  sprawdza , który przycisk został klikniety 
 * 
 *  \return rozmiar planszy
 */
int menu::sprawdz_rozmiar() 
{ 
    int szerokosc_komorki = WIDTH/6;

    SDL_Event event;  

    while(SDL_PollEvent(&event))
    {                                    
        if(event.type == SDL_QUIT)
        {
            return 0;
        }                           
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_ESCAPE])
        {
            return 0;
        }              
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {                          
            // zakres 3x3                         
            if(event.button.x < szerokosc_komorki && event.button.x>0 && event.button.y<HEIGHT/2 && event.button.y>HEIGHT/3 )
            {
                return 3; 
            }
            // zakres 4x4 
            if(event.button.x < 2*szerokosc_komorki && event.button.x>szerokosc_komorki && event.button.y<HEIGHT/2 && event.button.y>HEIGHT/3)
            {
                return 4; 
            } 
            // zakres 5x5                        
            if(event.button.x < 3*szerokosc_komorki && event.button.x>2*szerokosc_komorki && event.button.y<HEIGHT/2 && event.button.y>HEIGHT/3)
            {
                return 5; 
            }
            // zakres 6x6 
            if(event.button.x < 4*szerokosc_komorki && event.button.x>3*szerokosc_komorki &&  event.button.y<HEIGHT/2 && event.button.y>HEIGHT/3)
            {
                return 6; 
            }
            // zakres 7x7                         
            if(event.button.x < 5*szerokosc_komorki && event.button.x>4*szerokosc_komorki && event.button.y<HEIGHT/2 && event.button.y>HEIGHT/3)
            {
                return 7; 
            }
            // zakres 8x8 
            if(event.button.x < 6*szerokosc_komorki && event.button.x>5*szerokosc_komorki && event.button.y<HEIGHT/2 && event.button.y>HEIGHT/3)
            {
                return 8; 
            }  

        }
    }
    return 1;
}

int menu::sprawdz_ile()
{
    int szerokosc_komorki = WIDTH/6;

    SDL_Event event;  

    while(SDL_PollEvent(&event))
    {                                    
        if(event.type == SDL_QUIT)
        {
            return 0;
        }                           
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_ESCAPE])
        {
            return 0;
        }  
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {             
            // zakres 3                     
            if(event.button.x < szerokosc_komorki && event.button.x>0 && event.button.y<(HEIGHT*5/6) && event.button.y>(HEIGHT*2/3) )
            {
                return 3; 
            }
            // zakres 4 
            if(event.button.x < 2*szerokosc_komorki && event.button.x>szerokosc_komorki && event.button.y<(HEIGHT*5/6) && event.button.y>(HEIGHT*2/3))
            {
                return 4; 
            } 
            // zakres 5                        
            if(event.button.x < 3*szerokosc_komorki && event.button.x>2*szerokosc_komorki && event.button.y<(HEIGHT*5/6) && event.button.y>(HEIGHT*2/3))
            {
                return 5; 
            }
            // zakres 6 
            if(event.button.x < 4*szerokosc_komorki && event.button.x>3*szerokosc_komorki &&  event.button.y<(HEIGHT*5/6 )&& event.button.y>(HEIGHT*2/3))
            {
                return 6; 
            }
            // zakres 7                         
            if(event.button.x < 5*szerokosc_komorki && event.button.x>4*szerokosc_komorki && event.button.y<(HEIGHT*5/6 )&& event.button.y>(HEIGHT*2/3))
            {
                return 7; 
            }
            // zakres 8 
            if(event.button.x < 6*szerokosc_komorki && event.button.x>5*szerokosc_komorki && event.button.y<(HEIGHT*5/6) && event.button.y>(HEIGHT*2/3))
            {
                return 8; 
            }  
       }
    }
    return 1;

}



#endif






