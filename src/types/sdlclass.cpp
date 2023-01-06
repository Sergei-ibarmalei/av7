#include "sdlclass.h"

using string_ = std::string;

Sdl::Sdl(const char* appName, log_::Log& log)
{
    init = Init(appName, log);
}

bool Sdl::Init(const char* appName, log_::Log& log)
{
    if (appName == nullptr)
    {
        log.log_info = "Application name is absent, abort.";
        log.push(log.log_info);
        return false;
    }
        
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        log.log_info = "Could not initialize video mode.";
        log.push(log.log_info);
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        log.log_info = "SDL linear texture error.";
        log.push(log.log_info);
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
        log.log_info = "Cannot create window.";
        log.push(log.log_info);
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow,
                                    -1,
                                    SDL_RENDERER_ACCELERATED);
    if (!gRenderer)
    {
        log.log_info = "Renderer could not be created.";
        log.push(log.log_info);
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        log.log_info = "Could not initialize png image.";
        log.push(log.log_info);
        return false;
    }

    if (TTF_Init() == 1)
    {
        log.log_info = "SDL_ttf could not initialize.";
        log.push(log.log_info);
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