#include "n_ob.h"

ObjectsStore::ObjectsStore(const tc* collection, const texture_* heap_digits)
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


    dieScoresStorage = new (std::nothrow) ObjectsList<DieScoresComplex>();
    if (!dieScoresStorage)
    {
        init = false; return;
    }

    alienLazerStorage = new (std::nothrow) ObjectsList<AlienLazer>();
    if (!alienLazerStorage)
    {
        init = false; return;
    }

}

ObjectsStore::~ObjectsStore()
{
    tcollection = nullptr;
    delete heroLazerStorage;
    heroLazerStorage = nullptr;
    delete alienFleetOneStorage;
    alienFleetOneStorage = nullptr;
    delete dieScoresStorage;
    dieScoresStorage = nullptr;
    delete alienLazerStorage;
    alienLazerStorage = nullptr;
}

void ObjectsStore::MoveHeroLazers()
{
    bool flag_StartSort = false;
    heroLazerStorage->Move(flag_StartSort);
    if (flag_StartSort)
    {
        heroLazerStorage->Sort(HERO_LAZERSTORAGE_CAP);
    }
}

void ObjectsStore::ShowHeroLazers(const Sdl* sdl) const
{
    heroLazerStorage->Show(sdl);
}



bool ObjectsStore::MakeHeroLazer(const plot* start)
{
    /*Если это первый выстрел*/
    if (heroLazerStorage->GetCounter() == 0)
    {
        HeroLazer* lazer = new (std::nothrow) HeroLazer{start,
                                    &tcollection->Pictures()[tn::blue_laser]};
        if (!lazer || (lazer->Status() == false)) return false;
            return heroLazerStorage->Push(lazer);

        return heroLazerStorage->Push(lazer);
    }
  
    #define COUNTER heroLazerStorage->GetCounter()
    #define PREVLAZER heroLazerStorage->operator[](COUNTER - 1)
    #define PREVLAZER_X PREVLAZER->Lazer_x()
    #define PREVLAZER_W PREVLAZER->Lazer_w()
    /*Если предыдущий выстрел слишком близко, то ничего не делаем*/
    if ( (PREVLAZER_X - start->x) < PREVLAZER_W * 3) return false;
    HeroLazer* lazer = new (std::nothrow) HeroLazer{start,
                                    &tcollection->Pictures()[tn::blue_laser]};
    if (!lazer || (lazer->Status() == false)) return false;
    return heroLazerStorage->Push(lazer);


    #undef PREVLAZER_X
    #undef PREVLAZER_W
    #undef PREVLAZER
    #undef COUNTER
}


bool  ObjectsStore::Checks_herolazer_plainAlien(status_t& status)
{
    #define HEROLAZER *heroLazerStorage->operator[](l)
    #define ALIEN *alienFleetOneStorage->operator[](a)
    #define HEROLAZER_ABSENT heroLazerStorage->operator[](0) == nullptr
    #define CURRENT_HEROLAZER_ABSENT heroLazerStorage->operator[](l) == nullptr
    #define ALIEN_ABSENT alienFleetOneStorage->operator[](a) == nullptr
    #define ALIEN_outSCREEN !alienFleetOneStorage->operator[](a)->OnScreen()
    #define ALIEN_SCORE alienFleetOneStorage->operator[](a)->GetScoreWeight()
    #define ALIEN_CENTER alienFleetOneStorage->operator[](a)->GetCenter()


    bool score_changed {false};
    if ( HEROLAZER_ABSENT ) return false;
    for (int l = 0; l < heroLazerStorage->GetCounter(); ++l)
    {
        if ( CURRENT_HEROLAZER_ABSENT ) break;
        for (int a = 0; a < alienFleetOneStorage->GetCapacity(); ++a)
        {
            if ( ALIEN_ABSENT ) continue;
            if (ALIEN_outSCREEN) break;

            if (ALIEN == HEROLAZER)
            {
                alienFleetOneStorage->operator[](a)->ItIsGoneNow();
                heroLazerStorage->operator[](l)->ResetOnScreen(false);
                heroLazerStorage->Sort(HERO_LAZERSTORAGE_CAP);
                status.gameScore += ALIEN_SCORE;
                score_changed = true;
                dieScoresStorage->Push(make_scoreComplex(ALIEN_CENTER, ALIEN_SCORE));
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

DieScoresComplex* ObjectsStore::make_scoreComplex(const plot* ship_center,
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
            DieScoresComplex* dsc = 
            new (std::nothrow) DieScoresComplex{ship_center, &digits[score]};
            if (!dsc || (dsc->Status() == false)) return nullptr;
            return dsc;
        }
        case 2:
        {
            hi = score / 10;
            low = score % 10;
            DieScoresComplex* dsc = 
            new (std::nothrow) DieScoresComplex{ship_center, &digits[hi],
                                                &digits[low]};
            if (!dsc || (dsc->Status() == false)) return nullptr;
            return dsc;
        }
        default: { return nullptr;}
    }

}

void ObjectsStore::ShowDieScores(const Sdl* sdl) const
{
    dieScoresStorage->Show(sdl);
}

void ObjectsStore::MoveDieScores()
{
    dieScoresStorage->Move();
}

void ObjectsStore::ClearDieScores()
{
    dieScoresStorage->Check();
}

void ObjectsStore::ShowAlienFleetOneLazers(const Sdl* sdl) const
{
    alienLazerStorage->Show(sdl);
}

void ObjectsStore::MoveAlienFleetOneLazers()
{
    alienLazerStorage->Move();
}

