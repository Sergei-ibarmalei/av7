#ifndef EXS_H
#define EXS_H

#include "errs.h"
#include <iostream>

class GameEx
{
    private:
    ex::gameErrs ge = ex::OK;

    public:
    GameEx(const ex::gameErrs& err);
    void GameExMsg();

};

#endif