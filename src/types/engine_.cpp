#include "engine_.h"
#include "../core/core.h"

#define CURRENTFLEET_ALIVE gameFleetsArray[currentFleet]->GetFleetOverStatus()\
                                                             == false
#define CURRENTFLEET gameFleetsArray[currentFleet]

Engine_::Engine_(const tc* collection, const texture_* digits)
{
    if (!collection || !digits)
    {
        init = false; return;
    }
    tcollection = collection;
    digits_ = digits;

    gameFleetsArray = 
                new (std::nothrow) GameFleet_ABC* [fleets::allFleets] {nullptr};
    if (!gameFleetsArray)
    {
        init = false; return;
    }

    
    if (!fillGameFleetsArray(collection, digits))
    {
        init = false; return;
    }
    if (!makeHeroLazerStorage())
    {
        init = false; return;
    }
    if (!makeDieStorage())
    {
        init = false; return;
    }
    if (!makeAnimatedList())
    {
        init = false; return;
    }
}


bool Engine_::makeAnimatedList()
{
    animatedList = new (std::nothrow) ObjectsList<Apack>();
    if (!animatedList) return false;
    return true;
}

bool Engine_::makeHeroLazerStorage()
{
    heroLazerStorage = 
                    new (std::nothrow) HeroLazerStorage{HERO_LAZERSTORAGE_CAP};
    if (!heroLazerStorage || heroLazerStorage->Status() == false)
    {
        return false;
    }
    return true;
}

bool Engine_::makeDieStorage()
{
    dieStorage = new (std::nothrow) ObjectsList<DieComplex>();
    if (!dieStorage)
    {
         return false;
    }
    return true;
}

/*Заполнение флотов*/
bool  Engine_::fillGameFleetsArray(const tc* collection, const texture_* digits)
{
    gameFleetsArray[fleets::firstfleet] = 
                        new (std::nothrow) FirstFleet{collection, digits,
                                                        ALIENFLEET_ONE_CAP};
    if (!gameFleetsArray[fleets::firstfleet] ||
        gameFleetsArray[fleets::firstfleet]->Status() == false)
    {
        init = false; return false;
    }
    return true;
}


Engine_::~Engine_()
{
    tcollection = nullptr;
    digits_ = nullptr;
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
    delete animatedList;
    animatedList = nullptr;
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

void Engine_::showAnimated_repeated(const Sdl* sdl) const
{
    animatedList->Show(sdl, tn::flow::repeated);
}

void Engine_::showAnimated_once(const Sdl* sdl) const
{
    animatedList->Show(sdl, tn::flow::once);
}

void Engine_::showFleet(const Sdl* sdl) const
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->ShowFleet(sdl);
}

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
        CURRENTFLEET->CheckFleetCrashHero(hero, status, dieStorage, animatedList);
}

bool Engine_::checkHeroLazerHitsFleet(status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        return CURRENTFLEET->CheckHeroLazerHitsFleet(heroLazerStorage, 
                                                     dieStorage, status,
                                                     animatedList);
    return false;
}

void Engine_::checkFleetLazerHitsHero(NHero* hero, status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->CheckFleetLazerHitsHero(hero, status, dieStorage, 
                                                animatedList);
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

void Engine_::clearAnimated()
{
    if (animatedList->IsEmpty()) return;
    animatedList->Check_and_clear();
}



void Engine_::InPause(const Sdl* sdl, status_t& status, GameInfoClass* gameInfo)
{
    showHeroLazers(sdl);
    showFleet(sdl);
    showDieStoreage(sdl);
    showFleetLazers(sdl);
    gameInfo->ShowGameInfo(sdl, status);
}

void Engine_::InGameFlow(Sdl* sdl, NHero* hero, status_t& status,
                        GameInfoClass* gameInfo, Border* b, Sky* s, Gui* gui)
{
    #define GAME_OVER status.gameIsOver == true

    if (GAME_OVER) return;

    showFleet(sdl);
    moveFleet(hero, status);
    checkFleetCrashHero(hero, status); // здесь есть анимация
    showHeroLazers(sdl);
    moveHeroLazers();
    if (checkHeroLazerHitsFleet(status)) //здесь тоже анимация
        gameInfo->ChangeScore(status);
    showDieStoreage(sdl);
    //
    showAnimated_repeated(sdl);
    //
    showFleetLazers(sdl);
    moveFleetLazers();
    checkFleetLazerHitsHero(hero, status);
    clearFleetLazers();
    moveDieStorage();
    //
    clearAnimated();
    //
    clearDieStorage();
    checkFleetsIsGone(status);
    checkTmpFleetIsGone(hero, status);
    if (IsGameOver(sdl, gameInfo, status, b, s, gui))
    {
        hero->Reincarnate(); return;
    }

    #undef GAME_OVER
}




bool Engine_::IsGameOver(Sdl* sdl, GameInfoClass* gameInfo,
                                status_t& status, Border* b, Sky* s, Gui* gui)
{
    if (status.gameIsOver)
    {

        gui->ResetGameOver();
        while (!status.gameQuit)
        {
            SDL_RenderClear(sdl->Renderer());
            borderSky_show_moving(sdl, b, s);
            gameInfo->ShowGameInfo(sdl, status);
            gui->ShowGameOver(sdl);
            gui->MoveGameOver(); 
            SDL_RenderPresent(sdl->Renderer());
            if (gui->IsGameOverMoving()) continue;
            while (SDL_PollEvent(&sdl->event()) != 0)
            {
                if (sdl->event().type == SDL_QUIT)
                {
                    status.gameQuit = true; return true;
                }
                else if (sdl->event().type == SDL_KEYDOWN &&
                    sdl->event().key.repeat == 0)
                {
                    switch (sdl->event().key.keysym.sym)
                    {
                        default:
                        {
                            status.mainMenu = true;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


void Engine_::checkFleetsIsGone(status_t& status)
{
    if (gameFleetsArray[currentFleet]->GetFleetOverStatus())
    {
        currentFleet++;
        if ( (currentFleet >= fleets::allFleets) || 
                                            (!gameFleetsArray[currentFleet]))
        {
            status.gameIsOver = true;
        }
    }
}

void  Engine_::checkTmpFleetIsGone(NHero* hero, status_t& status)
{
    if (status.gameIsOver) return;
    /*Если временные ушли за экран*/
    if (gameFleetsArray[currentFleet]->TmpFleetIsEmpty())
    {
        gameFleetsArray[currentFleet]->RemakeFleet(status);
        gameFleetsArray[currentFleet]->DeletingAllLazers();
        dieStorage->ClearList();
        heroLazerStorage->Clear();
        hero->ResetOnScreen(true);
        hero->IsLiveNow();
        hero->Reincarnate();
    }
}



bool Engine_::Reincarnate()
{
    if (!fillGameFleetsArray(tcollection, digits_)) return false;
    if (!makeHeroLazerStorage()) return false;
    if (!makeDieStorage()) return false;
    return true;
}




#undef CURRENTFLEET_ALIVE
#undef CURRENTFLEET

