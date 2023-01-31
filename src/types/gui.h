#ifndef GUI_H
#define GUI_H

#include "sdlclass.h"
#include "texturesnames.h"
#include "texturescollection.h"
#include "gametypes.h"
#include "../consts/gameconsts.h"



class Gui
{
    private:
    enum {pause, pressEsc, allPaused};
    enum {game, over, allGameOvered};
    enum {space = 100,};
    gameover::gostatus gostatus = gameover::moves;

    bool init {true};
    texture_* mainmenuTextures {nullptr};
    texture_* pauseTextures    {nullptr};
    texture_* gameoverTextures  {nullptr};

    int stopmovingGameWord_x;
    int stopmovingOverWord_x;
    void resetGameOverCoords();

    void showNewGameString(const Sdl* sdl, int chosen_texture);
    void showRulesString(const Sdl* sdl, int chosen_texture);
    void showExitString(const Sdl* sdl, int chosen_texture);
    void makepause(const texture_* stringsTextures);
    void makemainmenu(const texture_* stringsTextures);
    void makegameover(const texture_* stringsTextures);

    public:   
    explicit Gui(const texture_* stringsTextures);
    ~Gui();
    Gui(const Gui&) = delete;
    Gui& operator=(const Gui&) = delete;
    void ShowMainMenu(Sdl* sdl, status_t& status);
    void ShowPause(const Sdl* sdl) const;
    void ShowGameOver(const Sdl* sdl) const;
    bool Status() const {return init;}
    void MoveGameOver();
    void ResetGameOver();
    bool IsGameOverMoving() const;
};



#endif