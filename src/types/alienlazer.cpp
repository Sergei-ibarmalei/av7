//#include "n_ob.h"
#include "alienlazer.h"

AlienLazer::AlienLazer(const plot* start, const texture_* t):
            BaseLazer(start, dir::left, t)
{
    Velocities()->x = ALIENLAZER_VELOCITY;
    Velocities()->y = 0;
}


/*Проверка на столкновение лазера алиена и героя*/
bool AlienLazer::operator==(NHero& hero)
{
    /*Если герой уже убит, то ничего не проверяем*/
    if (hero.IsItGone() == true) return false;
    if (obj_texture->main_rect == *hero.GetMainRect())
    {
        return hero == obj_texture->main_rect;
    }
    return false;
}