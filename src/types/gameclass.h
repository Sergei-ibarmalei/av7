#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "../consts/gameconsts.h"
#include "borderclass.h"
#include "skyclass.h"


#include "engine_.h"
#include "gui.h"
#include "../core/core.h"


class GameClass
{
    private:
    enum {pause_, pressEscape};
    bool           init {true};
    
    Gui*           gui {nullptr};
    Border*        border {nullptr};
    Sky*           sky {nullptr};
    GameInfoClass* gameInfo {nullptr};
    Sdl*           sdl_ {nullptr};
    status_t       status;
    NHero*         nHero;
    Engine_*       engine;

    bool initEngine(const tc& collection);
    void initStatus();
    void restartStatus();
    bool initBorder();
    bool initSky(texture_* starTexture);
    bool partOne();
    void check_key_events();
    bool initGameInfo(const tc& collection);
    void pauseIsPressed();
    void showHeroIntro();

    public:
    GameClass(Sdl& sdl, tc& collection);
    ~GameClass();
    GameClass(const GameClass& ) = delete;
    GameClass& operator=(const GameClass& ) = delete;
    bool Status() const {return init;}

    bool flow(const tc& collection);
    bool RestartEngine(const tc& collection);


    
};

#endif