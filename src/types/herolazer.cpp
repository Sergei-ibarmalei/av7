#include "n_ob.h"

HeroLazer::HeroLazer(const plot* start, const texture_* t):
    BaseLazer(start, dir::right, t)
{
    Velocities()->x = HEROLAZER_VELOCITY;
    Velocities()->y = 0;
}

