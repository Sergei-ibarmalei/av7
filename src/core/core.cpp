#include "core.h"

bool mainCore()
{
    Sdl sdl("app");
    if (sdl.Status() == false) return false;

    tc collection(sdl.Renderer());
    if (collection.Status() == false) return false;
    GameClass gc(sdl, collection);
    if (gc.Status() == false) return false;
    if (!gc.flow()) return false;


    return true;
}



