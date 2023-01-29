#ifndef BASELAZER_H
#define BASELAZER_H

#include "elementaryobject.h"
#include "../consts/gameconsts.h"

class BaseLazer: public ElementaryObject
{
    protected:
    dir::direction direct;

    public:
    BaseLazer(const plot* start, dir::direction d, const texture_* t);
    BaseLazer(const BaseLazer&) = delete;
    BaseLazer& operator=(const BaseLazer&) = delete;
    virtual ~BaseLazer() {}
    void Move();
    int Lazer_x() const;
    int Lazer_y() const;
    int Lazer_w() const;
    void Show(const Sdl* sdl) const;
};


#endif