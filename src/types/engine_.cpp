#include "engine_.h"
#include "../core/core.h"

#define CURRENTFLEET_ALIVE (gameFleetsArray[currentFleet]->GetFleetOverStatus()\
                                                             == false)
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

bool  Engine_::MakeHeroLazer(const plot* start_pos, status_t& status)
{
    if (!start_pos) return false;
    /*Если это первый выстрел*/
    if (heroLazerStorage->GetCounter() == 0)
    {
        HeroLazer* lazer = new (std::nothrow) HeroLazer{start_pos,
                                    &tcollection->Pictures()[tn::blue_laser]};
        if (!lazer || (lazer->Status() == false)) return false;

        heroLazerStorage->Push(lazer);
        return true;
    }
  
    #define COUNTER heroLazerStorage->GetCounter()
    #define PREVLAZER heroLazerStorage->operator[](COUNTER - 1)
    #define PREVLAZER_X PREVLAZER->Lazer_x()
    #define PREVLAZER_W PREVLAZER->Lazer_w()
    
    /*Если предыдущий выстрел слишком близко, то ничего не делаем*/
    if ( (PREVLAZER_X - start_pos->x) < PREVLAZER_W * 3) return false;
    HeroLazer* lazer = new (std::nothrow) HeroLazer{start_pos,
                                    &tcollection->Pictures()[tn::blue_laser]};
    if (!lazer || (lazer->Status() == false))
    {
        status.gameQuit = true; return false;
    }
    heroLazerStorage->Push(lazer);
    return true;
    
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

void Engine_::showAnimated_once(const Sdl* sdl, bool stop) const
{
    animatedList->Show(sdl, tn::flow::once, stop);
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

void Engine_::moveFleet(const Sdl* sdl, NHero* hero, status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->MoveFleet(hero, status, sdl->SoundEffects());
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

//Движение черепа и/или счета за подбитие
void Engine_::moveDieStorage()
{
    dieStorage->Move();
}

//Проверка - врезался ли корабль в алиена из флота
void Engine_::checkFleetCrashHero(const Sdl* sdl, NHero* hero, status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->CheckFleetCrashHero(hero, status, dieStorage, 
                                        animatedList, sdl->SoundEffects());
}

//Проверка - подбил ли герой алиена из флота
bool Engine_::checkHeroLazerHitsFleet(const Sdl* sdl, status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        return CURRENTFLEET->CheckHeroLazerHitsFleet(heroLazerStorage, 
                                                     dieStorage, status,
                                                     animatedList,
                                                     sdl->SoundEffects());
    return false;
}

//Проверка - подбит ли герой лазером алиена
void Engine_::checkFleetLazerHitsHero(const Sdl* sdl, 
                                      NHero* hero, status_t& status)
{
    if (CURRENTFLEET_ALIVE)
        CURRENTFLEET->CheckFleetLazerHitsHero(hero, status, dieStorage, 
                                            animatedList, sdl->SoundEffects());
}

//Очистка списка лазеров флота алиенов
void Engine_::clearFleetLazers()
{
    if (CURRENTFLEET_ALIVE)
    {
        CURRENTFLEET->ClearFleetLazers();
    }
}

//Очистка списка счетов за подбитие алиена
void Engine_::clearDieStorage()
{
    if (dieStorage->IsEmpty()) return;
    dieStorage->Check_and_clear();
}

//Очистка списка анимаций взрывов
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
    showAnimated_once(sdl, true);

    showFleetLazers(sdl);
    gameInfo->ShowGameInfo(sdl, status);
}

void Engine_::InGameFlow(Sdl* sdl, NHero* hero, 
                        status_t& status,
                        GameInfoClass* gameInfo, 
                        Border* b, 
                        Sky* s, 
                        Gui* gui)
{

    #define GAME_OVER status.gameIsOver == true
    #define DIESTORAGE_EMPTY dieStorage->IsEmpty()
    #define ANIMATED_EMPTY animatedList->IsEmpty()

    //Если гейм овер и вся анимация завершилась, выходим наверх
    if (GAME_OVER && ANIMATED_EMPTY && DIESTORAGE_EMPTY) return;

    showFleet(sdl);
    moveFleet(sdl, hero, status);
    checkFleetCrashHero(sdl, hero, status); 
    showHeroLazers(sdl);
    moveHeroLazers();
    if (checkHeroLazerHitsFleet(sdl, status))
        gameInfo->ChangeScore(status);
    showDieStoreage(sdl);
    //
    showAnimated_once(sdl);
    //
    showFleetLazers(sdl);
    moveFleetLazers();
    checkFleetLazerHitsHero(sdl, hero, status);
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
    

    #undef DIESTORAGE_EMPTY
    #undef ANIMATED_EMPTY
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
            showDieStoreage(sdl);
            showAnimated_once(sdl);
            moveDieStorage();
            clearDieStorage();
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
        if( (currentFleet >= fleets::allFleets) ||
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

