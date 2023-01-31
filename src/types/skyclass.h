#ifndef SKYCLASS_H
#define SKYCLASS_H

#include "sdlclass.h"
#include "../consts/gameconsts.h"

class Sky
{
    private:
    enum {fastMax = 5, slowMax = 4};
    int fastStarMax {fastMax};
    int slowStarMax {slowMax};
    rect_* fast {nullptr};
    rect_* slow {nullptr};
    texture_* starTexture {nullptr};
    bool init {true};
    void setStarsCoords();

    public:
    explicit Sky(texture_* t);
    ~Sky();
    Sky(const Sky& ) = delete;
    Sky& operator=(const Sky& ) = delete;
    bool Status() const {return init;}
    void MoveSky();
    void ShowSky(const Sdl* sdl) const;


};

#endif