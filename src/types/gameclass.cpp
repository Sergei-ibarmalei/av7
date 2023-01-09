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

    plot center {S_W / 2, S_H / 2};
    temp_hero = new Hero(center, &collection.Pictures()[tn::hero], log);


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

    pause[pause_].rect.x = centerPause_x - pause[pause_].rect.w / 2;
    pause[pause_].rect.y = centerPause_y - pause[pause_].rect.h / 2;
    pause[pressEscape].rect.x = centerPrEsc_x - pause[pressEscape].rect.w / 2;
    pause[pressEscape].rect.y = centerPrEsc_y - pause[pressEscape].rect.h / 2;

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
}

void GameClass::initStatus()
{
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
            //if (mm->Status() == false) return false;
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
                case SDLK_ESCAPE:
                {
                    status.pause = true; break;
                }
                default: {}
            }
        }

    }
}

void GameClass::pauseIsPressed()
{
    while (!status.gameQuit || !status.pause)
    {
        SDL_RenderClear(sdl_->Renderer());
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

void GameClass::borderSky_show_moving()
{
    border->ShowBorder(sdl_);
    sky->ShowSky(sdl_);
    sky->MoveSky();
}

void GameClass::showPause()
{
    sdl_->TextureRender(pause[pause_].texture, &pause[pause_].rect);
    sdl_->TextureRender(pause[pressEscape].texture, &pause[pressEscape].rect);
}

