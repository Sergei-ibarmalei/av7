#include "gameclass.h"

GameClass::GameClass(Sdl& sdl, tc& collection, log_::Log& log)
{
    sdl_ = &sdl;
    initStatus();
    mm = new (std::nothrow) MainMenu(collection.Strings(), log);
    if (!mm)
    {
        log.log_info = "Cannot allocate memory for main menu.\n";
        log.push(log.log_info);
        gameClassStatus = false;
        return;
    }
    if (mm->Status() == false)
    {
        log.log_info = "Main menu creation is failure.\n";
        log.push(log.log_info);
        gameClassStatus = false;
        return;
    }
    if (!(initBorder(log)))
    {
        gameClassStatus = false; return;
    }

    if (!(initSky(&collection.Pictures()[tn::star], log)))
    {
        gameClassStatus = false; return;
    }

    if (!(initGameInfo(collection, log)))
    {
        gameClassStatus = false; return;
    }

    pause = new (std::nothrow) texture_[2];
    if (!pause)
    {
        log.log_info = "Main menu creation is failure.\n";
        log.push(log.log_info);
        gameClassStatus = false;
        return;       
    }
    initPause(collection);

    nHero = new NHero(&collection.Pictures()[tn::hero]);
    if (nHero->Status() == false)
    {
        gameClassStatus = false;
        return;
    }
    objectsStore = new (std::nothrow) ObjectsStore(&collection);
    if (objectsStore->Status() == false)
    {
        gameClassStatus = false; return;
    }

    gameFleets = new (std::nothrow) Fleets(&collection);
    if (!gameFleets || !gameFleets->Status())
    {
        gameClassStatus = false; return;
    }



    

}

void GameClass::initPause(tc& collection)
{
    //enum {pause_, pressEscape};

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

bool GameClass::initGameInfo(tc& collection, log_::Log& log)
{
    gameInfo = new (std::nothrow) GameInfoClass(collection, log);
    if (!gameInfo)
    {
        log.log_info = "Cannot allocate memory for gameInfo in game class.\n";
        log.push(log.log_info);
        return false;
    }
    return gameInfo->Status();
}

bool GameClass::initBorder(log_::Log& log)
{
    border = new (std::nothrow) Border(log);
    if (!border)
    {
        log.log_info = "Cannot allocate memory for border in gameclass.\n";
        log.push(log.log_info);
        return false;
    }
    if (border->Status() == false)
    {
        log.log_info = "Border class initiate is failure.";
        log.push(log.log_info);
        return false;
    }
    return true;
}

bool GameClass::initSky(texture_* starTexture, log_::Log& log)
{
    sky = new (std::nothrow) Sky(starTexture, log);
    if (!sky)
    {
        log.log_info = "Cannot allocate memory for sky class.\n";
        log.push(log.log_info);
        return false;
    }
    if (sky->Status() == false)
    {
        log.log_info = "Sky class initiate is failure.\n";
        log.push(log.log_info);
        return false;
    }
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
    delete objectsStore;
    objectsStore = nullptr;

    delete gameFleets;
    gameFleets = nullptr;
}

void GameClass::initStatus()
{
    status.heroIntro = true;
    status.gameQuit = false;
    status.mainMenu = true;
    status.pause = false;
    status.partOne = false;
    status.partTwo = false;
    status.HeroLives = HERO_LIVES;
}

bool GameClass::flow(log_::Log& log)
{
    while (!status.gameQuit)
    {
        SDL_RenderClear(sdl_->Renderer());
        if (status.mainMenu)
        {
            mm->ShowMainMenu(sdl_, status, log);
        }
        if (status.partOne)
        {
            if (!partOne(log)) return false;
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
                    //temp_hero->HeroUp(); break;
                    nHero->HeroUp(); break;
                }
                case SDLK_DOWN:
                {
                    //temp_hero->HeroDown(); break;
                    nHero->HeroDown(); break;
                }
                case SDLK_RIGHT:
                {
                    //temp_hero->HeroRight(); break;
                    nHero->HeroRight(); break;
                }
                case SDLK_LEFT:
                {
                    //temp_hero->HeroLeft(); break;
                    nHero->HeroLeft(); break;
                }
                case SDLK_ESCAPE:
                {
                    status.pause = true; break;
                }
                case SDLK_SPACE:
                {
                    //gameStore->MakeHeroLaser(temp_hero->LaserStart());
                    objectsStore->MakeHeroLazer(nHero->LazerStart());
                }
                 
                default: {}
            }
        }
        else if(sdl_->event().type == SDL_KEYUP)
            //temp_hero->HeroStop();
            nHero->HeroStop();

    }
}

void GameClass::pauseIsPressed()
{
    while (!status.gameQuit || !status.pause)
    {
        SDL_RenderClear(sdl_->Renderer());
        nHero->Show(sdl_);
        objectsStore->ShowHeroLazers(sdl_);
        borderSky_show_moving();

        gameInfo->ShowGameInfo(sdl_, status);
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
        //temp_hero->ShowObj(sdl_);
        //nHero->ShowHero(sdl_);
        nHero->Show(sdl_);
        #ifdef SHOW_COL_R
            //temp_hero->showColR(sdl_);
            
        #endif
        borderSky_show_moving();
        gameInfo->ShowGameInfo(sdl_, status);
        //temp_hero->HeroMovesInIntro(status);
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

