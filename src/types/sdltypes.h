#ifndef SDLTYPES_H
#define SDLTYPES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#define S_W 1920
#define S_H 1080

struct Rect: public SDL_Rect
{
    Rect() {x = y = w = h = 0;}
    bool operator==(const struct Rect& r)
    {
        if ((y+h) <= r.y)      return false;
        if (y >= (r.y+r.h))    return false;
        if ((x+w) <= r.x)      return false;
        if (x>= (r.x+r.w))     return false;
        return true;
    }
};

using rect_ = Rect;

struct Texture 
{
    SDL_Texture* texture;
    rect_        rect;
};

using texture_ = Texture;


#endif