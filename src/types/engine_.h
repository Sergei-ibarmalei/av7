#ifndef ENGINE__H
#define ENGINE__H

#include "baselazer.h"
#include "nhero.h"
#include "objectslist.h"
#include "test.h"
#include "texturescollection.h"
#include "gameInfoClass.h"
#include "diecomplex.h"
#include "herolazer.h"
#include "alienlazer.h"
#include "alien.h"
#include "herolazerstorage.h"
#include "alienstorage.h"
#include "firstfleet.h"



class Engine_
{
    private:
    int currentFleet = fleets::firstfleet;
    bool init {true};
    const tc* tcollection;
    GameFleet_ABC** gameFleetsArray;
    HeroLazerStorage* heroLazerStorage;

    ObjectsList<DieComplex>* dieStorage;

    void showDieStoreage(const Sdl* sdl) const;
    void showHeroLazers(const Sdl* sdl) const;
    void showFleet(const Sdl* sdl) const;
    void showFleetLazers(const Sdl* sdl) const;

    void moveFleet(NHero* hero, status_t& status);
    void moveHeroLazers();
    void moveFleetLazers();
    void moveDieStorage();

    void checkFleetCrashHero(NHero* hero, status_t& status);
    bool checkHeroLazerHitsFleet(status_t& status);
    void checkFleetLazerHitsHero(NHero* hero, status_t& status);
    bool checkHeroStatus(NHero* hero, status_t& status);

    void clearFleetLazers();
    void clearDieStorage();

    public:
    Engine_(const tc* collection, const texture_* heap_digits);
    ~Engine_();
    Engine_(const Engine_&) = delete;
    Engine_& operator=(const Engine_&) = delete;

    bool Status() const {return init;}
    void MakeHeroLazer(const plot* start_pos, status_t& status);
    void InPause(const Sdl* sdl, status_t& status, GameInfoClass* gameInfo);
    void InGameFlow(const Sdl* sdl, NHero* hero, status_t& status,
                    GameInfoClass* gameInfo);
};








#endif


