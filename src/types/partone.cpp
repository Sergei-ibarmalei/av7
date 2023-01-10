#include "gameclass.h"
#include "../core/core.h"



bool GameClass::partOne(log_::Log& log)
{
    while (!status.gameQuit)
    {
        if (status.mainMenu) return true;
        if (status.heroIntro)
        {
            //temp_hero->HeroMovesInIntro(status);
            showHeroIntro();
            if (status.pause) pauseIsPressed();
            continue;
        }
        check_key_events();
        SDL_RenderClear(sdl_->Renderer());
        borderSky_show_moving();
        gameInfo->ShowGameInfo(sdl_, status);
        temp_hero->ShowObj(sdl_);
        #ifdef SHOW_COL_R
            temp_hero->showColR(sdl_);
        #endif


        if (status.pause) pauseIsPressed();
        SDL_RenderPresent(sdl_->Renderer());
    }
    return true;
}





