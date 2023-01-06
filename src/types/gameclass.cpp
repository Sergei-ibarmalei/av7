#include "gameclass.h"

GameClass::GameClass(log_::Log& log)
{
    initStatus();
}

GameClass::~GameClass()
{
    
}

void GameClass::initStatus()
{
    status.mainMenu = true;
    status.pause = false;
    status.partOne = false;
    status.partTwo = false;
    status.HeroLives = HERO_LIVES;
}

