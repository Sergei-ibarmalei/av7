#include "n_ob.h"
#include "../core/checkcrossing.h"

LongLazer::LongLazer(const plot* start, dir::direction d, const texture_* t):
    ElementaryObject(t)
{
    #define LAZER_HALF_H ElementaryObject::GetMainRect_h() / 2

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
            setUpLeftCorner(start->x, (start->y - LAZER_HALF_H));
            break;
        }
        default: {}
    }

    #undef LAZER_HALF_H
}

void LongLazer::Move()
{
    if (isOnScreen)
    {
        switch (direct)
        {
            case dir::right:
            {
                ElementaryObject::resetUpLeftCorner_x(PLAINLASER_VELOCITY);
                if (hasCrossedRight_fromScreen(GetLazer_x()))
                    ElementaryObject::ResetOnScreen(false);
                break;
            }
            case dir::left:
            {
                ElementaryObject::resetUpLeftCorner_x(-PLAINLASER_VELOCITY);
                if (hasCrossedLeft_fromScreen(GetLazerW()))
                    ElementaryObject::ResetOnScreen(false);
                break;
            }
            default: {}
        }
    }
}


int LongLazer::GetLazer_x() const
{
    return ElementaryObject::GetMainRect_x();
}

int LongLazer::GetLazer_y() const
{
    return ElementaryObject::GetMainRect_y();
}

int LongLazer::GetLazerW() const
{
    return ElementaryObject::GetMainRectW();
}

int LongLazer::GetLazerH() const
{
    return ElementaryObject::GetMainRectH();
}

void LongLazer::Show(const Sdl* sdl) const 
{
    ElementaryObject::ShowObj(sdl);
}

int LongLazer::GetLazer_w() const
{
    return ElementaryObject::GetMainRect_w();
}

