#include "n_ob.h"

Engine::Engine(const tc* collection, const texture_* heap_digits)
{
    if (!collection)
    {
        init = false; return;
    }
    tcollection = collection;
    if (!heap_digits)
    {
        init = false; return;
    }
    digits = heap_digits;
    heroLazerStorage = new (std::nothrow) 
                                        HeroLazerStorage{HERO_LAZERSTORAGE_CAP};
    if (!heroLazerStorage)
    {
        init = false; return;
    }
    alienFleetOneStorage = new (std::nothrow) 
                                    AlienFleet_oneStorage{ALIENFLEET_ONE_CAP};
    if (!alienFleetOneStorage)
    {
        init = false; return;
    }
    if (!makeAlienFleetOne(collection))
    {
        init = false; return;
    }


    dieStorage = new (std::nothrow) ObjectsList<DieComplex>();
    if (!dieStorage)
    {
        init = false; return;
    }

    alienLazerStorage = new (std::nothrow) ObjectsList<AlienLazer>();
    if (!alienLazerStorage)
    {
        init = false; return;
    }

    alienFleetTmpStorage = nullptr;

}

Engine::~Engine()
{
    tcollection = nullptr;
    delete heroLazerStorage;
    heroLazerStorage = nullptr;
    delete alienFleetOneStorage;
    alienFleetOneStorage = nullptr;
    delete dieStorage;
    dieStorage = nullptr;
    delete alienLazerStorage;
    alienLazerStorage = nullptr;
    delete alienFleetTmpStorage;
    alienFleetTmpStorage = nullptr;
}

void Engine::MoveHeroLazers()
{
    bool flag_StartSort = false;
    heroLazerStorage->Move(flag_StartSort);
    if (flag_StartSort)
    {
        heroLazerStorage->Sort(HERO_LAZERSTORAGE_CAP);
    }
}

void Engine::ShowHeroLazers(const Sdl* sdl) const
{
    heroLazerStorage->Show(sdl);
}



bool Engine::makeHeroLazer(const plot* start)
{
    if (!start) return false;
    /*Если это первый выстрел*/
    if (heroLazerStorage->GetCounter() == 0)
    {
        HeroLazer* lazer = new (std::nothrow) HeroLazer{start,
                                    &tcollection->Pictures()[tn::blue_laser]};
        if (!lazer || (lazer->Status() == false)) return false;

        return heroLazerStorage->Push(lazer);
    }
  
    #define COUNTER heroLazerStorage->GetCounter()
    #define PREVLAZER heroLazerStorage->operator[](COUNTER - 1)
    #define PREVLAZER_X PREVLAZER->Lazer_x()
    #define PREVLAZER_W PREVLAZER->Lazer_w()
    /*Если предыдущий выстрел слишком близко, то ничего не делаем*/
    if ( (PREVLAZER_X - start->x) < PREVLAZER_W * 3) return true;
    HeroLazer* lazer = new (std::nothrow) HeroLazer{start,
                                    &tcollection->Pictures()[tn::blue_laser]};
    if (!lazer || (lazer->Status() == false)) return false;
    return heroLazerStorage->Push(lazer);


    #undef PREVLAZER_X
    #undef PREVLAZER_W
    #undef PREVLAZER
    #undef COUNTER
}

void  Engine::Checks_alienlazer_hitsHero(NHero* hero, status_t& status)
{
    if (alienLazerStorage->Check_withObject(hero))
    {
        /*Если героя подбивают, показываем череп*/
        dieStorage->Push(make_DieComplex(hero->GetCenter()));
        status.hero_dead = true;
    }
}


bool  Engine::Checks_herolazer_hitsAlien(status_t& status)
{
    #define HEROLAZER *(*(heroLazerStorage))[l]
    #define ALIEN *(*(alienFleetOneStorage))[a]
    #define HEROLAZER_ABSENT (*(heroLazerStorage))[0] == nullptr
    #define CURRENT_HEROLAZER_ABSENT (*(heroLazerStorage))[l] == nullptr
    #define ALIEN_ABSENT (*(alienFleetOneStorage))[a] == nullptr
    #define ALIEN_outSCREEN !(*(alienFleetOneStorage))[a]->OnScreen()
    #define ALIEN_SCORE (*(alienFleetOneStorage))[a]->GetScoreWeight()
    #define ALIEN_CENTER (*(alienFleetOneStorage))[a]->GetCenter()


    bool score_changed {false};
    if ( HEROLAZER_ABSENT ) return false;
    for (int l = 0; l < heroLazerStorage->GetCounter(); ++l)
    {
        if ( CURRENT_HEROLAZER_ABSENT ) break;
        for (int a = 0; a < alienFleetOneStorage->GetCounter(); ++a)
        {
            if ( ALIEN_ABSENT ) continue;
            if (ALIEN_outSCREEN) break;

            if (ALIEN == HEROLAZER)
            {
                (*(alienFleetOneStorage))[a]->ItIsGoneNow();
                (*(heroLazerStorage))[l]->ResetOnScreen(false);
                heroLazerStorage->Sort(HERO_LAZERSTORAGE_CAP);
                status.gameScore += ALIEN_SCORE;
                score_changed = true;
                dieStorage->
                    Push(make_DieComplex(ALIEN_CENTER, ALIEN_SCORE));
                break;
            }
        }
    }

    

    #undef ALIEN_CENTER
    #undef HEROLAZER
    #undef ALIEN
    #undef HEROLAZER_ABSENT
    #undef CURRENT_HEROLAZER_ABSENT
    #undef ALIEN_ABSENT
    #undef ALIEN_outSCREEN
    #undef ALIEN_SCORE
    
    return score_changed;
}


