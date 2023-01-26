#ifndef SDLTYPES_H
#define SDLTYPES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include "../consts/graphconsts.h"

struct Echelon
{
    int hi, low;
    bool operator==(const SDL_Rect& r) const
    {
        if (r.y < hi)        return false;
        if ((r.y+r.h) > low) return false;
        return true;
    }
};
using echelon = Echelon;

struct Rect: public SDL_Rect
{
    Rect() {x = y = w = h = 0;}

    bool operator==(const struct Rect& r) const
    {
        if ((y+h) <= r.y)      return false;
        if (y >= (r.y+r.h))    return false;
        if ((x+w) <= r.x)      return false;
        if (x>= (r.x+r.w))     return false;
        return true;
    }
    bool operator==(const echelon& e) const
    {
        if (y < e.hi)      return false;
        if ((y+h) > e.low) return false;
        return true;
    }



    friend std::ostream& operator<<(std::ostream& os, const  Rect& r);

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



class CRC 
{
    private:
    rect_* array;
    int    arrLen;
    bool   init {true};
    bool   cmp_oneTomany(const rect_* r);
    bool   comparison(const rect_* first, 
                      const int len, const rect_* second) const;

    public:
    CRC(const int len);
    CRC(const CRC&) = delete;
    CRC& operator=(const CRC&) = delete;
    //bool operator==(const CRC& crc);
    bool operator==(CRC* crc);
    bool operator==(const rect_* r);

    bool operator==(const rect_& r);




    
    rect_* Array() {return array;}
    bool Status() const {return init;}


};


#endif
