#include "TextObject.h"

TextObject::TextObject()
{
    ;
}

TextObject::~TextObject()
{

}

void TextObject::SetColor(const int& type)
{
    if(type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0}
        text_color_ = color;
    }
    else if (type == )
}
