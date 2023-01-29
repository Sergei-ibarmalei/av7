#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "../consts/gameconsts.h"
#include "mainmenu.h"
#include "borderclass.h"
#include "skyclass.h"


#include "engine_.h"


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

    NHero* nHero;
    Engine_*  engine;
    



    void initStatus();
    bool initBorder();
    bool initSky(texture_* starTexture);
    bool partOne();
    void check_key_events();
    void borderSky_show_moving();
    bool initGameInfo(tc& collection);
    void initPause(tc& collection);
    void pauseIsPressed();
    void showPause();
    void showHeroIntro();

    public:
    GameClass(Sdl& sdl, tc& collection);
    ~GameClass();
    GameClass(const GameClass& ) = delete;
    GameClass& operator=(const GameClass& ) = delete;
    bool Status() const {return gameClassStatus;}

    bool flow();


    
};

#endif