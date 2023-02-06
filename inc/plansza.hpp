#ifndef PLANSZA_HHP
#define PLANSZA_HHP

#include <iostream>
#include <vector>

#include <random>
#include <algorithm>

#include <random>
#include <algorithm>
#include "sdl.hpp"
#include "zmienne_globalne.hpp"

using namespace std;


std::ostream& operator<<(std::ostream& os, std::pair<int, int>& p)
{
  return os << "(" << p.first << ", " <<p.second << ")";
}

class plansza
{
    private:
        int rozmiar;
        int ile_w_rzedzie;
        char board[10][10];

    public:
        plansza(int, int);     

        int  getrozmiar() const {return rozmiar;} 
        int  &getrozmiar()      {return rozmiar;} 
        int  getilosc() const {return rozmiar;} 
        int  &getilosc()      {return rozmiar;} 
        
        //na konsoli
        void WypiszPlansze();    

        //juz nie      
        bool ruch(int czyj_ruch, int pion, int poziom);      
        bool czy_ktos_wygral(int czyj_ruch);   
        bool czyRemis();               
        void cofnijRuch(int x, int y);    
        int  miniMax(int czyj_ruch, int x, int y, int glebia, int Alpha, int Beta, bool isMaximizingPlayer);
        int* najlepszyRuch(int czyj_ruch);       
        bool czyPusto(int x, int y); 

        //SDL    
        bool input(int czyj_ruch);               
        void draw(int r, int g, int b);     
        void draw_X(int x, int y);         
        void draw_O(int x, int y);         
        int  kto_wygral_albo_remis(int czyj_ruch);
};



/**
 *  \brief wypelnia plansze pustymi miejscami
 */

plansza::plansza(int x, int y)
{ 
    ile_w_rzedzie = y;         
    rozmiar = x;                     
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j< rozmiar; j++)
        {
            board[i][j] = ' ';        
        }
    }
}


/**
 *  \brief  rysuje krzyzyk 
 */
void plansza::draw_X(int x, int y)
{
    int szerokosc_komorki  = WIDTH/rozmiar;     
    int wysokosc_komorki = HEIGHT/rozmiar;

    const float polowa_sciany_komorki = fmin(szerokosc_komorki, wysokosc_komorki) * 0.25;   
    const float center_x = szerokosc_komorki * 0.5 + x * szerokosc_komorki;             
    const float center_y = wysokosc_komorki * 0.5 + y * wysokosc_komorki;             

    //czerwony X
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // dwie linie X
    SDL_RenderDrawLine(renderer, center_x - polowa_sciany_komorki, center_y - polowa_sciany_komorki, center_x + polowa_sciany_komorki, center_y + polowa_sciany_komorki); 
    SDL_RenderDrawLine(renderer, center_x + polowa_sciany_komorki, center_y - polowa_sciany_komorki, center_x - polowa_sciany_komorki, center_y + polowa_sciany_komorki); 
}

/**
 *  \brief  rysuje okrag 
 */

void plansza::draw_O(int x1, int y1)
{

    float promien = (WIDTH/rozmiar)/4; 
    const int srednica = (promien*2);

    int szerokosc_komorki  = WIDTH/rozmiar;  
    int wysokosc_komorki = HEIGHT/rozmiar;

    int x = promien - 1;
    int y = 0;
    int pomx = 1;
    int pomy = 1;
    
    int blad= pomx - srednica;
 
    const float polowa_sciany_komorki = fmin(szerokosc_komorki, wysokosc_komorki) * 0.25; 
    const float center_x = szerokosc_komorki * 0.5 + y1 * szerokosc_komorki;             //liczymy wspolzedna x srodka okregu (środka komorki)
    const float center_y = wysokosc_komorki * 0.5 + x1 * wysokosc_komorki;           //liczymy wspolzedna y srodka okregu (środka komorki)

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //ustawienie koloru na zielony dla kolka

    while (x >= y)
    {
       SDL_RenderDrawPoint(renderer, center_x + x, center_y - y);
       SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
       SDL_RenderDrawPoint(renderer, center_x - x, center_y - y);
       SDL_RenderDrawPoint(renderer, center_x - x, center_y + y);
       SDL_RenderDrawPoint(renderer, center_x + y, center_y - x);
       SDL_RenderDrawPoint(renderer, center_x + y, center_y + x);
       SDL_RenderDrawPoint(renderer, center_x - y, center_y - x);
       SDL_RenderDrawPoint(renderer, center_x - y, center_y + x);
 
       if (blad <= 0)
       {
          ++y;
          blad += pomy;
          pomy += 2;
       }
       if (blad > 0)
       {
          --x;
          pomx += 2;
          blad += (pomx - srednica);
       }
    }
}


