#include "n_ob.h"

HeroLazerStorage::HeroLazerStorage(const int capacity): ArrStorageABC(capacity)
{
    if (init == false) return;
}





HeroLazer* HeroLazerStorage::operator[](const int index)
{
    if (index < 0 || index >= counter) return nullptr;
    return static_cast<HeroLazer*>(storage[index]);
}



void HeroLazerStorage::Move(bool& flag_toStartSort)
{
    for (int i = 0; i < counter; ++i)
    {
        static_cast<HeroLazer*>(storage[i])->Move();
        if (static_cast<HeroLazer*>(storage[i])->OnScreen() == false)
            flag_toStartSort = true;
    }
}

void HeroLazerStorage::Show(const Sdl* sdl) const
{
    for (int i = 0; i < counter; ++i)
    {
        if (storage[i])
            static_cast<HeroLazer*>(storage[i])->Show(sdl);
    }
}

