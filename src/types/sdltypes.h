#ifndef SDLTYPES_H
#define SDLTYPES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include "../consts/graphconsts.h"


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
    rect_        main_rect;
};

using texture_ = Texture;

struct plot_
{
    int x; int y;
};

using plot = plot_;

/*Collision compare arrays*/
class Cca
{
    private:
    rect_* arr;
    int    length;
    bool init {true};
    bool comparis(rect_* first, const int len, 
                  rect_* second);

    public:
    Cca(): arr(nullptr), length(0) {}
    bool operator==(const Cca& ca);
    Cca& operator=(const Cca& ca);
    void Set(rect_* a, const int len);
    ~Cca();
    bool Status() const {return init;}
};

class CRC 
{
    private:
    rect_* array;
    int    arrLen;
    bool   init {true};
    bool   comparison(rect_* first, const int len, rect_* second);

    public:
    //CRC(const int len): array(nullptr), arrLen(len) {}
    CRC(const int len);
    CRC(const CRC& crc);
    CRC& operator=(const CRC& crc);
    bool operator==(const CRC& crc);
    rect_* Array() {return array;}
    bool Status() const {return init;}


};


#endif
