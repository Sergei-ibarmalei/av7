#include "n_ob.h"

AlienLazer::AlienLazer(const plot* start, const texture_* t):
            BaseLazer(start, dir::left, t)
{
    Velocities()->x = ALIENLAZER_VELOCITY;
    Velocities()->y = 0;
}

bool AlienLazer::operator==(NHero& hero)
{
    if (obj_texture->main_rect == *hero.GetMainRect())
    {
        return hero == obj_texture->main_rect;
    }
    return false;
}