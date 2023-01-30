#ifndef GAMEFLEETABC_H
#define GAMEFLEETABC_H

#include "objectslist.h"
#include "alienstorage.h"
#include "herolazerstorage.h"
#include "alienlazer.h"
#include "texturescollection.h"
#include "diecomplex.h"

class GameFleet_ABC
{
    protected:
    bool init {true};
    bool fleetIsOver {false};
    const tc* tcollection;
    const texture_* digits;
    int fleetCapacity;
    AlienStorage* fleetStorage;
    AlienStorage* tmp_fleetStorage;
    ObjectsList<AlienLazer>* fleetLazerStorage;

    bool makeTmpFleetStorage(status_t& status);
    virtual bool makeFleet(const tc* collection) = 0;


    public:
    GameFleet_ABC(const tc* collection, const texture_* heap_digits);
    virtual ~GameFleet_ABC() = 0;

    bool Status() const {return init;}
    bool CheckHeroLazerHitsFleet(HeroLazerStorage* heroLazerStorage, 
                        ObjectsList<DieComplex>* dieStorage, status_t& status);
    void CheckFleetLazerHitsHero(NHero* hero, status_t& status,
                            ObjectsList<DieComplex>* dieStorage);
    void DeletingAllLazers();

    virtual void MoveFleet(NHero* hero, status_t&  status) = 0;
    virtual void MoveFleetLazers() = 0;

    virtual void ShowFleet(const Sdl* sdl) const = 0;
    virtual void ShowFleetLazers(const Sdl* sdl) const = 0;

    virtual void CheckFleetCrashHero(NHero* hero, status_t& status,
                                ObjectsList<DieComplex>* dieStorage) = 0;


    virtual void ClearFleetLazers() = 0;
    ArrStorageABC* Fleet() {return fleetStorage;}
    bool FleetIsOver() const {return fleetIsOver;}
    bool TmpFleetIsEmpty() const;
    virtual void RemakeFleet(status_t& status) = 0;

};


#endif