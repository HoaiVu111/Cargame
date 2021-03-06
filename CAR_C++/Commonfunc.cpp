#include "CommonFunc.h"

using namespace std;

CommonFunc::CommonFunc()
{
    pTexture = NULL; //
    pRect.x = 0;
    pRect.y = 0;
    pRect.w = 0;
    pRect.h = 0;
}

CommonFunc::~CommonFunc()
{
    Free();
}

bool CommonFunc::loadFromFile(const std::string &path, SDL_Renderer* renderer)
{

	Free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B ) );   //transparent background n/v
    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    pRect.w = loadedSurface->w;
    pRect.h = loadedSurface->h;
    SDL_FreeSurface( loadedSurface );
    pTexture = newTexture;
	return pTexture != NULL;
}

void CommonFunc::render(SDL_Renderer* des, const SDL_Rect* clip,  int x,  int y )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_Rect renderQuad = {offset.x, offset.y, pRect.w, pRect.h};
    SDL_RenderCopy(des, pTexture, NULL, &renderQuad);
}

void CommonFunc::Free()
{
    if (pTexture == NULL)
    {
        SDL_DestroyTexture(pTexture);
        pTexture = NULL;
        pRect.w = 0;
        pRect.h = 0;
    }
}

//kiem tra va cham
bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;


    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
        return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
        return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
        return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
        return true;
        }
    }


    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
        return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
        return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
        return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
        return true;
        }
    }

    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }
    return false;
}
