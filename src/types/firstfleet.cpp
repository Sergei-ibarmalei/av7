#include "n_ob.h"
#include "../core/rand.h"
#include "../core/core.h"

FirstFleet::FirstFleet(const tc* collection,
        const texture_* heap_digits): GameFleet_ABC(collection, heap_digits)
{
    if (!init) return;
    fleetStorage = new (std::nothrow) AlienStorage {ALIENFLEET_ONE_CAP};
    if (!fleetStorage || fleetStorage->Status() == false)
    {
        init = false; return;
    }
}

bool FirstFleet::makeFirstFleet(tc* collection)
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


        if (!fleetStorage->Push(alien)) return false;
    }
    return true;
    

    #undef ALIEN_TEXTURE
    #undef ALIEN_LASER_TEXTURE
    #undef RIGHT_SIDE
    #undef SHIP_MAINRECT_H
    #undef DOWN
}

void FirstFleet::MoveFleet(NHero* hero, status_t& status)
{

    /*Если герой подбит, то не двигаем флот прямо*/
    if (status.hero_dead) return;
    #ifdef STOP_FLEET_MOVING
        if (status.stop_fleet_moving) return;
    #endif

    #define COUNTER fleetStorage->GetCounter()
    #define ALIEN_IS_ABSENT !(*(fleetStorage))[alien]
    #define ALIEN_IN_HEROECHELON\
                        (*(fleetStorage))[alien]->OnScreen() &&\
                        *(*(fleetStorage))[alien] ==\
                        hero->GetHeroEchelon()
    #define ALIEN_WALKED_ENOUGH_WITHOUT_FIRE\
                (*(fleetStorage))[alien]->GetStepsWithoutFire() ==\
                ALIENFLEET_ONE_MAXSTEPSWITHOUTFIRE
    #define HERO_IS_ALIVE hero->IsItGone() == false

    for (int alien = 0; alien < COUNTER; ++alien)
    {

        if (ALIEN_IS_ABSENT) continue;

        #ifdef ALIEN_CAN_SHOOT
            if (HERO_IS_ALIVE && ALIEN_IN_HEROECHELON && 
                                            ALIEN_WALKED_ENOUGH_WITHOUT_FIRE)
            {
                 AlienLazer* lazer = new (std::nothrow) 
                AlienLazer{(*(fleetStorage))[alien]->GetLazerStart(),
                                &tcollection->Pictures()[tn::alien_laser01]};
                if (!lazer || (lazer->Status() == false)) continue;
                fleetLazerStorage->Push(lazer);
                (*(fleetStorage))[alien]->ResetStepsWithoutFire();
            }

        #endif

        if (ALIEN_WALKED_ENOUGH_WITHOUT_FIRE)
        {
            (*(fleetStorage))[alien]->ResetStepsWithoutFire();
        }

        (*(fleetStorage))[alien]->StrightMove();

        if ((*(fleetStorage))[alien]->IsItGone())
            fleetStorage->Remove(alien);
    }

    #undef COUNTER
    #undef HERO_IS_ALIVE
    #undef ALIEN_IS_ABSENT
    #undef ALIEN_IN_HEROECHELON
    #undef ALIEN_WALKED_ENOUGH_WITHOUT_FIRE
    #undef ALIENFLEET_ONE_MAXSTEPSWITHOUTFIRE
 

}


void FirstFleet::MoveFleetLazers()
{
    fleetLazerStorage->Move();
}

void FirstFleet::ShowFleet(const Sdl* sdl) const
{
    #define ALIEN_IS_not_ONSCREEN !(*(fleetStorage))[alien]->OnScreen()
    #define TMP_ALIEN_IS_not_ONSCREEN\
            !(*(tmp_fleetStorage))[alien]->OnScreen()
    #define ALIEN_IS_ABSENT !(*(fleetStorage))[alien]
    #define TMP_ALIEN_IS_ABSENT !(*(tmp_fleetStorage))[alien]
    #define COUNTER fleetStorage->GetCounter()
    #define TMP_COUNTER tmp_fleetStorage->GetCounter()

    /*Если существует временное хранилище, то рисуем его*/
    if (tmp_fleetStorage)
    {
        for (int alien = 0; alien < TMP_COUNTER; ++alien)
        {
            if (TMP_ALIEN_IS_ABSENT)       continue;
            if (TMP_ALIEN_IS_not_ONSCREEN) continue;
            (*(tmp_fleetStorage))[alien]->Show(sdl);
        }
    }
    else
    /*Иначе рисуем основное хранилище*/
    {
        for (int alien = 0; alien < COUNTER; ++alien)
        {
            if (ALIEN_IS_ABSENT)       continue;
            if (ALIEN_IS_not_ONSCREEN) continue;
            (*(fleetStorage))[alien]->Show(sdl);
        }
    }
    


    #undef TMP_ALIEN_IS_not_ONSCREEN
    #undef TMP_ALIEN_IS_ABSENT
    #undef TMP_COUNTER
    #undef ALIEN_IS_not_ONSCREEN
    #undef ALIEN_IS_ABSENT
    #undef COUNTER
}

void FirstFleet::ShowFleetLazers(const Sdl* sdl) const
{
    fleetLazerStorage->Show(sdl);
}

void FirstFleet::CheckFleetCrashHero(NHero* hero, status_t& status,
                                        ObjectsList<DieComplex>* dieStorage)
{
    #define ALIEN_IS_ABSENT !(*(fleetStorage))[alien]
    #define ALIEN_isnot_ONSCREEN (*(fleetStorage))[alien]->OnScreen()\
                                                                       == false

    for (int alien = 0; alien < fleetStorage->GetCounter(); ++alien)
    {
        if (ALIEN_IS_ABSENT) continue;
        if (ALIEN_isnot_ONSCREEN) break;
        if (*(*(fleetStorage))[alien] == hero)
        {
            fleetStorage->Remove(alien);
            dieStorage->Push(Make_DieComplex(hero->GetCenter(), tcollection));
            hero->ItIsGoneNow();
            status.hero_dead = true;
            return;
        }
    }

    #undef ALIEN_IS_ABSENT
    #undef ALIEN_isnot_ONSCREEN   
}


void FirstFleet::CheckFleetLazerHitsHero(NHero* hero, status_t& status,
                    ObjectsList<DieComplex>* dieStorage)
{
     if (fleetLazerStorage->Check_withObject(hero))
    {
        /*Если героя подбивают, показываем череп*/
        dieStorage->Push(Make_DieComplex(hero->GetCenter(), tcollection));
        status.hero_dead = true;
    }   
}


void FirstFleet::ClearFleetLazers()
{
    fleetLazerStorage->Check_and_clear();
}

