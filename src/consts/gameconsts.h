#ifndef GAMECONSTS_H
#define GAMECONSTS_H

#include "graphconsts.h"

#define VELOCITY_FOR_RUNBACK 5

#define HERO_LIVES 3
#define HERO_VELOCITY_X 3
#define HERO_VELOCITY_Y 3
#define HERO_LAZERSTORAGE_CAP 5

#define HERO_ECHELON_HI 70
#define HERO_ECHELON_LOW 70

#define BORDER_THICKNESS 5
#define UP_BORDER_X 0
#define UP_BORDER_Y 80
#define UP_BORDER_W   S_W
#define UP_BORDER_H   BORDER_THICKNESS 
#define DOWN_BORDER_X UP_BORDER_X 
#define DOWN_BORDER_Y S_H - BORDER_THICKNESS 
#define DOWN_BORDER_W UP_BORDER_W 
#define DOWN_BORDER_H BORDER_THICKNESS 
#define LEFT_BORDER_X 0
#define LEFT_BORDER_Y UP_BORDER_Y + BORDER_THICKNESS 
#define LEFT_BORDER_W BORDER_THICKNESS 
#define LEFT_BORDER_H DOWN_BORDER_Y 
#define RIGHT_BORDER_X S_W - BORDER_THICKNESS 
#define RIGHT_BORDER_Y LEFT_BORDER_Y 
#define RIGHT_BORDER_W BORDER_THICKNESS 
#define RIGHT_BORDER_H LEFT_BORDER_H

#define FAST_STAR_VELOCITY 2
#define SLOW_STAR_VELOCITY 1

#define PLAINLASER_VELOCITY 3
#define PLAINLASER_OFFSET 20

#define HEROLAZER_VELOCITY 3

#define PLAINALIENLASER_OFFSET 1
#define PLAINALIENLASER_VELOCITY 3

#define ALIENFLEET_ONE_CAP 25
#define ALIENFLEET_ONE_VELOCITY 2
#define ALIENFLEET_ONE_VELOCITY_BACK 5
#define ALIENFLEET_ONE_SPACE_BETWEEN 550
#define ALIENFLEET_ONE_MAXSTEPSWITHOUTFIRE 200

#define ALIENLAZER_VELOCITY ALIENFLEET_ONE_VELOCITY+1

#define DIESCORE_VELOCITY -1

#define GAMEOVER_CAPACITY 3


/*Направление движения*/
namespace dir
{
    enum direction {right, left, up, down};
}

/*Пересечения*/
namespace re
{
    /*прям. пересечений героя*/
    enum  heros {one, two, three, four, five, allR};

    /*алиен тип первый*/
    enum  alien_t1 {t1_one, t1_two, t1_three, t1_allR};
}

namespace scores
{
    enum weight {plainAlien = 5,};
}

namespace fleets
{
    enum {firstfleet, secondfleet, allFleets};
}

namespace gameover
{
    enum gostatus {moves, stops,};
}



#endif