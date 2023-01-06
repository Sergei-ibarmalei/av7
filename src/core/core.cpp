#include "core.h"

bool mainCore()
{
    log_::Log gameLog;
    Sdl sdl("app", gameLog);
    if (sdl.Status() == false) return false;

    TexturesCollection tc(sdl.Renderer(), gameLog);
    if (tc.Status() == false)
    {
        gameLog.Show();
        return false;
    }


    return true;
}