DieComplex* Engine::make_DieComplex(const plot* ship_center)
{
    DieComplex* dsc = 
    new (std::nothrow) DieComplex(ship_center, 
                                &tcollection->Pictures()[tn::scull]);
    if (!dsc || dsc->Status() == false) return nullptr;
    return dsc;
}

/// @brief Создание комплекса летающего счета или черепа
/// @param ship_center - центр корабля для отсчета координат
/// @param score - счет, из которого создается комплекс
/// @param scull - true - если нужно создать череп героя вместо счета
/// @return 
DieComplex* Engine::make_DieComplex(const plot* ship_center,
                                                const int score)
{
    if (score <= 0) return nullptr;

    int complexLength = score / 10;
    int hi, low;
    if (complexLength < 1) complexLength = 1;
    else complexLength = 2;


    switch (complexLength)
    {
        case 1:
        {
            DieComplex* dsc = 
            new (std::nothrow) DieComplex{ship_center, &digits[score]};
            if (!dsc || (dsc->Status() == false)) return nullptr;
            return dsc;
        }
        case 2:
        {
            hi = score / 10;
            low = score % 10;
            DieComplex* dsc = 
            new (std::nothrow) DieComplex{ship_center, &digits[hi],
                                                &digits[low]};
            if (!dsc || (dsc->Status() == false)) return nullptr;
            return dsc;
        }
        default: { return nullptr;}
    }

}

void Engine::ShowDieScores(const Sdl* sdl) const
{
    dieStorage->Show(sdl);
}

void Engine::MoveDieScores()
{
    dieStorage->Move();
}

/*Очистка списка DieScores*/
void Engine::ClearDieScores()
{
    dieStorage->Check_and_clear();
}

void Engine::ShowAlienFleetOneLazers(const Sdl* sdl) const
{
    alienLazerStorage->Show(sdl);
}

void Engine::MoveAlienFleetOneLazers()
{
    alienLazerStorage->Move();

}

/*Очистка списка выстрелянных лазеров алиенов*/
void Engine::ClearAlienLazers()
{
    alienLazerStorage->Check_and_clear();
}

bool Engine::MakeHeroLazer(const plot* start)
{
    return makeHeroLazer(start);
}




void Engine::DoGameAlgorithm(NHero* hero, const Sdl* sdl, 
                        status_t& status, GameInfoClass* gameInfo)
{
    #define GAMEOVER status.gameIsOver == true

    if (GAMEOVER) return;
    ShowAlienFleetOne(sdl);
    MoveAlienFleetOne(hero, status);
    CheckAleinFleetOneHitsHero(hero, status);
    ShowHeroLazers(sdl);
    MoveHeroLazers();
    if (Checks_herolazer_hitsAlien(status))
        gameInfo->ChangeScore(status);
    ShowDieScores(sdl);
    ShowAlienFleetOneLazers(sdl);
    MoveAlienFleetOneLazers();
    //
    Checks_alienlazer_hitsHero(hero, status);
    //
    ClearAlienLazers();
    MoveDieScores();
    ClearDieScores(); 
    Checks_isHeroDead(status);
    
    #undef GAMEOVER

}

void Engine::InPause(const Sdl* sdl, status_t& status, 
                                GameInfoClass* gameInfo)
{
    ShowHeroLazers(sdl);
    ShowAlienFleetOne(sdl);
    ShowDieScores(sdl);
    ShowAlienFleetOneLazers(sdl);
    gameInfo->ShowGameInfo(sdl, status);
}

void Engine::Checks_isHeroDead(status_t& status)
{
    #define NOSCORES_NOLAZERS dieStorage->IsEmpty()&&\
                                    alienLazerStorage->IsEmpty()
    /*if (status.hero_dead)
    {
        //status.HeroLives--;
        if (status.HeroLives <=0)
        {
            status.gameIsOver = true;
            return;
        }
    }*/

    if (status.hero_dead && NOSCORES_NOLAZERS)
    {

        status.hero_dead = false;
        /*TODO*/
        if (make_tmpAlienFleetOneStorage(status)) 
        {
            status.aliens_go_back = true;
        }
    }

    #undef NOSCORES_NOLAZERS
}



