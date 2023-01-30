#include "gui.h"


Gui::Gui(const texture_* stringsTextures)
{
    if (!stringsTextures)
    {
        init = false; return;
    }

    mainmenuTextures = new (std::nothrow) texture_[tn::pause];
    if (!mainmenuTextures)
    {
        init = false; return;
    }
    makepause(stringsTextures);
    makemainmenu(stringsTextures);
    makegameover(stringsTextures);




}

Gui::~Gui()
{
    mainmenuTextures = nullptr;
    pauseTextures  = nullptr;
    gameoverTextures = nullptr;
}

void Gui::makegameover(const texture_* stringsTextures)
{
    /*Init GAME OVER textures*/
    gameoverTextures = new (std::nothrow) texture_[allGameOvered];
    if (!gameoverTextures)
    {
        init = false; return;
    }
    /*Set GAME OVER coords*/

    for (int string = 0; string < allGameOvered; ++string)
    {
        gameoverTextures[string] = stringsTextures[string];
    }
   
    int fullLenght = gameoverTextures[game].main_rect.w +
        gameoverTextures[over].main_rect.w + space;
    stopmovingGameWord_x = (S_W / 2) - (fullLenght / 2);
    stopmovingOverWord_x = 
            stopmovingGameWord_x + gameoverTextures[game].main_rect.w + space;
    resetGameOverCoords();
 

}



void Gui::resetGameOverCoords()
{
    gameoverTextures[game].main_rect.x = S_W;
    gameoverTextures[game].main_rect.y = 
                            (S_H / 2) - gameoverTextures[game].main_rect.h / 2;
    gameoverTextures[over].main_rect.x = LEFT_BORDER_X - 
                                        gameoverTextures[over].main_rect.w;
    gameoverTextures[over].main_rect.y = gameoverTextures[game].main_rect.y;

    gostatus = gameover::moves;
 
}

void Gui::MoveGameOver()
{
    if (gostatus == gameover::stops) return;
    gameoverTextures[game].main_rect.x -= GAMEOVER_CAPACITY;
    gameoverTextures[over].main_rect.x += GAMEOVER_CAPACITY;
    if (gameoverTextures[game].main_rect.x <= stopmovingGameWord_x &&
        gameoverTextures[over].main_rect.x >= stopmovingOverWord_x)
        gostatus = gameover::stops;
}

void Gui::makemainmenu(const texture_* stringsTextures)
{

    /*Init MAIN MENU textures*/
    for (int string = tn::new_game; string < tn::pause; ++string)
    {
        mainmenuTextures[string] = stringsTextures[string];
    }

    /*Set MAIN MENU textures coords*/

    int center_x{S_W / 2};
    int center_y{0};
    int oneFourth{S_H / 4};
    int count{0};
    int step{1};
    int offset {tn::new_game_bright - tn::new_game};

    for (count = tn::new_game; count < tn::new_game_bright; ++count)
    {
        center_y = step * oneFourth;
        mainmenuTextures[count].main_rect.x =
            center_x - mainmenuTextures[count].main_rect.w / 2;
        mainmenuTextures[count+offset].main_rect.x = 
                            mainmenuTextures[count].main_rect.x;
        mainmenuTextures[count].main_rect.y =
            center_y - mainmenuTextures[count].main_rect.h / 2;
        mainmenuTextures[count+offset].main_rect.y = 
                            mainmenuTextures[count].main_rect.y;
        step += 1;
    }


}

