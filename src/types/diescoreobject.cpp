#include "n_ob.h"

DieScoresObject::DieScoresObject(const texture_* textures):
    ElementaryObject(textures)
{
    Velocities()->x = 0;
    Velocities()->y = DIESCORE_VELOCITY;
    stepsCount = 0;
}

void DieScoresObject::move_object()
{
    if (IsItGone()) return;
    resetUpLeftCorner();
    stepsCount++;
    if (stepsCount == pathLength) ItIsGoneNow();
}

void DieScoresObject::Move()
{
    move_object();
}

void DieScoresObject::Show(const Sdl* sdl) const
{
    ShowObj(sdl);
}