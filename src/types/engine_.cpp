#include "engine_.h"

#define CURRENTFLEET_ALIVE gameFleetsArray[currentFleet]->FleetIsOver() == false
#define CURRENTFLEET gameFleetsArray[currentFleet]

Engine_::Engine_(const tc* collection, const texture_* digits)
{
    if (!collection || !digits)
    {
        init = false; return;
    }
    tcollection = collection;

    gameFleetsArray = 
                new (std::nothrow) GameFleet_ABC* [fleets::allFleets] {nullptr};
    if (!gameFleetsArray)
    {
        init = false; return;
    }

    

    gameFleetsArray[fleets::firstfleet] = 
                        new (std::nothrow) FirstFleet{collection, digits,
                                                        ALIENFLEET_ONE_CAP};
    if (!gameFleetsArray[fleets::firstfleet] ||
        gameFleetsArray[fleets::firstfleet]->Status() == false)
    {
        init = false; return;
    }



    heroLazerStorage = 
                    new (std::nothrow) HeroLazerStorage{HERO_LAZERSTORAGE_CAP};
    if (!heroLazerStorage || heroLazerStorage->Status() == false)
    {
        init = false; return;
    }

    dieStorage = new (std::nothrow) ObjectsList<DieComplex>();
    if (!dieStorage)
    {
        init = false; return;
    }

}

Engine_::~Engine_()
{
    tcollection = nullptr;
    delete heroLazerStorage;
    heroLazerStorage = nullptr;
    delete dieStorage;
    dieStorage = nullptr;
    for (int i = fleets::firstfleet; i < fleets::allFleets; ++i)
    {
        delete gameFleetsArray[i];
        gameFleetsArray[i] = nullptr;
    }
    delete gameFleetsArray;
    gameFleetsArray = nullptr;
}

void  Engine_::MakeHeroLazer(const plot* start_pos, status_t& status)
{
    if (!start_pos) return;
    /*Если это первый выстрел*/
    if (heroLazerStorage->GetCounter() == 0)
    {
        HeroLazer* lazer = new (std::nothrow) HeroLazer{start_pos,
                                    &tcollection->Pictures()[tn::blue_laser]};
        if (!lazer || (lazer->Status() == false)) return;

        heroLazerStorage->Push(lazer);
    }
  
    #define COUNTER heroLazerStorage->GetCounter()
    #define PREVLAZER heroLazerStorage->operator[](COUNTER - 1)
    #define PREVLAZER_X PREVLAZER->Lazer_x()
    #define PREVLAZER_W PREVLAZER->Lazer_w()
    /*Если предыдущий выстрел слишком близко, то ничего не делаем*/
    if ( (PREVLAZER_X - start_pos->x) < PREVLAZER_W * 3) return;
    HeroLazer* lazer = new (std::nothrow) HeroLazer{start_pos,
                                    &tcollection->Pictures()[tn::blue_laser]};
    if (!lazer || (lazer->Status() == false))
    {
        status.gameQuit = true; return;
    }
    heroLazerStorage->Push(lazer);


    #undef PREVLAZER_X
    #undef PREVLAZER_W
    #undef PREVLAZER
    #undef COUNTER
}

void Engine_::showHeroLazers(const Sdl* sdl) const
{
    heroLazerStorage->Show(sdl);
}


void Engine_::showDieStoreage(const Sdl* sdl) const
{
    dieStorage->Show(sdl);
}

//---------------------------------------------------------------------------
void Engine_::showFleet(const Sdl* sdl) const
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->ShowFleet(sdl);
}
//---------------------------------------------------------------------------

void Engine_::showFleetLazers(const Sdl* sdl) const
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->ShowFleetLazers(sdl);
}

void Engine_::moveFleet(NHero* hero, status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->MoveFleet(hero, status);
}

void Engine_::moveFleetLazers()
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->MoveFleetLazers();
}

void Engine_::moveHeroLazers()
{
    bool flag_StartSort = false;
    heroLazerStorage->Move(flag_StartSort);
    if (flag_StartSort)
    {
        heroLazerStorage->Sort(HERO_LAZERSTORAGE_CAP);
    }
}

void Engine_::moveDieStorage()
{
    dieStorage->Move();
}

void Engine_::checkFleetCrashHero(NHero* hero, status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->CheckFleetCrashHero(hero, status, dieStorage);
}

bool Engine_::checkHeroLazerHitsFleet(status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        return CURRENTFLEET->CheckHeroLazerHitsFleet(heroLazerStorage, 
                                                     dieStorage, status);
    return false;
}

void Engine_::checkFleetLazerHitsHero(NHero* hero, status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->CheckFleetLazerHitsHero(hero, status, dieStorage);
}

void Engine_::clearFleetLazers()
{
    if (CURRENTFLEET_ALIVE)
    {
        CURRENTFLEET->ClearFleetLazers();
    }
}

void Engine_::clearDieStorage()
{
    if (dieStorage->IsEmpty()) return;
    dieStorage->Check_and_clear();
}



void Engine_::InPause(const Sdl* sdl, status_t& status, GameInfoClass* gameInfo)
{
    showHeroLazers(sdl);
    showFleet(sdl);
    showDieStoreage(sdl);
    showFleetLazers(sdl);
    gameInfo->ShowGameInfo(sdl, status);
}

void Engine_::InGameFlow(const Sdl* sdl, NHero* hero, status_t& status,
                            GameInfoClass* gameInfo)
{
    #define GAME_OVER status.gameIsOver == true

    if (GAME_OVER) return;

    showFleet(sdl);
    moveFleet(hero, status);
    checkFleetCrashHero(hero, status);
    showHeroLazers(sdl);
    moveHeroLazers();
    if (checkHeroLazerHitsFleet(status))
        gameInfo->ChangeScore(status);
    showDieStoreage(sdl);
    showFleetLazers(sdl);
    moveFleetLazers();
    checkFleetLazerHitsHero(hero, status);
    clearFleetLazers();
    moveDieStorage();
    clearDieStorage();
    //Check: is hero dead??
    if (checkHeroStatus(hero, status) == true) return;

    #undef GAME_OVER
}

bool Engine_::checkHeroStatus(NHero* hero, status_t& status)
{
    /*Если временные ушли за экран*/
    if (gameFleetsArray[currentFleet]->TmpFleetIsEmpty())
    {
        gameFleetsArray[currentFleet]->RemakeFleet(status);
        gameFleetsArray[currentFleet]->DeletingAllLazers();
        heroLazerStorage->Clear();
        hero->ResetOnScreen(true);
        hero->IsLiveNow();
        hero->Reincarnate();
        return true;
    }
    return false;
}




#undef CURRENTFLEET_ALIVE
#undef CURRENTFLEET

