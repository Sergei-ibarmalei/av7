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
    if (mm) 
    {
        delete mm; mm = nullptr;
    }
    if (border)
    {
        delete border; border = nullptr;
    }
    if (sky)
    {
        delete sky; sky = nullptr;
    }
    if (gameInfo)
    {
        delete gameInfo; gameInfo = nullptr;
    }
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
            if (mm->Status() == false) return false;
        }
        if (status.partOne)
        {
            if (!partOne(log)) return false;
        }
    }
    return true;
}

void GameClass::action()
{
    while (SDL_PollEvent(&sdl_->event()) != 0)
    {
        if (sdl_->event().type == SDL_QUIT) status.gameQuit = true;
    }
}

void GameClass::borderSky_show_moving()
{
    border->ShowBorder(sdl_);
    sky->ShowSky(sdl_);
    sky->MoveSky();
}

