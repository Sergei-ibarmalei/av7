#include "movingfleets.h"
#include "../core/checking.h"

#define toPlainAlien_t1 static_cast<PlainAlien_t1*>

void move(obNode* shipFirst)
{
    if (!shipFirst) 
    {
        return;
    }
    toPlainAlien_t1(shipFirst->object)->Move();

    #define MAINRECT_X static_cast<PlainAlien_t1*>(shipFirst->object)->GetMainRect_x()
    if (hasCrossedRight(MAINRECT_X))
        toPlainAlien_t1(shipFirst->object)->ResetOnScreen(true);

    if (hasCrossedLeft(MAINRECT_X))
        toPlainAlien_t1(shipFirst->object)->ResetOnScreen(false);
    #undef MAINRECT_X
    move(shipFirst->next);



}

void Move_at1_fleet(GameClass* gc)
{
   if (gc->gameFleets->Alien_t1_fleet_first() == nullptr) return;
   move(gc->gameFleets->Alien_t1_fleet_first());

}

#undef toPlainAlien_t1 