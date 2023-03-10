#include "dieobject.h"

DieObject::DieObject(const texture_* textures):
    ElementaryObject(textures)
{
    Velocities()->x = 0;
    Velocities()->y = DIESCORE_VELOCITY;
    stepsCount = 0;
}

void DieObject::move_object()
{
    if (IsItGone()) return;
    resetUpLeftCorner();
    stepsCount++;
    if (stepsCount == DIEOBJECT_PATHLENGTH) ItIsGoneNow();
}

void DieObject::Move()
{
    move_object();
}

void DieObject::Show(const Sdl* sdl) const
{
    ShowObj(sdl);
}