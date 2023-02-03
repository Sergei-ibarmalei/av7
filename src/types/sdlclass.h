#ifndef SDLCLASS_H
#define SDLCLASS_H

#include "sdltypes.h"

class Sdl
{
    private:
    SDL_Renderer*   gRenderer;
    SDL_Window*     gWindow;
    SDL_Event       e;

    music*          soundEffects;
    bool Init(const char* appName);
    bool init = true;
    bool initSoundEffects();

    public:
    explicit Sdl(const char* appName);
    Sdl(const Sdl& ) = delete;
    ~Sdl();
    bool Status() const {return init;}
    void TextureRender(SDL_Texture* const t, rect_* const r) const;
    SDL_Renderer* Renderer() const {return gRenderer;}
    SDL_Event& event() {return e;}
    music* SoundEffects() const {return soundEffects;}
};

#endif