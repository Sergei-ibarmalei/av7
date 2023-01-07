#ifndef MAINMENU_H
#define MAINMENU_H

#include "sdlclass.h"
#include "texturesnames.h"
#include "texturescollection.h"
#include "gametypes.h"


class MainMenu
{
    private:
    texture_* mmTextures = nullptr;
    bool      mmStatus = true;

    void init_mmTextures(texture_* t, log_::Log& log);
    void set_mmTextures();
    void showNewGameString(Sdl* sdl, int chosen_texture);
    void showRulesString(Sdl* sdl, int chosen_texture);
    void showExitString(Sdl* sdl, int chosen_texture);

    public:
    MainMenu(texture_* t, log_::Log& log);
    MainMenu(const MainMenu& ) = delete;
    MainMenu& operator=(const MainMenu& ) = delete;
    ~MainMenu();
    void ShowMainMenu(Sdl* sdl, status_t& gameStatus, log_::Log& log);
    bool Status() const {return mmStatus;}
};


#endif