//#include "n_ob.h"
#include "../core/rand.h"
#include "../core/core.h"

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

/*Движение флота алиенов*/
void Engine::MoveAlienFleetOne(NHero* hero, status_t& status)
{
    /*Если герой подбит, то не двигаем флот прямо*/
    if (status.hero_dead) return;
    #ifdef STOP_FLEET_MOVING
        if (status.stop_fleet_moving) return;
    #endif

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

        #ifdef ALIEN_CAN_SHOOT
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

        #endif

        if (ALIEN_WALKED_ENOUGH_WITHOUT_FIRE)
        {
            (*(alienFleetOneStorage))[alien]->ResetStepsWithoutFire();
        }

        (*(alienFleetOneStorage))[alien]->StrightMove();

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

/*Проверка на столкновение алиена и героя*/
void Engine::Checks_AleinFleetOneHitsHero(NHero* hero, status_t& status)
{
    #define ALIEN_IS_ABSENT !(*(alienFleetOneStorage))[alien]
    #define ALIEN_isnot_ONSCREEN (*(alienFleetOneStorage))[alien]->OnScreen()\
                                                                       == false

    for (int alien = 0; alien < alienFleetOneStorage->GetCounter(); ++alien)
    {
        if (ALIEN_IS_ABSENT) continue;
        if (ALIEN_isnot_ONSCREEN) break;
        if (*(*(alienFleetOneStorage))[alien] == hero)
        {
            alienFleetOneStorage->Remove(alien);
            dieStorage->Push(make_DieComplex(hero->GetCenter()));
            hero->ItIsGoneNow();
            status.hero_dead = true;
            return;
        }
    }

    #undef ALIEN_IS_ABSENT
    #undef ALIEN_isnot_ONSCREEN
}

void Engine::ShowAlienFleetOne(const Sdl* sdl) const
{
    #define ALIEN_IS_not_ONSCREEN !(*(alienFleetOneStorage))[alien]->OnScreen()
    #define TMP_ALIEN_IS_not_ONSCREEN\
            !(*(alienFleetTmpStorage))[alien]->OnScreen()
    #define ALIEN_IS_ABSENT !(*(alienFleetOneStorage))[alien]
    #define TMP_ALIEN_IS_ABSENT !(*(alienFleetTmpStorage))[alien]
    #define COUNTER alienFleetOneStorage->GetCounter()
    #define TMP_COUNTER alienFleetTmpStorage->GetCounter()

    /*Если существует временное хранилище, то рисуем его*/
    if (alienFleetTmpStorage)
    {
        for (int alien = 0; alien < TMP_COUNTER; ++alien)
        {
            if (TMP_ALIEN_IS_ABSENT)       continue;
            if (TMP_ALIEN_IS_not_ONSCREEN) continue;
            (*(alienFleetTmpStorage))[alien]->Show(sdl);
        }
    }
    else
    /*Иначе рисуем основное хранилище*/
    {
        for (int alien = 0; alien < COUNTER; ++alien)
        {
            if (ALIEN_IS_ABSENT)       continue;
            if (ALIEN_IS_not_ONSCREEN) continue;
            (*(alienFleetOneStorage))[alien]->Show(sdl);
        }
    }
    


    #undef TMP_ALIEN_IS_not_ONSCREEN
    #undef TMP_ALIEN_IS_ABSENT
    #undef TMP_COUNTER
    #undef ALIEN_IS_not_ONSCREEN
    #undef ALIEN_IS_ABSENT
    #undef COUNTER
}

/*Временное хранилище алиенов для ухода с экрана*/
bool Engine::make_tmpAlienFleetOneStorage(status_t& status)
{
    #define ALIEN_IS_ABSENT !(*(alienFleetOneStorage))[alien]
    #define ALIEN_IS_ON_SCREEN (*(alienFleetOneStorage))[alien]->OnScreen()

    /*Если список действующих алиенов не пустой*/
    if (alienFleetOneStorage->IsEmpty() == false)
    {
        /*Подсчитываем количество оставшихся на экране алиенов*/
        int lastOnScreen = 0;
        for (int alien = 0; alien < ALIENFLEET_ONE_CAP; ++alien)
        {
            if (ALIEN_IS_ABSENT) continue;
            if (ALIEN_IS_ON_SCREEN) lastOnScreen++;
            else break;
        }
        if (lastOnScreen <= 0) return false;
        /*Создаем временное хранилище*/
        alienFleetTmpStorage = 
                new (std::nothrow) AlienStorage {lastOnScreen};
        if (!alienFleetTmpStorage || alienFleetTmpStorage->Status() == false)
        {
            status.gameQuit = true;
            return false;
        }
        for (int alien = 0; alien < ALIENFLEET_ONE_CAP; ++alien)
        {
            if (ALIEN_IS_ABSENT) continue;
            if (ALIEN_IS_ON_SCREEN)
            {
                //Толкаем во временное хранилище алиена
                alienFleetTmpStorage->Push((*(alienFleetOneStorage))[alien]);
                //В постоянном хранилище на старом месте заносим nullptr
                alienFleetOneStorage->Clear_at(alien);
                continue;
            }
            //Все остальное в постоянном хранилище удаляем
            alienFleetOneStorage->Remove(alien);
        }
        return true;
    }
    return false;

    #undef ALIEN_IS_ON_SCREEN
    #undef ALIEN_IS_ABSENT
}