#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "../consts/gameconsts.h"
//#include "gametypes.h"
#include "mainmenu.h"

class GameClass
{
    private:
    MainMenu* mm;
    Sdl*      sdl_;
    status_t status;
    bool     gameClassStatus = true;

    void initStatus();
    //void showMM(Sdl& sdl, status_t& status);

    public:
    GameClass(Sdl& sdl, tc& collection, log_::Log& log);
    ~GameClass();
    GameClass(const GameClass& ) = delete;
    GameClass& operator=(const GameClass& ) = delete;
    bool Status() const {return gameClassStatus;}

    bool flow(log_::Log& log);
};

#endif