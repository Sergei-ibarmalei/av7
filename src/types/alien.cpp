#include "n_ob.h"

Alien::Alien(const texture_* t,
                             const plot* start,
                             const texture_* lazer):AlienABC(t,
                             re::alien_t1::t1_allR, start, lazer)
{
    ElementaryObject::Velocities()->x = -ALIENFLEET_ONE_VELOCITY;
    ElementaryObject::Velocities()->y = 0;
    scoreWeight = scores::plainAlien;
    stepsWithoutFire = 0;
}



void Alien::Show(const Sdl* sdl)
{
    AlienABC::Show(sdl);
}

void Alien::setCr()
{
    #define CR cr->Array()
    #define ONE re::alien_t1::t1_one
    #define TWO re::alien_t1::t1_two
    #define THREE re::alien_t1::t1_three
    #define MAINR_UPLEFT_X GetMainRect_x()
    #define MAINR_UPLEFT_Y GetMainRect_y()


    CR[ONE].x = MAINR_UPLEFT_X + 32;
    CR[ONE].y = MAINR_UPLEFT_Y;
    CR[ONE].w = 39;
    CR[ONE].h = 31;

    CR[TWO].x = MAINR_UPLEFT_X + 4;
    CR[TWO].y = CR[ONE].y + CR[ONE].h;
    CR[TWO].w = 87;
    CR[TWO].h = 32;

    CR[THREE].x = CR[ONE].x;
    CR[THREE].y = CR[TWO].y + CR[TWO].h;
    CR[THREE].w = CR[ONE].w;
    CR[THREE].h = CR[ONE].h;



    #undef CR
    #undef ONE
    #undef TWO
    #undef THREE
}


/*Проверка на столкновение алиена и лазера героя*/
bool Alien::operator==(const HeroLazer& hl)
{
    if (obj_texture->main_rect == *hl.GetMainRect())
    {
        return *Alien::cr == hl.GetMainRect();
    }
    return false;
}



/*Проверка - находится ли алиен в эшелоне героя*/
bool Alien::operator==(const echelon* heroEchelon)
{
    return *GetMainRect() == *heroEchelon;
}



bool Alien::operator==(const NHero* hero)
{
    if (obj_texture->main_rect == *hero->GetMainRect())
    {   
        return *cr == hero->CR();
    }
    return false;
}



