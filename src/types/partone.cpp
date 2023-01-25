#include "gameclass.h"
#include "../core/core.h"

#define HERO_ECHELON nHero->GetHeroEchelon()

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
        objectsStore->ShowAlienFleetOne(sdl_);
        objectsStore->MoveAlienFleetOne(HERO_ECHELON); 
        objectsStore->ShowHeroLazers(sdl_);
        objectsStore->MoveHeroLazers();
        if (objectsStore->Checks_herolazer_plainAlien(status))
            gameInfo->ChangeScore(status);
        objectsStore->ShowDieScores(sdl_);
        objectsStore->ShowAlienFleetOneLazers(sdl_);
        objectsStore->MoveAlienFleetOneLazers(); 
        objectsStore->MoveDieScores();
        objectsStore->ClearDieScores();



        borderSky_show_moving();
        gameInfo->ShowGameInfo(sdl_, status);
        if (status.pause) pauseIsPressed();
        SDL_RenderPresent(sdl_->Renderer());       

    }
    return true;
}