/**
 *  \brief  rysuje plansze
 */
void plansza::draw(int r, int g, int b)
{
    int szerokosc_komorki  = WIDTH/rozmiar;
    int wysokosc_komorki = HEIGHT/rozmiar;

    // zmiana koloru w zaleznosci od stanu gry
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    for(int i = 1; i < rozmiar; ++i)
    {
        SDL_RenderDrawLine(renderer, i * szerokosc_komorki, 0, i * szerokosc_komorki, HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * wysokosc_komorki, WIDTH, i * wysokosc_komorki);
    }

    framecount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if(timerFPS<(1000/60))
    {
        SDL_Delay((1000/60)-timerFPS);
    }

    SDL_RenderPresent(renderer);
}

/**
 *  \brief  Jeśli jest klikniecie na plansze to rysuje O lub X
 *  \return true - ruch sie wykonal lub false - ruch nie wykonal sie
 */

bool plansza::input(int czyj_ruch)
{ 
    int szerokosc_komorki  = WIDTH/rozmiar;
    int wysokosc_komorki = HEIGHT/rozmiar;

    SDL_Event event; 
        
    while(SDL_PollEvent(&event))
    {                                     
        if(event.type == SDL_QUIT)
        {
            SDL_DestroyRenderer(renderer); 
            SDL_DestroyWindow(window);
            SDL_Quit(); 
            running = false; 
            tak_nie = false; 
            jeszcze_raz = false;
        }          

        //dodatkowo klawiatura - esc = wyjscie z programu
        const Uint8 *keystates = SDL_GetKeyboardState(NULL); 
        if(keystates[SDL_SCANCODE_ESCAPE])
        {
            running = false; 
            tak_nie = false; 
            jeszcze_raz = false;
        }    
        
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {      
            //gdy X
            if(czyj_ruch ==  10)
            {                          
                //gdy jest pusto                             
                if(board[event.button.y/wysokosc_komorki][event.button.x/szerokosc_komorki] == ' ')
                {      
                    board[event.button.y/wysokosc_komorki][event.button.x/szerokosc_komorki] = 'x';
                    draw_X(event.button.x / szerokosc_komorki, event.button.y / wysokosc_komorki); 
                    // ruch sie wykonal  
                    return 1;                                                           
                } 
                else 
                {
                    cout<< "tu nie mozna" << endl; 
                    //ruch sie nie wykonal
                    return 0;
                }                       
            }   
            // gdy O
            if(czyj_ruch == -10)
            {                                        
                if(board[event.button.y/wysokosc_komorki][event.button.x/szerokosc_komorki] == ' ')
                {      
                    board[event.button.y/wysokosc_komorki][event.button.x/szerokosc_komorki] = 'o'; 
                    draw_O(event.button.x/szerokosc_komorki, event.button.y/wysokosc_komorki); 
                    // gdy ruch sie wykonal 
                    return 1;                                                 
                } 
                else 
                {
                    cout<< "tu nie mozna" << endl; 
                    // gdy ruch sie nie wykonal
                    return 0;
                }                      
            } 
        }
    }
    return 0;
}


/**
 *  \brief  do terminala, aby sprawdzic czy algorytm jest dobry 
 */
void plansza::WypiszPlansze (){        
    for(int i = 0; i < rozmiar; i ++)
    {
        cout<<" ";
        for(int j = 0; j < rozmiar; j++)
        {
            cout << board[i][j] << " | ";
        }
        cout << endl;
        for(int k = 0; k < rozmiar; k++)
        {
            cout << "----";
        }
        cout << endl;
    }
}

