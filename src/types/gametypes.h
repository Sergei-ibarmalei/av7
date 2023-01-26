#ifndef GAMETYPES_H
#define GAMETYPES_H

#include "sdltypes.h"

typedef struct 
{
    bool heroIntro;
    bool mainMenu;
    bool pause;
    bool partOne;
    bool partTwo;
    int  HeroLives;
    bool gameQuit;

    int  gameScore;
    bool hero_dead;
} status_t;

enum borderSides {borderUp,
                  borderDown,
                  borderRight,
                  borderLeft,
                  blackBanner,
                  allBorderSides};

#endif