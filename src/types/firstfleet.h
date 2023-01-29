#ifndef FIRSTFLEET_H
#define FIRSTFLEET_H

#include "gamefleetabc.h"

class FirstFleet: public GameFleet_ABC
{
    private:
    bool makeFirstFleet(const tc* collection);

    public:
    FirstFleet(const tc* collection, const texture_* heap_digits);
    FirstFleet(const FirstFleet&) = delete;
    ~FirstFleet() {}
    FirstFleet& operator=(const FirstFleet&) = delete;

    void MoveFleet(NHero* hero, status_t& status) override;
    void MoveFleetLazers() override;

    void ShowFleet(const Sdl* sdl) const override;
    void ShowFleetLazers(const Sdl* sdl) const override;

    void CheckFleetCrashHero(NHero* hero, status_t& status,
                            ObjectsList<DieComplex>* dieStorage) override;


    void ClearFleetLazers() override;
                    
};

#endif