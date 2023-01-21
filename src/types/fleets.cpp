#include "n_ob.h"
#include "../core/rand.h"

bool ObjectsStore::makeAlienFleetOne(const tc* collection)
{
    #define RIGHT_SIDE RIGHT_BORDER_X+RIGHT_BORDER_W
    #define SHIP_MAINRECT_H collection->Pictures()[tn::alien_one].main_rect.h
    #define UP (UP_BORDER_Y+UP_BORDER_H)+SHIP_MAINRECT_H
    #define DOWN DOWN_BORDER_Y-SHIP_MAINRECT_H
    #define ALIEN_TEXTURE &collection->Pictures()[tn::alien_one]
    #define ALIEN_LASER_TEXTURE &collection->Pictures()[tn::alien_laser01]

    plot alien_start;
    for (int count = 0; count < ALIENFLEET_ONE_CAP; ++count)
    {
        alien_start.x = RIGHT_SIDE +
            (count * ALIENFLEET_ONE_SPACE_BETWEEN);
        alien_start.y = getRand(UP, DOWN);
        if (!alienFleetOneStorage->
            Push(new PlainAlien_t1{ALIEN_TEXTURE, &alien_start, 
                                   ALIEN_LASER_TEXTURE})) return false;
    }
    return true;
    

    #undef ALIEN_TEXTURE
    #undef ALIEN_LASER_TEXTURE
    #undef RIGHT_SIDE
    #undef SHIP_MAINRECT_H
    #undef DOWN
}

void ObjectsStore::MoveAlienFleetOne()
{
    #define COUNTER alienFleetOneStorage->GetCounter()
    #define ALIEN_IS_ABSENT !alienFleetOneStorage->operator[](alien)

    for (int alien = 0; alien < COUNTER; ++alien)
    {
        if (ALIEN_IS_ABSENT) continue;
        alienFleetOneStorage->operator[](alien)->Move();
        if (alienFleetOneStorage->operator[](alien)->IsItGone())
            alienFleetOneStorage->Remove(alien);
    }

    #undef COUNTER
    #undef ALIEN_IS_ABSENT
 
}

void ObjectsStore::ShowAlienFleetOne(const Sdl* sdl) const
{
    #define ALIEN_IS_ALIVE alienFleetOneStorage->\
                                operator[](alien)->IsItGone() == false
    #define ALIEN_IS_not_ONSCREEN alienFleetOneStorage->\
                                operator[](alien)->OnScreen() == false
    #define ALIEN_IS_ABSENT !alienFleetOneStorage->operator[](alien)
    #define COUNTER alienFleetOneStorage->GetCounter()
    
    for (int alien = 0; alien < COUNTER; ++alien)
    {

        if (ALIEN_IS_ABSENT) continue;
        if (ALIEN_IS_not_ONSCREEN)
        {
            continue;
        }
        alienFleetOneStorage->operator[](alien)->Show(sdl);
    }

    #undef ALIEN_IS_ALIVE
    #undef ALIEN_IS_not_ONSCREEN
    #undef ALIEN_IS_ABSENT
    #undef COUNTER
}

