#ifndef TEXTURESCOLLECTION_H
#define TEXTURESCOLLECTION_H


#include "gamefonts.h"
//#include "errs.h"
#include "../loging/loging.h"
#include "texturesnames.h"

class TexturesCollection
{
    private:
        const char* names[tn::allStringTextures] = 
        {
            "NEW GAME", "RULES", "EXIT",
            "NEW GAME", "RULES", "EXIT",
            "PAUSE", "Press Esc to continue, Q to exit in Main menu",
            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "x 1", "x 2", "x 3"
        };

        const char* names_pics[tn::all_pics]
        {
            "images/hero.png", "images/hero_scale_mult.png",
            "images/alien_one.png",
            "images/laserBlue01.png", "images/alien_laser01.png",
            "images/one_star.png", "images/moon_one.png"
        };
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
        texture_* Pictures() const {return pictures;}
        texture_* Strings()  {return strings;}

};

using tc = TexturesCollection;

#endif

