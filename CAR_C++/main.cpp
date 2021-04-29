#include "Threat.h"
#include "Player.h"
#include "Global.h"
#include "Button.h"
#include "Commonfunc.h"
#include <SDL_mixer.h>
#include <time.h>

using namespace std;

int START_BUTTON_POSX = 100 ;
int START_BUTTON_POSY = 300;
int QUIT_BUTTON_POSX = 500;
int QUIT_BUTTON_POSY = 300;
int TITLE_BUTTON_POSX = 240;
int TITLE_BUTTON_POSY = 100;

int START_BUTTON_HEIGHT  = 200;
int START_BUTTON_WIDTH  = 300;
int QUIT_BUTTON_HEIGHT  = 200;
int QUIT_BUTTON_WIDTH  = 300;
int TITLE_BUTTON_HEIGHT  = 150;
int TITLE_BUTTON_WIDTH  = 450;

SDL_Texture* start_button_texture_1  = NULL;
SDL_Texture* start_button_texture_2= NULL;

SDL_Texture* quit_button_texture_1 = NULL;
SDL_Texture* quit_button_texture_2 = NULL;

SDL_Texture* title_button_texture  = NULL;

Mix_Music* soundtrack  ;
Mix_Music* exp ;


bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT );


void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, CommonFunc gBackgroundTexture);

bool checkBackground(SDL_Renderer* &gRenderer);

void drawBackground(SDL_Renderer* &gRenderer, int& backGround_y);

void drawPlayer(SDL_Event gEvent, SDL_Renderer* &gRenderer, Player &player );

bool drawThreats(SDL_Event gEvent, SDL_Renderer* &gRenderer, SDL_Window* &gWindow,
                 Threat &Threat, Player player, CommonFunc gBackgroundTexture);

CommonFunc gBackgroundTexture;

SDL_Window* gWindow = NULL ;
SDL_Renderer* gRenderer = NULL ;
SDL_Event gEvent ;

void LoadGraphic(){
    start_button_texture_1 = IMG_LoadTexture(gRenderer, "start1.png");
    start_button_texture_2 = IMG_LoadTexture(gRenderer, "start2.png");
    quit_button_texture_1 = IMG_LoadTexture(gRenderer, "quit_g1.png");
    quit_button_texture_2 = IMG_LoadTexture(gRenderer, "quit_g2.png");
    title_button_texture = IMG_LoadTexture(gRenderer, "title.png");
}


bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    bool success = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    gWindow = SDL_CreateWindow( "CAR GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) ;
    return success;
}

bool checkBackground(SDL_Renderer* &gRenderer)
{
    bool check = gBackgroundTexture.loadFromFile("background.png", gRenderer);
    if (check == false) return false;
    return true;
}

