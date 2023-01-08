#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "../consts/gameconsts.h"
#include "mainmenu.h"
#include "borderclass.h"
#include "skyclass.h"
#include "gameInfoClass.h"

class GameClass
{
    private:
    MainMenu*      mm {nullptr};
    Border*        border {nullptr};
    Sky*           sky {nullptr};
    GameInfoClass* gameInfo {nullptr};

    Sdl*      sdl_;
    status_t status;
    bool     gameClassStatus = true;

    void initStatus();
    bool initBorder(log_::Log& log);
    bool initSky(texture_* starTexture, log_::Log& log);
    bool partOne(log_::Log& log);
    void action();
    void borderSky_show_moving();
    bool initGameInfo(tc& collection, log_::Log& log);

    public:
    GameClass(Sdl& sdl, tc& collection, log_::Log& log);
    ~GameClass();
    GameClass(const GameClass& ) = delete;
    GameClass& operator=(const GameClass& ) = delete;
    bool Status() const {return gameClassStatus;}

    bool flow(log_::Log& log);
    
};

#endif