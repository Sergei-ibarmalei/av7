#include "texturescollection.h"

#include "texturesnames.h"
using string_ = std::string;

TexturesCollection::TexturesCollection(SDL_Renderer* const renderer)
{
    if (!renderer)
    {
        status = false;
        return;
    }
    r = renderer;
    if (!initGameFonts())
    {
        status = false; return;
    }
    if (!makeStringsTextures())
    {
        status = false; return;
    }

    if (!makePicturesTextures())
    {
        status = false; return;
    }

    if (!makeSmokyPicturesTextures())
    {
        status = false; return;
    }

}


void TexturesCollection::textureFree(SDL_Texture* t)
{
    if (t)
    {
        SDL_DestroyTexture(t);
        t = nullptr;
    }
}

bool TexturesCollection::fromFile(texture_* arrayOftextures,
                                  SDL_Renderer* r,
                                  const char** arrayOfnames,
                                  const int start, const int stop)
{
    for (int texture = start; texture < stop; ++ texture)
    {
        arrayOftextures[texture].texture = nullptr;
        if (loadFromFile(r, &arrayOftextures[texture].texture,
                            arrayOftextures[texture].main_rect,
                            arrayOfnames[texture]) == false) 
        {
            arrayOftextures[texture].texture = nullptr;
            return false;
        }
    }
    return true;
}

bool TexturesCollection::makePicturesTextures()
{
    pictures = new (std::nothrow)texture_[tn::all_pics];
    if (!pictures) return false;
    return fromFile(pictures, r, names_pics, tn::hero, tn::all_pics);
}

bool TexturesCollection::makeSmokyPicturesTextures()
{
    smoky_pictures = new (std::nothrow) texture_[tn::allsmokyblow];
    if (!smoky_pictures) return false;
    return fromFile(smoky_pictures, r, names_smoky, 0, tn::allsmokyblow);
}

bool TexturesCollection::fromText(texture_* arrayOftextures,
                                  SDL_Renderer* r,
                                  const char** arrayOfnames,
                                  gamefont_* font,
                                  const int start, const int stop)
{
    for (int texture = start; texture < stop; ++ texture)
    {
        arrayOftextures[texture].texture = nullptr;
        if (loadFromText(r, &arrayOftextures[texture].texture,
                            arrayOftextures[texture].main_rect,
                            arrayOfnames[texture],
                            font) == false)
        {
            arrayOftextures[texture].texture = nullptr;
            return false;
        }
    }
    return true;
}



bool TexturesCollection::makeStringsTextures()
{
    strings = new (std::nothrow) texture_[tn::allStringTextures];
    if (!strings)
    {
        status = false;
        return status;
    }
    /*MAKING TEXUTURES FOR GAME OVER*/
    if (!fromText(strings, r, names, &gameFonts[tn::Pause], 
                    tn::game, tn::allStringTextures))
        return false;

    /*MAKING TEXTURES FOR MAIN MENU*/

    if (!fromText(strings, r, names, &gameFonts[tn::MainMenu], 
                    tn::new_game, tn::new_game_bright))
        return false;

    if (!fromText(strings, r, names, &gameFonts[tn::MainMenuBright], 
                    tn::new_game_bright, tn::pause))
        return false;

    /*MAKING TEXTURES FOR PAUSE*/

    if (!fromText(strings, r, names, &gameFonts[tn::Pause], 
                    tn::pause, tn::pressEscape))
        return false;
    /*MAKING TEXTURE FOR PRESS ESC..*/

    if (!fromText(strings, r, names, &gameFonts[tn::PressEsc], 
                    tn::pressEscape, tn::zeroScore))
        return false;
    /*MAKING TEXTURE FOR SCORES*/
    if (!fromText(strings, r, names, &gameFonts[tn::Scores], 
                    tn::zeroScore, tn::zeroScoreB))
        return false;

    /*MAKING TEXTURE FOR SCORE BANNER*/
    if (!fromText(strings, r, names, &gameFonts[tn::ScoresBanner], 
                    tn::zeroScoreB, tn::x0))
        return false;

    /*MAKING TEXTURE FOR LIVE MULTIPLICATION*/
    if (!fromText(strings, r, names, &gameFonts[tn::LiveMult], 
                    tn::x0, tn::game))
        return false;

    return true;
}



