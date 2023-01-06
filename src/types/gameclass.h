#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "../consts/gameconsts.h"
#include "../loging/loging.h"
#include "gametypes.h"

class GameClass
{
    private:
    status_t status;

    void initStatus();


    public:
    GameClass(log_::Log& log);
    ~GameClass();
    GameClass(const GameClass& ) = delete;
    GameClass& operator=(const GameClass& ) = delete;

};

#endif