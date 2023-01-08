#include "gameclass.h"
#include "../core/core.h"


bool GameClass::partOne(log_::Log& log)
{
    while (!status.gameQuit)
    {
        if (status.mainMenu) return true;
        action();
        SDL_RenderClear(sdl_->Renderer());
        borderSky_show_moving();
        gameInfo->ShowGameInfo(sdl_, status);



        SDL_RenderPresent(sdl_->Renderer());
    }
    return true;
}





