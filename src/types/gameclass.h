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
    enum {pause_, pressEscape};
    MainMenu*      mm {nullptr};
    Border*        border {nullptr};
    Sky*           sky {nullptr};
    GameInfoClass* gameInfo {nullptr};

    Sdl*      sdl_ {nullptr};
    status_t status;
    texture_* pause {nullptr};
    bool     gameClassStatus = true;

    void initStatus();
    bool initBorder(log_::Log& log);
    bool initSky(texture_* starTexture, log_::Log& log);
    bool partOne(log_::Log& log);
    void check_key_events();
    void borderSky_show_moving();
    bool initGameInfo(tc& collection, log_::Log& log);
    void initPause(tc& collection);
    void pauseIsPressed();
    void showPause();

    public:
    GameClass(Sdl& sdl, tc& collection, log_::Log& log);
    ~GameClass();
    GameClass(const GameClass& ) = delete;
    GameClass& operator=(const GameClass& ) = delete;
    bool Status() const {return gameClassStatus;}

    bool flow(log_::Log& log);
    
};

#endif