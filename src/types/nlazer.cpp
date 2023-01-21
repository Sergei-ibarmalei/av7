#include "n_ob.h"
#include "../core/checkcrossing.h"

BaseLazer::BaseLazer(const plot* start, dir::direction d, const texture_* t):
    ElementaryObject(t)
{
    #define LAZER_HALF_HEIGHT GetMainRect_h() / 2
    #define LAZER_WIDTH GetMainRect_w()

    direct = d;
    isOnScreen = true;

    switch (direct)
    {
        case dir::left:
        {
            setUpLeftCorner(start->x - LAZER_WIDTH, start->y); break;
        }
        case dir::right:
        {
            setUpLeftCorner(start->x, (start->y - LAZER_HALF_HEIGHT)); break;
        }
        default: {}
    }

    #undef LAZER_HALF_HEIGHT
    #undef LAZER_WIDTH
}

void BaseLazer::Move()
{
    #define MAINRECT_X obj_texture->main_rect.x
    #define MAINRECT_WIDTH obj_texture->main_rect.x+obj_texture->main_rect.w

    if (!isOnScreen) return;
    switch (direct)
    {
        case dir::right:
        {
            resetUpLeftCorner_x(obj_velocities->x);
            if (hasCrossedRight_fromScreen(MAINRECT_X))
                isOnScreen = false;
            break;
        }
        case dir::left:
        {
            resetUpLeftCorner_x(-obj_velocities->x);
            if (hasCrossedLeft_fromScreen(MAINRECT_WIDTH))
                isOnScreen = false;
            break;
        }
        default: {}
    }
    #undef MAINRECT_X
    #undef MAINRECT_WIDTH
}

int BaseLazer::Lazer_x() const
{
    return GetMainRect_x();
}

int BaseLazer::Lazer_y() const 
{
    return GetMainRect_y();
}

int BaseLazer::Lazer_w() const 
{
    return GetMainRect_w();
}

void BaseLazer::ShowLazer(const Sdl* sdl) const 
{
    ShowObj(sdl);
}



HeroLazer::HeroLazer(const plot* start, const texture_* t):
    BaseLazer(start, dir::right, t)
{
    Velocities()->x = HEROLAZER_VELOCITY;
    Velocities()->y = 0;
}