/**
 *  \brief  w zaleznosci od tego czy ruch sie odbył czy nie jest wykonywane dzialanie 
 */
bool plansza::ruch (int czyj_ruch, int pion, int poziom)
{      
    //O
    if(czyj_ruch == -10)
    {                          
        if(board[pion][poziom] == ' ')
        {
            board[pion][poziom] = 'o'; 
            return true;
        }
        else
        {
            cout << "tu nie mozna" <<endl;
            return false;
        }
    }
    else if(czyj_ruch == 10)
    {
        if(board[pion][poziom] == ' ')
        {
            board[pion][poziom] = 'x';
            return true;              
        }
        else
        {
            cout << "tu nie mozna" <<endl;
            return false;
        }
    }
    else
    {
        cout << "cos nie tak" << endl;
        return false;
    }
}



void plansza::cofnijRuch(int x, int y){
    board[x][y] = ' ';
}

/**
 *  \brief  sprawdza czy w danym miejscu cos jest
 */
bool plansza::czyPusto(int x, int y)
{
    if(board[x][y] == ' ')
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool plansza::czy_ktos_wygral(int czyj_ruch)
{
    int counter = 0;
    char zwyciezca;

    if(czyj_ruch ==  10)
    { 
        zwyciezca = 'x';
    }
    if(czyj_ruch == -10)
    { 
        zwyciezca = 'o';
    }

    counter = 0;
    //poziomo
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            if(board[i][j] == zwyciezca)
            {
                counter ++;
            }
            else
            {
                counter = 0;
            }
            if(counter == ile_w_rzedzie)
            {
                return true;
            }
        }
        
        counter = 0;
    }

    //pionowo
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            if(board[j][i] == zwyciezca)
            {
                counter ++;
            }
            else
            {
                counter = 0;
            }
            if(counter == ile_w_rzedzie)
            {
                return true;
            }
        }
       
        counter = 0;
    }

    //po ukosie
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            if(board[i][j] == zwyciezca)
            {
                for(int k = 1; k < ile_w_rzedzie; k++)
                {
                    if(board[i+k][j+k] == zwyciezca)
                    {
                        counter ++; 
                    }
                    else{counter = 0;}
                }
            }
            if(counter == ile_w_rzedzie - 1)
            {
                return true;
            }
        }
    }
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            if(board[i][j] == zwyciezca)
            {
                for(int k = 1; k < ile_w_rzedzie; k++)
                {
                    if(board[i+k][j-k] == zwyciezca)
                    {
                        counter ++; 
                    }
                    else
                    {
                        counter = 0;
                    }
                }
            }
            if(counter == ile_w_rzedzie - 1)
            {
                return true;
            }
        }
    }
    return false;
}


bool plansza::czyRemis()
{
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            if(board[i][j] == ' ')
            {
                // nie ma remisu
                return false; 
            }
        }
    }
    //remis
    return true; 
}

/**
 *  \brief  sprawdza czy wygrala ktoras strona albo czy jest remis
 * 
 *  \return 100 jesli wygral aktualny, -100 jesli przeciwnik i 0 jesli remis
 */
int plansza::kto_wygral_albo_remis(int czyj_ruch)
{
    if(czy_ktos_wygral(czyj_ruch)==true)
    {
        return  100;
    }
    else if(czy_ktos_wygral((-1)*czyj_ruch)==false)
    {
        return -100;
    }
    else 
    {
        return 0;
    }
}

/**
 *  \brief  algorytm miniMax
 */
