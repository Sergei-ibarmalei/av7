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
}

GameClass::~GameClass()
{
    sdl_ = nullptr;
    if (mm) 
    {
        delete mm;
        mm = nullptr;
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
            
        }
    }
    return true;
}

