#ifndef SDLCLASS_H
#define SDLCLASS_H

#include "sdltypes.h"
#include "../loging/loging.h"

class Sdl
{
    private:
    SDL_Renderer*   gRenderer;
    SDL_Window*     gWindow;
    SDL_Event       e;
    bool Init(const char* appName, log_::Log& log);
    bool init = true;

    public:
    explicit Sdl(const char* appName, log_::Log& log);
    Sdl(const Sdl& ) = delete;
    ~Sdl();
    bool Status() const {return init;}
    void TextureRender(SDL_Texture* const t, rect_* const r) const;
    SDL_Renderer* Renderer() const {return gRenderer;}
    SDL_Event& event() {return e;}
};

#endif