int plansza::miniMax(int czyj_ruch, int x, int y, int glebia, int Alpha, int Beta, bool isMaximizingPlayer)
{
    int NajlepszaWartosc, wartosc;

    int score = kto_wygral_albo_remis(czyj_ruch); 

    char zwyciezca; 

    if(czyj_ruch ==  10)
    {
         zwyciezca = 'x';
    }
    if(czyj_ruch == -10)
    { 
        zwyciezca = 'o';
    }


    //gdy remis
    if(czyRemis() == true || glebia == 0)
    {
        return score;
    } 

    //gdy ktos wygra
    if(score == 100 || score == -100)
    {
        return score;
    }

    if(isMaximizingPlayer == true)
    {
        NajlepszaWartosc = - Infinity;

        for(int i = 0; i < rozmiar; i++)
        {
            for(int j = 0; j < rozmiar; j++)
            {
                //gdy moge zrobić ruch 
                if(board[i][j] == ' ')
                {            
                    board[i][j] = zwyciezca;                                            
                    wartosc = miniMax(czyj_ruch, i, j, glebia - 1, Alpha, Beta, false); // min bo false
                    //tak jakby go nigdy nie było
                    cofnijRuch(i, j); 
                                                  
                    NajlepszaWartosc = std::max(NajlepszaWartosc, wartosc);  

                    //jeśli Alpha znajdzie lepsza opcje   
                    Alpha = std::max(Alpha, NajlepszaWartosc);  
                    //odcinamy ścieżke Beta jak mamy lepsza                                               
                    if(Beta <= Alpha)
                    {
                        break;
                    }                                           
                }
            }
        }
        return NajlepszaWartosc;
    }
    else
    {
        NajlepszaWartosc = Infinity;

        for(int i = 0; i < rozmiar; i++)
        {
            for(int j = 0; j < rozmiar; j++)
            {
                //gdy moge zrobić ruch
                if(board[i][j] == ' ')
                {                                       
                    ruch(czyj_ruch * (-1), i, j);   
                                                                   
                    wartosc = miniMax(czyj_ruch, i, j, glebia - 1, Alpha, Beta, true);  // max bo true

                    //analogicznie jak wyzej 
                    cofnijRuch(i, j);                                                   
                    NajlepszaWartosc = std::min(NajlepszaWartosc, wartosc);
                                
                    Beta = std::min(Beta, NajlepszaWartosc);  

                        break;
                                                          
                }
            }
        }
        return NajlepszaWartosc;
    }

}

/**
 *  \brief  metoda szukajaca dla danego stanu planszy najlepszego ruchu
 *
 *  \return tablice wspolzednych najlepszego ruchu
 */

int* plansza::najlepszyRuch(int czyj_ruch)
{ 
    int* ruch = new int[2]; 

    int NajlepszaWartosc,glebia,wartosc,c;

    NajlepszaWartosc = (-1) * Infinity;
    c = 0;

    char zwyciezca;
    if(czyj_ruch ==  10)
    { 
        zwyciezca = 'x';
    } 
    if(czyj_ruch == -10)
    { 
        zwyciezca = 'o';
    } 

    //abstrakyjne
    ruch[0] = -10; 
    ruch[1] = -10;   

    if(rozmiar <= 3)
    {
        glebia = 10;
    }  
    else
    {
       glebia = 7;
    }

    std::vector<std::pair<int,int>> coordinates;
  
    for(int i=0; i < rozmiar; ++i)
        for(int j=0; j < rozmiar; ++j)
        coordinates.push_back(std::make_pair(i,j));

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(coordinates.begin(), coordinates.end(), g);


    for(auto& p: coordinates)
    {
        int i,j;
        i=p.first;
        j=p.second;
            if(board[i][j] == ' ')
            {             
                if(czyj_ruch == 10)
                {                                                                                            
                    board[i][j] = 'o';  

                    //jak ktos wygrał nie ma sensu minmax                                                                                          
                    if(czy_ktos_wygral((-1)*czyj_ruch) == true)
                    {
                        cofnijRuch(i, j);
                        ruch[0] = i; 
                        ruch[1] = j; 
                        return ruch;
                    }         
                }
                board[i][j] = zwyciezca;         
                wartosc = miniMax(czyj_ruch, i, j, glebia, (-1)*Infinity, Infinity, 0); 
                cofnijRuch(i, j);               
                
                //patrzymy czy wczesniejsza sciezka jest lesza
                if(wartosc > NajlepszaWartosc)
                { 
                    ruch[0] = i;                
                    ruch[1] = j;                
                    NajlepszaWartosc = wartosc; 
                }
            }
    }
    return ruch;
}


#endif
