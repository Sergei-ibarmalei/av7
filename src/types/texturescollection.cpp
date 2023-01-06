#include "texturescollection.h"

#include "texturesnames.h"
using string_ = std::string;

TexturesCollection::TexturesCollection(SDL_Renderer* const renderer,
                                        log_::Log& log)
{
    if (!renderer)
    {
        status = false;
        log.log_info = "Cannot create texture collection, render is null.\n";
        log.push(log.log_info);
        return;
    }
    r = renderer;
    if (!initGameFonts(log))
    {
        status = false; return;
    }
    if (!makeStringsTextures(log))
    {
        status = false; return;
    }

    if (!makePicturesTextures(log))
    {
        status = false; return;
    }

}

TexturesCollection::~TexturesCollection()
{
    
}

void TexturesCollection::textureFree(SDL_Texture* t)
{
    if (t)
    {
        SDL_DestroyTexture(t);
        t = nullptr;
    }
}

bool TexturesCollection::makePicturesTextures(log_::Log& log)
{
    int texture;
    pictures = new (std::nothrow)texture_[tn::all_pics];
    if (!pictures)
    {
        log.log_info = "Cannot allocate memory for pictures textures.";
        log.push(log.log_info);
        return false;
    }
    for (texture = tn::hero; texture < tn::all_pics; ++texture)
    {
        pictures[texture].texture = nullptr;
        if (loadFromFile(r,
                         &pictures[texture].texture,
                         pictures[texture].rect,
                         names_pics[texture], log) == false) return false;

    }
    return true;
}

bool TexturesCollection::makeStringsTextures(log_::Log& log)
{
    int texture;
    strings = new (std::nothrow) texture_[tn::allStringTextures];
    if (!strings)
    {
        log.log_info = "Cannot allocate memory for strings textures.";
        log.push(log.log_info);
        status = false;
        return status;
    }
    /*MAKING TEXTURES FOR MAIN MENU*/
    for (texture = tn::new_game; texture < tn::new_game_bright; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].rect,
                         names[texture],
                         &gameFonts[tn::MainMenu], log) == false) return false;
    }
    /*MAKING TEXTURES FOR MAIN MENU BRIGHT*/
    for (texture = tn::new_game_bright; texture < tn::pause; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].rect,
                         names[texture],
                         &gameFonts[tn::MainMenuBright], log) == false)
            return false;
    }

    /*MAKING TEXTURES FOR PAUSE*/
    texture = tn::pause;
    if (loadFromText(r,
                     &strings[texture].texture,
                     strings[texture].rect,
                     names[texture],
                     &gameFonts[tn::Pause], log) == false) return false;
    /*MAKING TEXTURE FOR PRESS ESC..*/

    texture = tn::PressEsc;
    if (loadFromText(r,
                     &strings[texture].texture,
                     strings[texture].rect,
                     names[texture],
                     &gameFonts[tn::Pause], log) == false) return false;
    /*MAKING TEXTURE FOR SCORES*/
    for (texture = tn::zeroScore; texture < tn::zeroScoreB; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].rect,
                         names[texture],
                         &gameFonts[tn::Scores], log) == false) return false;
    }
    /*MAKING TEXTURE FOR SCORE BANNER*/
    for (texture = tn::zeroScoreB; texture < tn::x1; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].rect,
                         names[texture],
                         &gameFonts[tn::ScoresBanner], log) == false)
            return false;
    }
    /*MAKING TEXTURE FOR LIVE MULTIPLIVCATION*/

    for (texture = tn::x1; texture < tn::allStringTextures; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].rect,
                         names[texture],
                         &gameFonts[tn::LiveMult], log) == false) return false;
    }

    return true;
}



bool TexturesCollection::initGameFonts(log_::Log& log)
{
    gameFonts = new (std::nothrow) gamefont_[tn::allGameFonts];
    if (!gameFonts)
    {
        log.log_info = "Cannot allocate memory for game fonts.";
        log.push(log.log_info);
        return false;
    }
    setFontsProperties();
    for (int font = 0; font < tn::allGameFonts; ++font)
    {
        gameFonts[font].font = TTF_OpenFont(GLOBALFONTNAME,
                                            gameFonts[font].size);
        if (!gameFonts[font].font)
        {
            log.log_info = "Cannot open font.";
            log.push(log.log_info);
            return false;
        }
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