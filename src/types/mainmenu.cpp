#include "mainmenu.h"

MainMenu::MainMenu(texture_* t,log_::Log& log)
{
    if (!t)
    {
        log.log_info = "Textures for main menu are absent.\n";
        log.push(log.log_info);
        mmStatus = false;
        return;
    }
    init_mmTextures(t, log);


}

MainMenu::~MainMenu()
{
    if (mmTextures)
    {
        for (int object = tn::new_game; object < tn::pause; ++object)
        {
            mmTextures[object].texture = nullptr;
        }
        delete[] mmTextures;
        mmTextures = nullptr;
    }
}

void MainMenu::init_mmTextures(texture_* t, log_::Log& log)
{
    mmTextures = new (std::nothrow) texture_[tn::pause];
    if (!mmTextures)
    {
        log.log_info = "Cannot allocate memory for main menu texts.\n";
        log.push(log.log_info);
        mmStatus = false;
        return;
    }
    for (int object = tn::new_game; object < tn::pause; ++object)
    {
        mmTextures[object] = t[object];
    }
    set_mmTextures();
}

void MainMenu::set_mmTextures()
{
    int center_x{S_W / 2};
    int center_y{0};
    int oneFourth{S_H / 4};
    int count{0};
    int step{1};
    int offset {tn::new_game_bright - tn::new_game};

    for (count = tn::new_game; count < tn::new_game_bright; ++count)
    {
        center_y = step * oneFourth;
        mmTextures[count].rect.x =
            center_x - mmTextures[count].rect.w / 2;
        mmTextures[count+offset].rect.x = mmTextures[count].rect.x;
        mmTextures[count].rect.y =
            center_y - mmTextures[count].rect.h / 2;
        mmTextures[count+offset].rect.y = mmTextures[count].rect.y;
        step += 1;
    }

    
}

void MainMenu::ShowMainMenu(Sdl* sdl, status_t& gameStatus, log_::Log& log)
{
    if (!sdl)
    {
        log.log_info = "In main menu sdl is null.\n";
        log.push(log.log_info);
        mmStatus = false;
        return;
    }
    int chosen_texture = tn::new_game_bright;

    while (!gameStatus.gameQuit)
    {
        while (SDL_PollEvent(&sdl->event()) != 0)
        {
            if (sdl->event().type == SDL_QUIT) gameStatus.gameQuit = true;
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
                            gameStatus.mainMenu = false;
                            gameStatus.partOne = true;
                            gameStatus.partTwo = false;
                            gameStatus.pause = false;
                            return;
                        }
                        if (chosen_texture == tn::rules_bright)
                        {

                        }
                        if (chosen_texture == tn::exit_bright)
                        {
                            gameStatus.mainMenu = false;
                            gameStatus.partOne = false;
                            gameStatus.partTwo = false;
                            gameStatus.pause = false;
                            gameStatus.gameQuit = true;
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

void MainMenu::showNewGameString(Sdl* sdl, int chosen_texture)
{
    if (chosen_texture != tn::new_game_bright)
        chosen_texture = tn::new_game;
    sdl->TextureRender(mmTextures[chosen_texture].texture,
                        &mmTextures[chosen_texture].rect);
}

void MainMenu::showRulesString(Sdl* sdl, int chosen_texture)
{
    if (chosen_texture != tn::rules_bright)
        chosen_texture = tn::rules;
    sdl->TextureRender(mmTextures[chosen_texture].texture,
                        &mmTextures[chosen_texture].rect);
}

void MainMenu::showExitString(Sdl* sdl, int chosen_texture)
{
    if (chosen_texture != tn::exit_bright)
        chosen_texture = tn::exit;
    sdl->TextureRender(mmTextures[chosen_texture].texture,
                        &mmTextures[chosen_texture].rect);

}