#ifndef THREAT_H
#define THREAT_H

#include "CommonFunc.h"
#include "Player.h"
#include "Global.h"

#define WIDTH_THREAT 100
#define HEIGHT_THREAT 200

#define THREAT_SPEED 5


struct Threat : public CommonFunc
{
    Threat();
    ~Threat();

    void HandleMove();
    void HandleInputAction();
    void Draw(SDL_Renderer* des);


    SDL_Rect threatRect;
};

#endif // THREAT_H
