#include "texturescollection.h"

using string_ = std::string;

bool TexturesCollection::loadFromFile(SDL_Renderer* r,
                                      SDL_Texture** t,
                                      rect_& mainRect,
                                      const char* name)
{

    if (!r)
    {
        status = false;
        return false;
    }
    if (!t)
    {
        status = false;
        return false;
    }
    if (!name)
    {
        status = false;
        return false;
    }
    textureFree(*t);
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(name);
    if (!loadedSurface)
    {
        status = false;
        return false;
    }
    SDL_SetColorKey(loadedSurface,
                    SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, 0, 0, 0));
    newTexture = SDL_CreateTextureFromSurface(r, loadedSurface);
    if (!newTexture)
    {
        status = false;
        return false;
    }
    mainRect.w = loadedSurface->w;
    mainRect.h = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    *t = newTexture;   
    return true;
}

bool TexturesCollection::loadFromText(SDL_Renderer* r,
                                      SDL_Texture** t,
                                      rect_& mainRect,
                                      const char* textToTexture,
                                      gamefont_* font)
{
    if (!r) return false;
    if (!t) return false;
    if (!textToTexture) return false;
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* txtSurface = 
    TTF_RenderText_Solid(font->font,
                         textToTexture,
                         font->color);
    if (!txtSurface) return false;
    newTexture = SDL_CreateTextureFromSurface(r, txtSurface);
    if (!newTexture) return false;

    /*Для букв устанавливаем разную ширину и высоту*/
    if (font->isAlpha)
    {
        mainRect.w = txtSurface->w;
        mainRect.h = txtSurface->h;
    }
    /*Для цифр устанавливаем одинаковую ширину */
    else
    {
        mainRect.w = 25;
        mainRect.h = txtSurface->h;
    }
    SDL_FreeSurface(txtSurface);
    *t = newTexture;

    return true;
}