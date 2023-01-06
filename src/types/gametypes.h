#ifndef GAMETYPES_H
#define GAMETYPES_H

#include "sdltypes.h"

typedef struct 
{
    bool mainMenu;
    bool pause;
    bool partOne;
    bool partTwo;
    int  HeroLives;
    bool gameQuit;
} status_t;
#endif