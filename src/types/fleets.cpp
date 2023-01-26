#include "n_ob.h"
#include "../core/rand.h"

bool Engine::makeAlienFleetOne(const tc* collection)
{
    #define RIGHT_SIDE RIGHT_BORDER_X+RIGHT_BORDER_W
    #define SHIP_MAINRECT_H collection->Pictures()[tn::alien_one].main_rect.h
    #define UP (UP_BORDER_Y+UP_BORDER_H)+SHIP_MAINRECT_H
    #define DOWN DOWN_BORDER_Y-SHIP_MAINRECT_H
    #define ALIEN_TEXTURE &collection->Pictures()[tn::alien_one]
    #define ALIEN_LASER_TEXTURE &collection->Pictures()[tn::alien_laser01]

    plot alien_start;
    for (int count = 0; count < ALIENFLEET_ONE_CAP; ++count)
    {
        alien_start.x = RIGHT_SIDE +
            (count * ALIENFLEET_ONE_SPACE_BETWEEN);
        alien_start.y = getRand(UP, DOWN);

        Alien* alien = new (std::nothrow) Alien{ALIEN_TEXTURE, &alien_start,
                                    ALIEN_LASER_TEXTURE};
        if (!alien || (alien->Status() == false)) return false;


        if (!alienFleetOneStorage->Push(alien)) return false;
    }
    return true;
    

    #undef ALIEN_TEXTURE
    #undef ALIEN_LASER_TEXTURE
    #undef RIGHT_SIDE
    #undef SHIP_MAINRECT_H
    #undef DOWN
}

void Engine::MoveAlienFleetOne(NHero* hero)
{
    #define COUNTER alienFleetOneStorage->GetCounter()
    #define ALIEN_IS_ABSENT !(*(alienFleetOneStorage))[alien]
    #define ALIEN_IN_HEROECHELON\
                        (*(alienFleetOneStorage))[alien]->OnScreen() &&\
                        *(*(alienFleetOneStorage))[alien] ==\
                        hero->GetHeroEchelon()
    #define ALIEN_WALKED_ENOUGH_WITHOUT_FIRE\
                (*(alienFleetOneStorage))[alien]->GetStepsWithoutFire() ==\
                ALIENFLEET_ONE_MAXSTEPSWITHOUTFIRE
    #define HERO_IS_ALIVE hero->IsItGone() == false

    for (int alien = 0; alien < COUNTER; ++alien)
    {

        if (ALIEN_IS_ABSENT) continue;

        if (HERO_IS_ALIVE && ALIEN_IN_HEROECHELON && 
                                            ALIEN_WALKED_ENOUGH_WITHOUT_FIRE)
        {
            AlienLazer* lazer = new (std::nothrow) 
            AlienLazer{(*(alienFleetOneStorage))[alien]->GetLazerStart(),
                                &tcollection->Pictures()[tn::alien_laser01]};
            if (!lazer || (lazer->Status() == false)) continue;
            alienLazerStorage->Push(lazer);
            (*(alienFleetOneStorage))[alien]->ResetStepsWithoutFire();
        }
        if (ALIEN_WALKED_ENOUGH_WITHOUT_FIRE)
        {
            (*(alienFleetOneStorage))[alien]->ResetStepsWithoutFire();
        }

        (*(alienFleetOneStorage))[alien]->StrightMove(hero);

        if ((*(alienFleetOneStorage))[alien]->IsItGone())
            alienFleetOneStorage->Remove(alien);
    }

    #undef COUNTER
    #undef HERO_IS_ALIVE
    #undef ALIEN_IS_ABSENT
    #undef ALIEN_IN_HEROECHELON
    #undef ALIEN_WALKED_ENOUGH_WITHOUT_FIRE
    #undef ALIENFLEET_ONE_MAXSTEPSWITHOUTFIRE
 
}

void Engine::ShowAlienFleetOne(const Sdl* sdl) const
{
    #define ALIEN_IS_ALIVE !(*(alienFleetOneStorage))[alien]->IsItGone()
    #define ALIEN_IS_not_ONSCREEN !(*(alienFleetOneStorage))[alien]->OnScreen()
    #define ALIEN_IS_ABSENT !(*(alienFleetOneStorage))[alien]
    #define COUNTER alienFleetOneStorage->GetCounter()
    
    for (int alien = 0; alien < COUNTER; ++alien)
    {

        if (ALIEN_IS_ABSENT)       continue;
        if (ALIEN_IS_not_ONSCREEN) continue;
        if (!(*(alienFleetOneStorage))[alien]) return;
        else (*(alienFleetOneStorage))[alien]->Show(sdl);
    }

    #undef ALIEN_IS_ALIVE
    #undef ALIEN_IS_not_ONSCREEN
    #undef ALIEN_IS_ABSENT
    #undef COUNTER
}