bool TexturesCollection::initGameFonts()
{
    gameFonts = new (std::nothrow) gamefont_[tn::allGameFonts];
    if (!gameFonts) return false;
    setFontsProperties();
    for (int font = 0; font < tn::allGameFonts; ++font)
    {
        gameFonts[font].font = TTF_OpenFont(GLOBALFONTNAME,
                                            gameFonts[font].size);
        if (!gameFonts[font].font) return false;
    }
    return true;
}

void TexturesCollection::setFontsProperties()
{
    /*MAIN MENU FONT PROPERTIES*/
    gameFonts[tn::MainMenu].size = MAINMENUFONTSIZE;
    gameFonts[tn::MainMenu].color = FIREBRICK;
    gameFonts[tn::MainMenu].isAlpha = true;

    /*MAIN MENU BRIGHT FONT PROPERTIES*/
    gameFonts[tn::MainMenuBright].size = MAINMENUFONTSIZE;
    gameFonts[tn::MainMenuBright].color = INDIANRED;
    gameFonts[tn::MainMenuBright].isAlpha = true;

    /*SCORES FONT PROPERTIES*/
    gameFonts[tn::Scores].size = SCORESFONTSIZE;
    gameFonts[tn::Scores].color = POWDERBLUE;
    gameFonts[tn::Scores].isAlpha = false;

    /*SCORESBANNER FONT PROPERTIES*/
    gameFonts[tn::ScoresBanner].size = SCORESBANNERFONTSIZE;
    gameFonts[tn::ScoresBanner].color = LIGHTSTEELBLUE;
    gameFonts[tn::ScoresBanner].isAlpha = false;

    /*PAUSE FONT PROPERTIES*/
    gameFonts[tn::Pause].size = PAUSEFONTSIZE;
    gameFonts[tn::Pause].color = DARKORANGE;
    gameFonts[tn::Pause].isAlpha = true;

    /*PRESS ESC FONT PROPERTIES*/
    gameFonts[tn::PressEsc].size = PRESSESCFONTSIZE;
    gameFonts[tn::PressEsc].color = FIREBRICK;
    gameFonts[tn::PressEsc].isAlpha = true;

    /*LIVE MULTIPLE FONT PROPERTIES*/
    gameFonts[tn::LiveMult].size = LIVEMULTFONTSIZE;
    gameFonts[tn::LiveMult].color = LIGHTSTEELBLUE;
    gameFonts[tn::LiveMult].isAlpha = true;
}

TexturesCollection::~TexturesCollection()
{
    int object;
    if (gameFonts)
    {
        for (object = tn::MainMenu; object < tn::allGameFonts; ++object)
        {
            if (gameFonts[object].font)
                TTF_CloseFont(gameFonts[object].font);
            gameFonts[object].font = nullptr;
        }
    }
    delete[] gameFonts;
    gameFonts = nullptr;

    if (strings)
    {
        for (object = tn::new_game; object < tn::allStringTextures; ++object)
        {
            if(strings[object].texture)
                textureFree(strings[object].texture);
            strings[object].texture = nullptr;
        }
    }
    delete[] strings;
    strings = nullptr;

    if (pictures)
    {
        for (object = tn::hero; object < tn::all_pics; ++object)
        {
            if (pictures[object].texture)
                textureFree(pictures[object].texture);
            pictures[object].texture = nullptr;
        }
    }
    delete[] pictures;
    pictures = nullptr;

    if (smoky_pictures)
    {
        for (object = 0; object < tn::allsmokyblow; ++object)
        {
            if (!smoky_pictures[object].texture) continue;
            if (smoky_pictures[object].texture)
            {
                textureFree(smoky_pictures[object].texture);
            }
            smoky_pictures[object].texture = nullptr;
        }
    }


    delete smoky_pictures;
    smoky_pictures = nullptr;


}