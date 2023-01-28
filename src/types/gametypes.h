#ifndef GAMETYPES_H
#define GAMETYPES_H

#include "sdltypes.h"
#include "test.h"

typedef struct 
{
    bool heroIntro;
    bool mainMenu;
    bool pause;
    bool partOne;
    bool partTwo;
    int  HeroLives;
    bool gameQuit;
    bool gameIsOver;
    int  gameScore;
    bool hero_dead;
    bool aliens_go_back;

    #ifdef STOP_FLEET_MOVING
        bool stop_fleet_moving;
    #endif
    
} status_t;

enum borderSides {borderUp,
                  borderDown,
                  borderRight,
                  borderLeft,
                  blackBanner,
                  allBorderSides};

#endif