void Gui::makepause(const texture_* stringsTextures)
{

    /*Init PAUSE textures*/
    pauseTextures = new (std::nothrow) texture_[allPaused];
    if (!pauseTextures)
    {
        init = false; return;
    }
    pauseTextures[pause] = stringsTextures[tn::pause];
    pauseTextures[pressEsc] = stringsTextures[tn::pressEscape];

    /*Set PAUSE textures coords*/
    int centerPause_x = S_W / 2;
    int centerPause_y = S_H / 2;
    int centerPrEsc_x = S_W / 2;
    int centerPrEsc_y = S_H - 100;

    pauseTextures[pause].main_rect.x = 
                        centerPause_x - pauseTextures[pause].main_rect.w / 2;
    pauseTextures[pause].main_rect.y = 
                        centerPause_y - pauseTextures[pause].main_rect.h / 2;
    pauseTextures[pressEsc].main_rect.x = 
        centerPrEsc_x - pauseTextures[pressEsc].main_rect.w / 2;
    pauseTextures[pressEsc].main_rect.y = 
        centerPrEsc_y - pauseTextures[pressEsc].main_rect.h / 2;


}

void Gui::ShowMainMenu(Sdl* sdl, status_t& status)
{
    if (!sdl) return;
    int chosen_texture = tn::new_game_bright;

    while (!status.gameQuit)
    {
        while (SDL_PollEvent(&sdl->event()) != 0)
        {
            if (sdl->event().type == SDL_QUIT) status.gameQuit = true;
            else if
            (sdl->event().type == SDL_KEYDOWN && sdl->event().key.repeat ==0)
            {
                switch (sdl->event().key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        chosen_texture -= 1;
                        if (chosen_texture < tn::new_game_bright)
                            chosen_texture = tn::exit_bright;
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        chosen_texture += 1;
                        if (chosen_texture > tn::exit_bright)
                            chosen_texture = tn::new_game_bright;
                        break;
                    }
                    case SDLK_RETURN:
                    {
                        if (chosen_texture == tn::new_game_bright)
                        {
                            status.mainMenu = false;
                            status.partOne = true;
                            status.partTwo = false;
                            status.pause = false;
                            return;
                        }
                        if (chosen_texture == tn::rules_bright)
                        {

                        }
                        if (chosen_texture == tn::exit_bright)
                        {
                            status.mainMenu = false;
                            status.partOne = false;
                            status.partTwo = false;
                            status.pause = false;
                            status.gameQuit = true;
                        }
                    }
                }
            }
        }
        SDL_RenderClear(sdl->Renderer());
        showNewGameString(sdl, chosen_texture);
        showRulesString(sdl, chosen_texture);
        showExitString(sdl, chosen_texture);
        SDL_RenderPresent(sdl->Renderer());
    }
}

void Gui::showNewGameString(const Sdl* sdl, int chosen_texture)
{
    if (chosen_texture != tn::new_game_bright)
        chosen_texture = tn::new_game;
    sdl->TextureRender(mainmenuTextures[chosen_texture].texture,
                        &mainmenuTextures[chosen_texture].main_rect);
}

void Gui::showRulesString(const Sdl* sdl, int chosen_texture)
{
    if (chosen_texture != tn::rules_bright)
        chosen_texture = tn::rules;
    sdl->TextureRender(mainmenuTextures[chosen_texture].texture,
                        &mainmenuTextures[chosen_texture].main_rect);
}

void Gui::showExitString(const Sdl* sdl, int chosen_texture)
{
    if (chosen_texture != tn::exit_bright)
        chosen_texture = tn::exit;
    sdl->TextureRender(mainmenuTextures[chosen_texture].texture,
                        &mainmenuTextures[chosen_texture].main_rect);
}


void Gui::ShowPause(const Sdl* sdl) const
{
    sdl->TextureRender(pauseTextures[pause].texture, 
                            &pauseTextures[pause].main_rect);
    sdl->TextureRender(pauseTextures[pressEsc].texture, 
                            &pauseTextures[pressEsc].main_rect);
}

void Gui::ShowGameOver(const Sdl* sdl) const
{
    sdl->TextureRender(gameoverTextures[game].texture,
                        &gameoverTextures[game].main_rect);
    sdl->TextureRender(gameoverTextures[over].texture,
                        &gameoverTextures[over].main_rect);
}

void Gui::ResetGameOver()
{
    resetGameOverCoords();
}

