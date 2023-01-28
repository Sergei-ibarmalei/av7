#include "n_ob.h"


GameFleet_ABC::GameFleet_ABC(const tc* colleciton, const texture_* heap_digits)
{
    if (!colleciton || !heap_digits)
    {
        init = false; return;
    }
    fleetStorage = nullptr;
    tmp_fleetStorage = nullptr;
    fleetStorage_livesize = tmp_fleetStorage_livesize = 0;
    tcollection = colleciton;

}

GameFleet_ABC::~GameFleet_ABC()
{
    delete fleetStorage; 
    fleetStorage = nullptr;
    delete tmp_fleetStorage;
    tmp_fleetStorage = nullptr;

    tcollection = nullptr;
    digits = nullptr;
}