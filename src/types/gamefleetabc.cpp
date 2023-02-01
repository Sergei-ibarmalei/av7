#include "gamefleetabc.h"
#include "../core/core.h"


GameFleet_ABC::GameFleet_ABC(const tc* colleciton, const texture_* heap_digits)
{
    if (!colleciton || !heap_digits)
    {
        init = false; return;
    }
    fleetStorage = nullptr;
    tmp_fleetStorage = nullptr;
    tcollection = colleciton;
    digits = heap_digits;

}

GameFleet_ABC::~GameFleet_ABC()
{
    delete fleetStorage; 
    fleetStorage = nullptr;
    delete tmp_fleetStorage;
    tmp_fleetStorage = nullptr;
    tcollection = nullptr;
    digits = nullptr;
}

bool GameFleet_ABC::CheckHeroLazerHitsFleet(HeroLazerStorage *heroLazerStorage,
                                            ObjectsList<DieComplex> *dieStorage,
                                            status_t &status)
{
    #define HEROLAZER *(*(heroLazerStorage))[lazer]
    #define ALIEN *(*(fleetStorage))[alien]
    #define HEROLAZER_ABSENT (*(heroLazerStorage))[0] == nullptr
    #define CURRENT_HEROLAZER_ABSENT (*(heroLazerStorage))[lazer] == nullptr
    #define ALIEN_ABSENT (*(fleetStorage))[alien] == nullptr
    #define ALIEN_outSCREEN !(*(fleetStorage))[alien]->OnScreen()
    #define ALIEN_SCORE  (*(fleetStorage))[alien]->GetScoreWeight()
    #define ALIEN_CENTER (*(fleetStorage))[alien]->GetCenter()
    #define HEROLAZER_HITS_ALIEN ALIEN==HEROLAZER


    bool score_changed {false};
    if (HEROLAZER_ABSENT) return false;
    for (int lazer = 0; lazer < heroLazerStorage->GetCounter(); ++lazer)
    {
        if (CURRENT_HEROLAZER_ABSENT) break;
        for (int alien = 0; alien < fleetStorage->GetCounter(); ++alien)
        {
            if (ALIEN_ABSENT) continue;
            if (ALIEN_outSCREEN) break;
            if (HEROLAZER_HITS_ALIEN)
            {
                (*(fleetStorage))[alien]->ItIsGoneNow();

                (*(heroLazerStorage))[lazer]->ResetOnScreen(false);

                heroLazerStorage->Sort(HERO_LAZERSTORAGE_CAP);

                status.gameScore += ALIEN_SCORE;
                score_changed = true;
                dieStorage->Push(Make_DieComplex(digits, ALIEN_CENTER, 
                                                            ALIEN_SCORE));
                fleetStorage->Remove(alien);
                checksIsFleetOver();
                break;
            }
        }

    }
    return score_changed;


    #undef HEROLAZER_HITS_ALIEN
    #undef HEROLAZER
    #undef ALIEN
    #undef HEROLAZER_ABSENT
    #undef CURRENT_HEROLAZER_ABSENT
    #undef ALIEN_ABSENT
    #undef ALIEN_outSCREEN
    #undef ALIEN_SOCRE
    #undef ALIEN_CENTER





}

void GameFleet_ABC::CheckFleetLazerHitsHero(NHero* hero, status_t& status,
            ObjectsList<DieComplex>* dieStorage)
{
     if (fleetLazerStorage->Check_withObject(hero))
    {
        /*Если героя подбивают, показываем череп*/
        dieStorage->Push(Make_DieComplex(hero->GetCenter(), tcollection));
        makeTmpFleetStorage(status);
        status.hero_dead = true;
        status.HeroLives -= 1;
        if (status.HeroLives <= 0)
        {
            status.gameIsOver = true;
        }
    }
}

/*Создание временного хранилища из алиенов, оставшихся на экране*/
bool GameFleet_ABC::makeTmpFleetStorage(status_t& status)
{
    #define ALIEN_IS_ABSENT !(*(fleetStorage))[alien]
    #define ALIEN_IS_ON_SCREEN (*(fleetStorage))[alien]->OnScreen()

    /*Если действующий флот не пустой*/
    if (fleetStorage->IsEmpty() == false)
    {
        /*Подсчитываем количество оставшихся на экране алиенов*/
        int lastOnScreen = 0;
        for (int alien = 0; alien < fleetCapacity; ++alien)
        {
            if (ALIEN_IS_ABSENT) continue;
            if (ALIEN_IS_ON_SCREEN) lastOnScreen++;
            else break;
        }
        if (lastOnScreen <= 0) return false;
        /*Создаем временное хранилище*/
        tmp_fleetStorage = 
            new (std::nothrow) AlienStorage {lastOnScreen};
        if (!tmp_fleetStorage || tmp_fleetStorage->Status() == false)
        {
            status.gameQuit = true;
            return false;
        }

        for (int alien = 0; alien < fleetCapacity; ++alien)
        {
            if (ALIEN_IS_ABSENT) continue;
            if (ALIEN_IS_ON_SCREEN)
            {
                //Толкаем во временное хранилище алиена
                tmp_fleetStorage->Push((*(fleetStorage))[alien]);
                //В постоянном хранилище на старом месте заносим nullptr
                fleetStorage->Clear_at(alien);
                continue;
            }
            //Всех остальных в постоянном хранилище удаляем
            fleetStorage->Remove(alien);
        }
        return true;
    }
    return false;

    #undef ALIEN_IS_ON_SCREEN
    #undef ALIEN_IS_ABSENT
}


bool GameFleet_ABC::TmpFleetIsEmpty() const
{
    if (!tmp_fleetStorage) return false;
    return (tmp_fleetStorage->IsEmpty());
}

void GameFleet_ABC::DeletingAllLazers()
{
    fleetLazerStorage->ClearList();
}

void GameFleet_ABC::checksIsFleetOver()
{
    if (fleetStorage->GetLiveSize() == 0)
    {
        fleetIsOver = true;
    }
}

