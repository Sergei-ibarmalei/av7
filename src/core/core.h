#ifndef CORE_H
#define CORE_H

//#include "../types/sdlclass.h"
#include "../types/gameclass.h"
#include "../types/borderclass.h"
#include "../types/skyclass.h"
#include "../types/diecomplex.h"

bool mainCore();
DieComplex* Make_DieComplex(const texture_* digits, const plot* ship_center,
                                                const int score);
DieComplex* Make_DieComplex(const plot* ship_center, const tc* collection);
void borderSky_show_moving(const Sdl* sdl, Border* border, Sky* sky);
//void BorderSky_show_moving(Sdl* sdl, Border* border, Sky* sky);

#endif