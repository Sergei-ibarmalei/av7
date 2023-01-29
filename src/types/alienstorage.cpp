#include "alienstorage.h"

AlienStorage::AlienStorage(const int capacity): 
                                                ArrStorageABC(capacity)
{
    if (!init) return;
}



Alien* AlienStorage::operator[](const int index)
{
    if (index < 0 || index >= counter)
    {
        return nullptr;
    }
    return static_cast<Alien*>(storage[index]);
}

