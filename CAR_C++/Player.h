#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "CommonFunc.h"

#define WIDTH_PLAYER 85
#define HEIGHT_PLAYER 170

#define BORDER_WIDTH_LEFT_X_VAL 200         //quy uoc le duong
#define BORDER_WIDTH_RIGHT_X_VAL 680

#define PLAYER_COLLISION_WIDTH 80
#define PLAYER_COLLISION_HEIGHT 165

#define PLAYER_SPEED 6                     //buoc nhay
#define ZERO 0

#define START_X 300                         //vi tri xuat phat player
#define START_Y 500

struct Player : public CommonFunc
{
        Player();
        ~Player();

        void handleInput(SDL_Event event, SDL_Renderer* &gRenderer);
        void handleMove(SDL_Renderer* renderer);
        void draw(SDL_Renderer* des);

        SDL_Rect playerRect;

};


#endif // PLAYER_H_INCLUDED
