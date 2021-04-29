#include "Threat.h"

using namespace std;

Threat::Threat()
{
    threatRect.x = 250;
    threatRect.y = - HEIGHT_THREAT;
    threatRect.w = 100;
    threatRect.h = 200;
    pRect.w = WIDTH_THREAT;
    pRect.h = HEIGHT_THREAT;
}

Threat::~Threat()
{

}

void Threat::HandleMove()
{
    threatRect.y +=  THREAT_SPEED;
    if (threatRect.y > SCREEN_HEIGHT)
    {
        threatRect.y = - HEIGHT_THREAT;
        int x_val;
        int ob;
        ob = rand()%2;
        if(ob == 1)
        {
             x_val = rand()/150 + 200;

        }
        else
        {
             x_val = rand()/150 + 450;
        }
        threatRect.x = x_val;
    }
}

void Threat::Draw(SDL_Renderer* des)
{
    SDL_Rect renderQuad = {threatRect.x, threatRect.y, WIDTH_THREAT, HEIGHT_THREAT};
    SDL_RenderCopy(des, pTexture, NULL, &renderQuad);
}

void Threat::HandleInputAction()
{

}

