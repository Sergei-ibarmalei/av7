#ifndef ANIMATEDPACK_H
#define ANIMATEDPACK_H

#include "texturescollection.h"
#include "sdlclass.h"


/*Class Animated pack of textures*/


class Apack
{
    protected:
    bool init {true};
    int packCapacity;
    int frame;
    texture_* tpack;

    void setCoords(plot* center);

    public:
    Apack() {}
    Apack(texture_* animPack, const int animPackCap, plot* center);
    Apack(const Apack&) = delete;
    Apack& operator=(const Apack&) = delete;
     ~Apack();
     
    /// @brief Показ анимации
    /// @param sdl  sdl 
    /// @param f анимация с повтором(repeated) или без (once)
    /// @param stop В паузе анимация останавливается
    void Show(const Sdl* sdl, const tn::flow f, bool stop = false);
    bool IsItGone() const {return frame == (packCapacity-1);}
    bool Status() const {return init;}
};





#endif