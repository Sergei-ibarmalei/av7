#include "n_ob.h"

LongLazer::LongLazer(const plot* start, dir::direction d, const texture_* t):
    ElementaryObject(t)
{
    direct = d;
    isOnScreen = true;
    switch (direct)
    {
        case dir::left:
        {
            setUpLeftCorner(start->x - obj_texture->main_rect.w, start->y);
            break;
        }
        case dir::right:
        {
            setUpLeftCorner(start->x + obj_texture->main_rect.w, start->y);
            break;
        }
        default: {}
    }
}

void LongLazer::Move()
{
    #define LAZER_W obj_texture->main_rect.x+obj_texture->main_rect.w

    if (isOnScreen)
    {
        switch (direct)
        {
            case dir::right:
            {
                obj_texture->main_rect.x += PLAINLASER_VELOCITY;
                if (obj_texture->main_rect.x > RIGHT_BORDER_X)
                    isOnScreen = false;
                break;
            }
            case dir::left:
            {
                obj_texture->main_rect.x -= PLAINLASER_VELOCITY;
                if (LAZER_W < BORDER_THICKNESS)
                    isOnScreen = false;
                break;
            }
            default: {}
        }
    }
    #undef LAZER_W
}

#ifdef SHOW_COL_R
    void LongLazer::ShowColR(Sdl* sdl)
    {
        ElementaryObject::showCollisionMainRect(sdl);
    }
#endif

