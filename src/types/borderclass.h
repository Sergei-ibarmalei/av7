#ifndef BORDERCLASS_H
#define BORDERCLASS_H

#include "sdlclass.h"
#include "gametypes.h"
#include "../consts/gameconsts.h"

class Border
{
    private:
    rect_* border;
    bool init {true};
    void setBorder();

    public:
    Border();
    ~Border();
    Border& operator=(const Border& ) = delete;
    Border(const Border& ) = delete;
    bool Status() const {return init;}
    void ShowBorder(const Sdl* sdl) const;
};
#endif