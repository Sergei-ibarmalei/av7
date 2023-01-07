#ifndef SKYCLASS_H
#define SKYCLASS_H

#include "sdlclass.h"
#include "../consts/gameconsts.h"
#include "../loging/loging.h"

class Sky
{
    private:
    int fastStarMax {5};
    int slowStarMax {4};
    rect_* fast {nullptr};
    rect_* slow {nullptr};
    texture_* starTexture {nullptr};
    bool init {true};
    void setStarsCoords();

    public:
    explicit Sky(texture_* t, log_::Log& log);
    ~Sky();
    Sky(const Sky& ) = delete;
    Sky& operator=(const Sky& ) = delete;
    bool Status() const {return init;}
    void MoveSky();
    void ShowSky(Sdl* sdl);


};

#endif