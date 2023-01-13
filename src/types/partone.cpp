#include "gameclass.h"
#include "../core/core.h"



bool GameClass::partOne(log_::Log& log)
{
    while (!status.gameQuit)
    {
 
        if (status.mainMenu) return true;
        if (status.heroIntro)
        {
            showHeroIntro();
            if (status.pause) pauseIsPressed();
            continue;
        }
        check_key_events();
        SDL_RenderClear(sdl_->Renderer());
        temp_hero->Move();
        //laserStore->ShowLaserStore(sdl_);
        stdlaserStore->ShowLaserStore(sdl_);
        temp_hero->ShowObj(sdl_);
        //laserStore->MoveLaserStore();
        stdlaserStore->MoveLaserStore();
        borderSky_show_moving();
        gameInfo->ShowGameInfo(sdl_, status);
        #ifdef SHOW_COL_R
            temp_hero->showColR(sdl_);
        #endif


        if (status.pause) pauseIsPressed();
        SDL_RenderPresent(sdl_->Renderer());       

    }
    return true;
}





