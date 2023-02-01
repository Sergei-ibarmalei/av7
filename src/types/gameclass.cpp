#include "gameclass.h"

GameClass::GameClass(Sdl& sdl, tc& collection)
{
    sdl_ = &sdl;
    initStatus();
    gui = new (std::nothrow) Gui(collection.Strings());
    if (!gui || gui->Status() == false)
    {
        init = false; return;
    }

    if (!(initBorder()))
    {
        init = false; return;
    }

    if (!(initSky(&collection.Pictures()[tn::star])))
    {
        init = false; return;
    }

    if (!(initGameInfo(collection)))
    {
        init = false; return;
    }


    nHero = new NHero(&collection.Pictures()[tn::hero]);
    if (!nHero || nHero->Status() == false)
    {
        init = false; return;
    }

    if (!initEngine(collection))
    {
        init = false; return;
    } 
   

}

bool GameClass::RestartEngine(const tc& collection)
{
    delete engine;
    engine = nullptr;
    delete gameInfo;
    gameInfo = nullptr;
    restartStatus();
    if (!initGameInfo(collection)) return false;
    if (!initEngine(collection)) return false;
    return true;
}

bool GameClass::initEngine(const tc& collection)
{
    engine = new (std::nothrow) Engine_(&collection, 
                                        gameInfo->HeapDigits());
    if (!engine || engine->Status() == false) return false;
    return true;
}

bool GameClass::initGameInfo(const tc& collection)
{
    gameInfo = new (std::nothrow) GameInfoClass(collection, status);
    if (!gameInfo || gameInfo->Status() == false) return false;
    return true;
}

bool GameClass::initBorder()
{
    border = new (std::nothrow) Border();
    if (!border || border->Status() == false) return false;
    return true;
}

bool GameClass::initSky(texture_* starTexture)
{
    sky = new (std::nothrow) Sky(starTexture);
    if (!sky || sky->Status() == false) return false;
    return true;
}

GameClass::~GameClass()
{
    sdl_ = nullptr;
    delete border; border = nullptr;
    delete sky; sky = nullptr;
    delete gameInfo; gameInfo = nullptr;


    delete nHero; nHero = nullptr;
    delete engine;
    engine = nullptr;

}

void GameClass::initStatus()
{
    status.heroIntro = true;
    status.gameQuit = false;
    status.gameIsOver = false;
    status.mainMenu = true;
    status.pause = false;
    status.partOne = false;
    status.partTwo = false;
    status.HeroLives = HERO_LIVES;
    status.gameScore = 0;
    status.hero_dead = false;
    status.aliens_go_back = false;

    #ifdef STOP_FLEET_MOVING
        status.stop_fleet_moving = false;
    #endif
}

void GameClass::restartStatus()
{
    status.heroIntro = true;
    status.gameQuit = false;
    status.gameIsOver = false;
    status.pause = false;
    status.partOne = false;
    status.partTwo = false;
    status.HeroLives = HERO_LIVES;
    status.gameScore = 0;
    status.hero_dead = false;
    status.aliens_go_back = false;

    #ifdef STOP_FLEET_MOVING
        status.stop_fleet_moving = false;
    #endif
}

bool GameClass::flow(const tc& collection)
{
    while (!status.gameQuit)
    {
        SDL_RenderClear(sdl_->Renderer());
        if (status.mainMenu)
        {
            gui->ShowMainMenu(sdl_, status);
        }
        if (status.partOne)
        {

            if (!RestartEngine(collection))
                status.gameQuit = true;

            if (!partOne()) return false;
        }
    }
    return true;
}

void GameClass::check_key_events()
{
    while (SDL_PollEvent(&sdl_->event()) != 0)
    {
        if (sdl_->event().type == SDL_QUIT) status.gameQuit = true;
        else if(sdl_->event().type == SDL_KEYDOWN &&
            sdl_->event().key.repeat == 0)
        {
            switch (sdl_->event().key.keysym.sym)
            {
                case SDLK_UP:
                {
                    nHero->HeroUp(); break;
                }
                case SDLK_DOWN:
                {
                    nHero->HeroDown(); break;
                }
                case SDLK_RIGHT:
                {
                    nHero->HeroRight(); break;
                }
                case SDLK_LEFT:
                {
                    nHero->HeroLeft(); break;
                }
                case SDLK_ESCAPE:
                {
                    status.pause = true; break;
                }
                case SDLK_SPACE:
                {
                        engine->MakeHeroLazer(nHero->LazerStart(), status); 
                        break;
                }
                #ifdef STOP_FLEET_MOVING
                    case SDLK_z:
                    {
                        status.stop_fleet_moving = !status.stop_fleet_moving;
                        break;
                    }
                #endif
                 
                default: {}
            }
        }
        else if(sdl_->event().type == SDL_KEYUP)
            nHero->HeroStop();

    }
}

void GameClass::pauseIsPressed()
{
    while (!status.gameQuit || !status.pause)
    {
        SDL_RenderClear(sdl_->Renderer());
        nHero->Show(sdl_);

        borderSky_show_moving(sdl_, border, sky);
        engine->InPause(sdl_, status, gameInfo);
        gui->ShowPause(sdl_);
        
        while (SDL_PollEvent(&sdl_->event()) != 0)
        {
            if (sdl_->event().type == SDL_QUIT)
            {
                status.gameQuit = true;
                status.pause = false;
                return;
            }
            else if(sdl_->event().type == SDL_KEYDOWN &&
                sdl_->event().key.repeat == 0)
            {
                switch (sdl_->event().key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        status.pause = false; return;
                    }
                    case SDLK_q:
                    {
                        status.mainMenu = true; return;
                    }
                    default: {}
                }
            }
        }
        SDL_RenderPresent(sdl_->Renderer());
    }
}

void GameClass::showHeroIntro()
{
    while (!status.gameQuit || !status.pause)
    {
        if (status.heroIntro == false) return;
        SDL_RenderClear(sdl_->Renderer());
        nHero->Show(sdl_);
        borderSky_show_moving(sdl_, border, sky);
        gameInfo->ShowGameInfo(sdl_, status);
        nHero->HeroMovesInIntro(status);

        while (SDL_PollEvent(&sdl_->event()) != 0)
        {
            if (sdl_->event().type == SDL_QUIT)
            {
                status.heroIntro = false;
                status.gameQuit = true;
                status.pause = false;
                return;
            }
            else if (sdl_->event().type == SDL_KEYDOWN &&
                sdl_->event().key.repeat == 0)
            {
                switch (sdl_->event().key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        status.pause = true; return;
                    }
                    default: {}
                }
            }
        }
        SDL_RenderPresent(sdl_->Renderer());

    }
}