void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, CommonFunc gBackgroundTexture)
{
    gBackgroundTexture.Free();
    SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
    Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void drawBackground(SDL_Renderer* &gRenderer, int& backGround_y)
{

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
    backGround_y += 2;
    gBackgroundTexture.render(gRenderer, NULL, 0, backGround_y);
    gBackgroundTexture.render(gRenderer, NULL, 0, backGround_y - SCREEN_HEIGHT);
    if (backGround_y >= SCREEN_HEIGHT)
    {
        backGround_y = 0;
    }
}

void drawPlayer(SDL_Event gEvent, SDL_Renderer* &gRenderer, Player &player )
{
    player.handleMove(gRenderer);
    player.draw(gRenderer);
}

bool drawThreats(SDL_Event gEvent, SDL_Renderer* &gRenderer, SDL_Window* &gWindow, Threat &Threat, Player player, CommonFunc gBackgroundTexture)
{
    Threat.HandleMove();
    Threat.Draw(gRenderer);
    bool is_col = SDLCommonFunc::CheckCollision(player.playerRect, Threat.threatRect); //
    if (is_col)
        {
        Mix_HaltMusic() ;
        Mix_PlayMusic(exp,1) ;
        SDL_Delay(3000);
        return false;
        }

    return true;
}

//ham main
int main(int argc, char* argv[])
{

    srand (time(NULL));   //cho viec dung ham rand()

    int backGround_y = 0;
    if( !init(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT) ) //
        {
            printf( "Failed to initialize!\n" );
            return -1;
        }

    if (checkBackground(gRenderer) == false)
        {
            printf( "Failed to render background!\n" );
            return -1;
        }
    soundtrack = Mix_LoadMUS("soundtrack.mp3") ;
    exp = Mix_LoadMUS("explosion.mp3") ;
    LoadGraphic() ;

    bool quit_menu1 = false ;
    int x,y ;
    Button start_button(START_BUTTON_POSX,START_BUTTON_POSY,START_BUTTON_WIDTH,START_BUTTON_HEIGHT,
                        start_button_texture_1, start_button_texture_2) ;
    Button quit_button(QUIT_BUTTON_POSX,QUIT_BUTTON_POSY,QUIT_BUTTON_WIDTH,QUIT_BUTTON_HEIGHT,
                       quit_button_texture_1, quit_button_texture_2) ;
    Button title_button(TITLE_BUTTON_POSX,TITLE_BUTTON_POSY,TITLE_BUTTON_WIDTH,TITLE_BUTTON_HEIGHT,
                       title_button_texture, NULL) ;


    start_button.Draw() ;
    quit_button.Draw() ;
    title_button.Draw();

    while(!quit_menu1)
    {
         while(SDL_PollEvent(&gEvent))
         {
             if(gEvent.type == SDL_QUIT){
                close(gWindow, gRenderer, gBackgroundTexture) ;
                return 0 ;
             }
             else {
                if(gEvent.type == SDL_MOUSEMOTION){
                    SDL_GetMouseState(&x,&y) ;
                    start_button.HandleEvent(x,y) ;
                    quit_button.HandleEvent(x,y) ;
                }
                if(gEvent.type == SDL_MOUSEBUTTONDOWN){
                    SDL_GetMouseState(&x,&y) ;
                    if(quit_button.ontheButton(x,y))
                    {
                        close(gWindow, gRenderer, gBackgroundTexture) ;
                        return 0 ;
                    }
                    if(start_button.ontheButton(x,y))
                    {
                        quit_menu1 = true ;
                    }

                }
             }
         }
     }

    Player player;
    player.loadFromFile("mycar.png", gRenderer);
    Threat threats;
    threats.loadFromFile("enemy.png", gRenderer);

    bool quit = false;
    Mix_PlayMusic(soundtrack,-1) ;

    clock_t start_t, end_t, total_t;
    int i;
    start_t = clock();

    while ( !quit )
        {
            while (SDL_PollEvent(&gEvent) != 0 )
            {

                if( gEvent.type == SDL_QUIT )
                {
                    quit = true;
                   // return 1;
                }
                else
                player.handleInput(gEvent, gRenderer);
            }

            drawBackground(gRenderer, backGround_y);

            bool is_col = drawThreats(gEvent, gRenderer, gWindow, threats, player, gBackgroundTexture);

            if (!is_col) //   return 1;
                quit = true ;

            drawPlayer(gEvent, gRenderer, player);
            SDL_Delay(10);

            SDL_RenderPresent( gRenderer );
        }

        Mix_HaltMusic() ;

        end_t = clock();
        total_t = (double)(end_t - start_t);                       /*thoi gian troi qua cua 1 lan choi game tinh bang
        so lan danh dau dong ho da troi qua tu khi chuong trinh duoc chay */

        CommonFunc Image;

        if     (total_t>50000)  Image.loadFromFile("3.png", gRenderer);
        else if(total_t >20000) Image.loadFromFile("2.png", gRenderer);
        else                    Image.loadFromFile("1.png", gRenderer);

        Image.render(gRenderer, NULL, 300, 170);

        SDL_RenderPresent( gRenderer );

        SDL_Delay(1500);
        close(gWindow, gRenderer, gBackgroundTexture);

        cout << "Your score " << total_t << endl;                   //in diem ra man hinh Console
        if     (total_t>50000)  cout << "Outrageous racer!";
        else if(total_t >20000) cout << "Drive carefully!";
        else                    cout << "Loser";

    return 0;
}



