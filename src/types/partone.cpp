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
        nHero->Move();
        nHero->Show(sdl_);
        //gameFleets->Alien_t1_Show(sdl_);
        //gameFleets->FleetMove();
        objectsStore->ShowAlienFleetOne(sdl_);
        objectsStore->MoveAlienFleetOne(); 
        objectsStore->ShowHeroLazers(sdl_);
        objectsStore->MoveHeroLazers();
        borderSky_show_moving();
        gameInfo->ShowGameInfo(sdl_, status);
        objectsStore->Checks_herolazer_plainAlien();

        //Checks_lazer_plainAlien(this);


        if (status.pause) pauseIsPressed();
        SDL_RenderPresent(sdl_->Renderer());       

    }
    return true;
}





