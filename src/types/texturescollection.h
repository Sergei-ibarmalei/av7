#ifndef TEXTURESCOLLECTION_H
#define TEXTURESCOLLECTION_H


#include "gamefonts.h"
#include "errs.h"
#include "../loging/loging.h"

class TexturesCollection
{
    private:
        SDL_Renderer* r = nullptr;
        bool status = true;
        gamefont_* gameFonts = nullptr;
        texture_*  pictures = nullptr;
        texture_*  strings  = nullptr;
        bool initGameFonts(log_::Log& log);
        void setFontsProperties();
        bool makePicturesTextures(log_::Log& log);
        bool makeStringsTextures(log_::Log& log);
        void textureFree(SDL_Texture* t);
        bool loadFromFile(SDL_Renderer* r,
                          SDL_Texture** t,
                          rect_& mainRect,
                          const char* name, log_::Log& log);
        bool loadFromText(SDL_Renderer* r,
                          SDL_Texture** t,
                          rect_& mainRect,
                          const char* textToTexture,
                          gamefont_* font, log_::Log& log);

    public:
        explicit TexturesCollection(SDL_Renderer* const r, log_::Log& log);
        ~TexturesCollection();
        TexturesCollection(const TexturesCollection& ) = delete;
        TexturesCollection& operator=(const TexturesCollection&) = delete;
        bool Status() const {return status;}

};

#endif

