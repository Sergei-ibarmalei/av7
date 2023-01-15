#include "n_ob.h"

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
                if (GetLazer_x() > RIGHT_BORDER_X)
                    isOnScreen = false;
                break;
            }
            case dir::left:
            {
                ElementaryObject::resetUpLeftCorner_x(-PLAINLASER_VELOCITY);
                if (GetLazerW() < BORDER_THICKNESS)
                    isOnScreen = false;
                break;
            }
            default: {}
        }
    }
}

#ifdef SHOW_COL_R
    void LongLazer::ShowColR(const Sdl* sdl) const
    {
        ElementaryObject::showCollisionMainRect(sdl);
    }
#endif


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

