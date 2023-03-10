#ifndef TEXTURESCOLLECTION_H
#define TEXTURESCOLLECTION_H


#include "gamefonts.h"
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
            "x 0", "x 1", "x 2", "x 3", "GAME", "OVER"
        };

        const char* names_pics[tn::all_pics]
        {
            "images/hero.png", "images/hero_scale_mult.png",
            "images/alien_one.png",
            "images/laserBlue01.png", "images/alien_laser01.png",
            "images/one_star.png", "images/scull_grey_01.png"
        };
        const char* names_smoky[tn::allsmokyblow]
        {
            "images/smoky/explosion00.png", "images/smoky/explosion01.png",
            "images/smoky/explosion02.png", "images/smoky/explosion03.png",
            "images/smoky/explosion04.png", "images/smoky/explosion05.png",
            "images/smoky/explosion06.png", "images/smoky/explosion07.png",
            "images/smoky/explosion08.png", "images/smoky/explosion09.png",
            "images/smoky/explosion10.png", "images/smoky/explosion11.png",
            "images/smoky/explosion12.png", "images/smoky/explosion13.png",
            "images/smoky/explosion14.png", "images/smoky/explosion15.png",
            "images/smoky/explosion16.png", "images/smoky/explosion17.png"
        };

        SDL_Renderer* r = nullptr;
        bool status = true;
        gamefont_* gameFonts = nullptr;
        texture_*  pictures = nullptr;
        texture_*  strings  = nullptr;
        texture_*  smoky_pictures = nullptr;
        bool initGameFonts();
        void setFontsProperties();
        bool makePicturesTextures();
        bool makeSmokyPicturesTextures();
        bool makeStringsTextures();
        void textureFree(SDL_Texture* t);
        bool loadFromFile(SDL_Renderer* r,
                          SDL_Texture** t,
                          rect_& mainRect,
                          const char* name);
        bool loadFromText(SDL_Renderer* r,
                          SDL_Texture** t,
                          rect_& mainRect,
                          const char* textToTexture,
                          gamefont_* font);
        bool fromFile(texture_* arrayOftextures,
                      SDL_Renderer* r,
                      const char** arrayOfnames,
                      const int start, const int stop);
        bool fromText(texture_* arrayOftextures,
                      SDL_Renderer* r,
                      const char** arrayOfnames,
                      gamefont_* font,
                      const int start, const int stop);

    public:
        explicit TexturesCollection(SDL_Renderer* const r);
        ~TexturesCollection();
        TexturesCollection(const TexturesCollection& ) = delete;
        TexturesCollection& operator=(const TexturesCollection&) = delete;
        bool Status() const {return status;}
        texture_* Pictures() const {return pictures;}
        texture_* Strings()  const {return strings;}
        texture_* Smoky()    const {return smoky_pictures;}

};

using tc = TexturesCollection;

#endif

