#include "sdlclass.h"

Sdl::Sdl(const char* appName)
{
    init = Init(appName);
}

bool Sdl::Init(const char* appName)
{
    if (appName == nullptr)
    {
        std::cout << "Application name is absent.\n";
        return false;
    }
        
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Could not initialize video mode.\n";
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "SDL linear texture error.\n";
        return false;
    }

    /*Create window*/
    gWindow = SDL_CreateWindow(appName,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   S_W,
                                   S_H,
                                   SDL_WINDOW_SHOWN);
    if (!gWindow)
    {
        std::cout << "Cannot create window.\n";
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow,
                                    -1,
                                    SDL_RENDERER_ACCELERATED);
    if (!gRenderer)
    {
        std::cout << "Renderer could not be created.\n";
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "Could not initialize png image.\n";
        return false;
    }

    if (TTF_Init() == 1)
    {
        std::cout << "SDL_ttf could not initialize.\n";
        return false;
    }

    return true;
}

void Sdl::TextureRender(SDL_Texture* const t, rect_* const r) const
{
    if (!t) return;
    SDL_RenderCopy(gRenderer, t, nullptr, r);
}

Sdl::~Sdl()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}