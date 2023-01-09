#include "skyclass.h"
#include "../core/rand.h"

#define UP UP_BORDER_Y + UP_BORDER_H
#define DOWN DOWN_BORDER_Y
#define LEFT LEFT_BORDER_W
#define RIGHT RIGHT_BORDER_X



Sky::Sky(texture_* t, log_::Log& log)
{
    if (!t)
    {
        log.log_info = "Cannot create sky, texture of star is absent.\n";
        log.push(log.log_info);
        init = false;
        return;
    }
    starTexture = t;
    fast = new (std::nothrow) rect_[fastStarMax];
    slow = new (std::nothrow) rect_[slowStarMax];
    if (!fast || !slow)
    {
        log.log_info = "Cannot allocate memory for stars.\n";
        log.push(log.log_info);
        init = false;
        return;
    }
    setStarsCoords();

}

void Sky::ShowSky(Sdl* sdl)
{
    for (int star = 0; star < fastStarMax; ++star)
    {
        sdl->TextureRender(starTexture->texture, &fast[star]);
    }
    for (int star = 0; star < slowStarMax; ++star)
    {
        sdl->TextureRender(starTexture->texture, &slow[star]);
    }
}

void Sky::setStarsCoords()
{
    for (int star = 0; star < fastStarMax; ++star)
    {
       fast[star].x = getRand(LEFT, RIGHT);
       fast[star].y = getRand(UP, DOWN);
       fast[star].w = starTexture->rect.w;
       fast[star].h = starTexture->rect.h;
    }

    for (int star = 0; star < slowStarMax; ++star)
    {
        slow[star].x = getRand(LEFT, RIGHT);
        slow[star].y = getRand(UP, DOWN);
        slow[star].w = starTexture->rect.w;
        slow[star].h = starTexture->rect.h;
    }


}

void Sky::MoveSky()
{
    for (int star = 0; star < fastStarMax; ++star)
    {
        fast[star].x -= FAST_STAR_VELOCITY;
        if (fast[star].x < LEFT)
        {
            fast[star].x = getRand(RIGHT, RIGHT+ 300);
            fast[star].y = getRand(UP, DOWN);
        }
    }

    for (int star = 0; star < slowStarMax; ++star)
    {
        slow[star].x -= SLOW_STAR_VELOCITY;
        if (slow[star].x < LEFT)
        {
            slow[star].x = getRand(RIGHT, RIGHT+ 300);
            slow[star].y = getRand(UP, DOWN);
        }
    }   
}

Sky::~Sky()
{
    starTexture = nullptr;
    delete[] fast;
    fast = nullptr;
    delete[] slow;
    slow = nullptr;
}


#undef UP
#undef DOWN
#undef LEFT
#undef RIGHT