#include "core.h"

bool mainCore()
{
    log_::Log gameLog;
    Sdl sdl("app", gameLog);
    if (sdl.Status() == false)
    {
        gameLog.Show(); return false;
    }

    tc collection(sdl.Renderer(), gameLog);
    if (collection.Status() == false)
    {
        gameLog.Show(); return false;
    }
    GameClass gc(sdl, collection, gameLog);
    if (gc.Status() == false)
    {
        gameLog.Show(); return false;
    }
    if (!gc.flow(gameLog))
    {
        gameLog.Show(); return false;
    }

    return true;
}