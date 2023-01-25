#include "mainmenu.h"

MainMenu::MainMenu(texture_* t)
{
    if (!t)
    {
        mmStatus = false;
        return;
    }
    init_mmTextures(t);


}

MainMenu::~MainMenu()
{
    for (int object = tn::new_game; object < tn::pause; ++object)
    {
        mmTextures[object].texture = nullptr;
    }
    delete[] mmTextures;
    mmTextures = nullptr;
}

void MainMenu::init_mmTextures(texture_* t)
{
    mmTextures = new (std::nothrow) texture_[tn::pause];
    if (!mmTextures)
    {
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
        mmTextures[count].main_rect.x =
            center_x - mmTextures[count].main_rect.w / 2;
        mmTextures[count+offset].main_rect.x = mmTextures[count].main_rect.x;
        mmTextures[count].main_rect.y =
            center_y - mmTextures[count].main_rect.h / 2;
        mmTextures[count+offset].main_rect.y = mmTextures[count].main_rect.y;
        step += 1;
    }

    
}

void MainMenu::ShowMainMenu(Sdl* sdl, status_t& gameStatus)
{
    if (!sdl)
    {
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
                        &mmTextures[chosen_texture].main_rect);
}

void MainMenu::showRulesString(Sdl* sdl, int chosen_texture)
{
    if (chosen_texture != tn::rules_bright)
        chosen_texture = tn::rules;
    sdl->TextureRender(mmTextures[chosen_texture].texture,
                        &mmTextures[chosen_texture].main_rect);
}

void MainMenu::showExitString(Sdl* sdl, int chosen_texture)
{
    if (chosen_texture != tn::exit_bright)
        chosen_texture = tn::exit;
    sdl->TextureRender(mmTextures[chosen_texture].texture,
                        &mmTextures[chosen_texture].main_rect);

}