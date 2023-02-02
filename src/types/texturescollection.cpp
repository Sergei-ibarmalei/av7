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

bool TexturesCollection::makePicturesTextures()
{
    int texture;
    pictures = new (std::nothrow)texture_[tn::all_pics];
    if (!pictures) return false;
    for (texture = tn::hero; texture < tn::all_pics; ++texture)
    {
        pictures[texture].texture = nullptr;
        if (loadFromFile(r,
                         &pictures[texture].texture,
                         pictures[texture].main_rect,
                         names_pics[texture]) == false) return false;

    }
    return true;
}

bool TexturesCollection::makeSmokyPicturesTextures()
{
    int texture;
    smoky_pictures = new (std::nothrow) texture_[tn::allsmokyblow];
    if (!smoky_pictures) return false;
    for (texture = 0; texture < tn::allsmokyblow; ++texture)
    {
        smoky_pictures[texture].texture = nullptr;
        if (loadFromFile(r,
                         &smoky_pictures[texture].texture,
                         smoky_pictures[texture].main_rect,
                         names_smoky[texture]) == false) return false;
    }
    return true;
}



bool TexturesCollection::makeStringsTextures()
{
    int texture;
    strings = new (std::nothrow) texture_[tn::allStringTextures];
    if (!strings)
    {
        status = false;
        return status;
    }
    /*MAKING TEXUTURES FOR GAME OVER*/
    for (texture = tn::game; texture < tn::allStringTextures; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].main_rect,
                         names[texture],
                         &gameFonts[tn::Pause]) == false) return false;
    }
    /*MAKING TEXTURES FOR MAIN MENU*/
    for (texture = tn::new_game; texture < tn::new_game_bright; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].main_rect,
                         names[texture],
                         &gameFonts[tn::MainMenu]) == false) return false;
    }
    /*MAKING TEXTURES FOR MAIN MENU BRIGHT*/
    for (texture = tn::new_game_bright; texture < tn::pause; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].main_rect,
                         names[texture],
                         &gameFonts[tn::MainMenuBright]) == false)
            return false;
    }

    /*MAKING TEXTURES FOR PAUSE*/
    texture = tn::pause;
    if (loadFromText(r,
                     &strings[texture].texture,
                     strings[texture].main_rect,
                     names[texture],
                     &gameFonts[tn::Pause]) == false) return false;
    /*MAKING TEXTURE FOR PRESS ESC..*/

    texture = tn::pressEscape;
    if (loadFromText(r,
                     &strings[texture].texture,
                     strings[texture].main_rect,
                     names[texture],
                     &gameFonts[tn::PressEsc]) == false) return false;
    /*MAKING TEXTURE FOR SCORES*/
    for (texture = tn::zeroScore; texture < tn::zeroScoreB; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].main_rect,
                         names[texture],
                         &gameFonts[tn::Scores]) == false) return false;
    }
    /*MAKING TEXTURE FOR SCORE BANNER*/
    for (texture = tn::zeroScoreB; texture < tn::x0; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].main_rect,
                         names[texture],
                         &gameFonts[tn::ScoresBanner]) == false)
            return false;
    }
    /*MAKING TEXTURE FOR LIVE MULTIPLICATION*/

    for (texture = tn::x0; texture < tn::game; ++texture)
    {
        if (loadFromText(r,
                         &strings[texture].texture,
                         strings[texture].main_rect,
                         names[texture],
                         &gameFonts[tn::LiveMult]) == false) return false;
    }
    

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
    for (object = tn::MainMenu; object < tn::allGameFonts; ++object)
    {
        if (gameFonts[object].font)
        {
            TTF_CloseFont(gameFonts[object].font);
            gameFonts[object].font = nullptr;
        }
    }
    delete[] gameFonts;
    gameFonts = nullptr;

    for (object = tn::hero; object < tn::all_pics; ++object)
    {
        if (pictures[object].texture)
        {
            textureFree(pictures[object].texture);
            pictures[object].texture = nullptr;
        }
    }
    delete[] pictures;
    pictures = nullptr;

    for (object = 0; object < tn::allsmokyblow; ++object)
    {
        if (smoky_pictures[object].texture)
        {
            textureFree(smoky_pictures[object].texture);
            smoky_pictures[object].texture = nullptr;
        }
    }
    delete smoky_pictures;
    smoky_pictures = nullptr;


    for (object = tn::new_game; object < tn::allStringTextures; ++object)
    {
        if(strings[object].texture)
        {
            textureFree(strings[object].texture);
            strings[object].texture = nullptr;
        }
    }
    delete[] strings;
    strings = nullptr;
}