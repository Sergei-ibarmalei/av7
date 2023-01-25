#include "n_ob.h"

AlienFleet_oneStorage::AlienFleet_oneStorage(const int capacity): 
                                                ArrStorageABC(capacity)
{
    if (!init) return;
}



Alien* AlienFleet_oneStorage::operator[](const int index)
{
    if (index < 0 || index >= counter)
    {
        return nullptr;
    }
    return static_cast<Alien*>(storage[index]);
}

