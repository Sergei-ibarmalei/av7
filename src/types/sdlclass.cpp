#include "sdlclass.h"

using string_ = std::string;

Sdl::Sdl(const char* appName)
{
    init = Init(appName);
}

bool Sdl::Init(const char* appName)
{
    if (appName == nullptr) return false;
        
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) return false;

    /*Create window*/
    gWindow = SDL_CreateWindow(appName,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   S_W,
                                   S_H,
                                   SDL_WINDOW_SHOWN);
    if (!gWindow)
    {
        std::cout << "Cannot initiate window, abort.\n"; return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow,
                                    -1,
                                    SDL_RENDERER_SOFTWARE/*SDL_RENDERER_ACCELERATED*/);
    if (!gRenderer) return false;

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) return false;

    if (TTF_Init() == 1) return false;

    //Init music
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) <0)
    {
        std::cout << "Cannot initiate audio, abort.\n"; return false;
    }

    //Init soundeffects
    return initSoundEffects();

}

void Sdl::TextureRender(SDL_Texture* const t, rect_* const r) const
{
    if (!t) return;
    SDL_RenderCopy(gRenderer, t, nullptr, r);
}

bool Sdl::initSoundEffects()
{
    soundEffects = new (std::nothrow) music;
    if (!soundEffects) return false;
    soundEffects->hero_laser = Mix_LoadWAV("sounds/laser_hero.wav");
    if (!soundEffects->hero_laser) return false;
    soundEffects->alien_laser = Mix_LoadWAV("sounds/laser_alien.wav");
    if (!soundEffects->alien_laser) return false;
    soundEffects->blow = Mix_LoadWAV("sounds/explosion.wav");
    if (!soundEffects->blow) return false;
    return true;
}

Sdl::~Sdl()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}