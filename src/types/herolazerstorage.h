#ifndef HEROLAZERSTORAGE_H
#define HEROLAZERSTORAGE_H

#include "arrstorageabc.h"
#include "herolazer.h"

class HeroLazerStorage: public ArrStorageABC
{
    public:
    explicit HeroLazerStorage(const int capacity);
    ~HeroLazerStorage() {}
    HeroLazerStorage(const HeroLazerStorage&) = delete;
    HeroLazerStorage& operator=(const HeroLazerStorage&) = delete;

    HeroLazer* operator[](const int index);
    void Move(bool& flag_toStartSort);
    void Show(const Sdl* sdl) const;
};



#endif