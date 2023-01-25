#include "gameclass.h"
#include "../core/core.h"

bool GameClass::partOne()
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
        nHero->Move();
        nHero->Show(sdl_);
        engine->DoGameAlgorithm(nHero, sdl_, status, gameInfo);


        borderSky_show_moving();
        gameInfo->ShowGameInfo(sdl_, status);
        if (status.pause) pauseIsPressed();
        SDL_RenderPresent(sdl_->Renderer());       

    }
    return true;
}





