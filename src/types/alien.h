#ifndef ALIEN_H
#define ALIEN_H

#include "alienabc.h"
#include "herolazer.h"
#include "nhero.h"


/// @brief Plain alien type one
class Alien: public AlienABC
{
    private:
    void setCr();
    public:
    Alien(const texture_* t, const plot* start, const texture_* lazer);
    ~Alien() {}
    Alien(const Alien&) = delete;
    Alien& operator=(const Alien&) = delete;
    bool operator==(const HeroLazer& hl);
    bool operator==(const echelon* heroEchelon);
    bool operator==(const NHero* hero);
    void Show(const Sdl* sdl);
};
#endif