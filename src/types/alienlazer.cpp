#include "n_ob.h"

AlienLazer::AlienLazer(const plot* start, const texture_* t):
            BaseLazer(start, dir::left, t)
{
    Velocities()->x = ALIENLAZER_VELOCITY;
    Velocities()->y = 0;
}