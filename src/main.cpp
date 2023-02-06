#include "SDL2/SDL.h"  
#include "SDL_ttf.h"       
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>

#include "../inc/plansza.hpp"
#include "../inc/menu.hpp"

using namespace std;

int main( int argc, char* args[])
{
    system("clear");

    int rozmiar, ile_w_rzedzie;
    int x, y;

    int czyj_ruch = 10;    
    // 10 = krzyzyk 
    // -10 = kolko    

    bool czy_ruch_sie_wykonal;

    // inicjalizacja SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){cout << "Blad przy SDL_Init" << endl;} 
    if(TTF_Init() < 0){cout << "Blad przy TTF_INIT" << endl;} 


    menu Menu;

    while(jeszcze_raz == true) //zmienna zainicjowana w sdl.hpp (graj jeszcze raz = true / wyjdz false)
    {
        tak_nie = true;         // zmienna decydujaca o wyswietlaniu sie okna do ponownego sprobowania

        build_menu=true;
        build_menu2=true;

        ile_w_rzedzie;
        rozmiar;
        ile_w_rzedzie=-1;
        rozmiar=-1;

            running = 1;
            fullscreen = 0;
            if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
            {
                cout << "Blad przy SDL_CreateWindowAndRenderer()" << endl;
            } 
            SDL_SetWindowTitle(window, "tic tac toe");
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

            surface=SDL_GetWindowSurface(window);
            font = TTF_OpenFont("../scpreg.ttf", 100);
            if ( !font ) {
                cout << "Failed to load font: " << TTF_GetError() << endl;
            }
            font2 = TTF_OpenFont("../Bazgroly.ttf", 100);
            if ( !font ) {
                cout << "Failed to load font: " << TTF_GetError() << endl;
            }



        int x;
        x=0;
        while(build_menu)
        {
            
            Menu.rysuj(0); 
                                            
            SDL_SetWindowTitle(window, "Menu");
            x = Menu.sprawdz_rozmiar();
             rozmiar=x;

            if(x < 3 || x > 8)
            {
                build_menu = true;
            }
            if(x>2 && x<9)
            {
 
                build_menu = false;
                Menu.rysuj(rozmiar); 
                SDL_Delay(1000);
            }
        }

        
        //czarny
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   
        //całe na czerwono
        SDL_RenderClear(renderer); 

        if(build_menu==false)
        {
            while(build_menu2)
            {
                SDL_SetWindowTitle(window, "Menu");
                Menu.rysuj(rozmiar); 
                int y;
                y = Menu.sprawdz_ile();
                while(y!=1)
                {
                    if(y<=rozmiar)
                    {
                        ile_w_rzedzie=y;
                        break;
                    }
                    else
                    {
                        break;
                    }

                }
                if(ile_w_rzedzie < 3 || ile_w_rzedzie > 8)
                {
                    build_menu2 = true;
                }
                if(ile_w_rzedzie>2 && ile_w_rzedzie<9)
                {
                    build_menu2 = false;
                }
            }
        }


        //czarny
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   
        //całe na czerwono
        SDL_RenderClear(renderer); 

       // ile_w_rzedzie=3;
        
        plansza board(rozmiar, ile_w_rzedzie); 
        board.WypiszPlansze();


        cout << endl << endl;
        cout << "rozmiar planszy to:  " << board.getrozmiar() << "x" << board.getrozmiar() << endl; 
        cout << endl << endl;

        cout << "w rzedzie" << ile_w_rzedzie;


        if(build_menu2==false)
        {
            board.draw(50, 50, 200); 


            while(running)
            {
                // wyrownanie klatek na sekunde
                lastFrame = SDL_GetTicks();

                if(lastFrame >= (lastFrame + 1000))
                {
                    lastTime = lastFrame; fps = framecount; framecount = 0;
                }

                update();

                board.draw(40, 43, 200);  


                if(czyj_ruch == 10)
                {  
                    //wstawianie X
                    czy_ruch_sie_wykonal = board.input(czyj_ruch); 
                }

                if(czyj_ruch == -10)
                { 
                    //Sztuczna inteligencja - zwraca tablice tab[2]
                    int* ruch = board.najlepszyRuch(czyj_ruch*(-1));

                    x = ruch[0];
                    y = ruch[1];

                    //wstawianie O
                    czy_ruch_sie_wykonal = board.ruch(czyj_ruch, x, y); 
                    
                    board.draw_O( x, y);                                
                    
                }

                //Kiedy ktoś wygrał
                if(board.czy_ktos_wygral(czyj_ruch) == true)  
                { 
                    system("clear");   
                    board.WypiszPlansze(); 

                    if(czyj_ruch == 10)
                    {
                        cout << "X Wygrał" << endl << endl; 
                        SDL_SetWindowTitle(window, "X Wygrał"); 
                        board.draw(255, 0, 0);
                    } 
                    else              
                    {
                        cout << "O Wygrał" << endl << endl; 
                        SDL_SetWindowTitle(window, "O Wygrał"); 
                        board.draw(0, 255, 0);
                    }
                    //stop tej gry
                    running = 0;  
                }

                //Kiedy Remmis
                if(board.czyRemis() == true)
                { 
                    system("clear");                    
                    board.WypiszPlansze();                
                    board.draw(255, 255, 0);             
                    SDL_SetWindowTitle(window, "REMIS"); 
                    cout << "REMIS" << endl;

                    //stop tej gry
                    running = 0;           
                }
                if(czy_ruch_sie_wykonal == true)
                {   
                    if(board.czyRemis() != true && board.czy_ktos_wygral(czyj_ruch) != true) 
                    {
                        system("clear"); board.WypiszPlansze(); 
                    } 
                    //zmiana z X na O lub z O na X
                    czyj_ruch = czyj_ruch * (-1);  
                }

            } 
            SDL_Delay(2000);         
            
            
            int pomocnicza = -1;
            

            while(tak_nie)
            {
                //czarny
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   
                //całe na czerwono
                SDL_RenderClear(renderer);    
                //polowa na zielono              
                drawZielono();                                   

                SDL_SetWindowTitle(window, "Czy chcesz kontynuowac?  T / N");

                pomocnicza = inputTak_Nie();

                if(pomocnicza <1 || pomocnicza>2)
                {
                    tak_nie = true;
                }

                //gdy klikniemy na czerwone
                else if(pomocnicza == 2)
                {
                    tak_nie = false; 
                    jeszcze_raz = false; 
                    cout << endl;
                }  
                //gdy klikniemy na zielone
                else if(pomocnicza == 1)
                {
                    tak_nie = false; 
                    jeszcze_raz = true; 
                    SDL_DestroyRenderer(renderer); 
                    SDL_DestroyWindow(window); 
                    czyj_ruch = 10;
                } 
            }

        } 
        TTF_CloseFont( font );
    }     
        TTF_Quit();
        SDL_Quit();                   
    
    return 0;
}