#ifndef ALIENLAZER_H
#define ALIENLAZER_H


#include "baselazer.h"
#include "nhero.h"


class AlienLazer: public BaseLazer
{
    public:
    AlienLazer(const plot* start, const texture_* t);
    bool operator==(NHero& hero);
};


#endif