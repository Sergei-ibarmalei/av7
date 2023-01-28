#include "gameclass.h"

GameClass::GameClass(Sdl& sdl, tc& collection)
{
    sdl_ = &sdl;
    initStatus();
    mm = new (std::nothrow) MainMenu(collection.Strings());
    if (!mm)
    {
        gameClassStatus = false;
        return;
    }
    if (mm->Status() == false)
    {
        gameClassStatus = false;
        return;
    }
    if (!(initBorder()))
    {
        gameClassStatus = false; return;
    }

    if (!(initSky(&collection.Pictures()[tn::star])))
    {
        gameClassStatus = false; return;
    }

    if (!(initGameInfo(collection)))
    {
        gameClassStatus = false; return;
    }

    pause = new (std::nothrow) texture_[2];
    if (!pause)
    {
        gameClassStatus = false;
        return;       
    }
    initPause(collection);

    nHero = new NHero(&collection.Pictures()[tn::hero]);
    if (!nHero || nHero->Status() == false)
    {
        gameClassStatus = false;
        return;
    }

    
    engine = new (std::nothrow) Engine(&collection, 
                                        gameInfo->HeapDigits());
    if (!engine || engine->Status() == false)
    {
        gameClassStatus = false; return;
    }

   

}

void GameClass::initPause(tc& collection)
{

    pause[pause_] = collection.Strings()[tn::pause];
    pause[pressEscape] = collection.Strings()[tn::pressEscape];

    int centerPause_x = S_W / 2;
    int centerPause_y = S_H / 2;
    int centerPrEsc_x = S_W / 2;
    int centerPrEsc_y = S_H - 100;

    pause[pause_].main_rect.x = centerPause_x - pause[pause_].main_rect.w / 2;
    pause[pause_].main_rect.y = centerPause_y - pause[pause_].main_rect.h / 2;
    pause[pressEscape].main_rect.x = 
        centerPrEsc_x - pause[pressEscape].main_rect.w / 2;
    pause[pressEscape].main_rect.y = 
        centerPrEsc_y - pause[pressEscape].main_rect.h / 2;

}

bool GameClass::initGameInfo(tc& collection)
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
    delete mm; mm = nullptr;
    delete border; border = nullptr;
    delete sky; sky = nullptr;
    delete gameInfo; gameInfo = nullptr;

    for (int t = 0; t < 2; ++t)
    {
        pause[t].texture = nullptr;
    }
    delete[] pause;

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

bool GameClass::flow()
{
    while (!status.gameQuit)
    {
        SDL_RenderClear(sdl_->Renderer());
        if (status.mainMenu)
        {
            mm->ShowMainMenu(sdl_, status);
        }
        if (status.partOne)
        {
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
                    status.gameQuit = 
                        !engine->MakeHeroLazer(nHero->LazerStart()); break;
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

        borderSky_show_moving();
        engine->InPause(sdl_, status, gameInfo);
        showPause();
        
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
        SDL_RenderClear(sdl_->Renderer());
        if (status.heroIntro == false) return;
        nHero->Show(sdl_);
        borderSky_show_moving();
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

void GameClass::borderSky_show_moving()
{
    border->ShowBorder(sdl_);
    sky->ShowSky(sdl_);
    sky->MoveSky();
}

void GameClass::showPause()
{
    sdl_->TextureRender(pause[pause_].texture, &pause[pause_].main_rect);
    sdl_->TextureRender(pause[pressEscape].texture, 
                        &pause[pressEscape].main_rect);
}

