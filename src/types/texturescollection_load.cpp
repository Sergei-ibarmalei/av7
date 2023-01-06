#include "texturescollection.h"

using string_ = std::string;

bool TexturesCollection::loadFromFile(SDL_Renderer* r,
                                      SDL_Texture** t,
                                      rect_& mainRect,
                                      const char* name, log_::Log& log)
{

    if (!r)
    {
        log.log_info = "In loadFromfile renderer is absent or nullprt."; 
        log.push(log.log_info);
        status = false;
        return false;
    }
    if (!t)
    {
        log.log_info = "In loadFromFile texture is absent or nullptr.";
        log.push(log.log_info);
        status = false;
        return false;
    }
    if (!name)
    {
        log.log_info = "In loadFromFile name is absent or nullptr.";
        log.push(log.log_info);
        status = false;
        return false;
    }
    textureFree(*t);
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(name);
    if (!loadedSurface)
    {
        log.log_info = "Cannot create loaded surface.";
        log.push(log.log_info);
        status = false;
        return false;
    }
    SDL_SetColorKey(loadedSurface,
                    SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, 0, 0, 0));
    newTexture = SDL_CreateTextureFromSurface(r, loadedSurface);
    if (!newTexture)
    {
        log.log_info = "Unable to create texture from " + string_(name);
        log.push(log.log_info);
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
                                      gamefont_* font, log_::Log& log)
{
    if (!r)
    {
        log.log_info = "In load from text renderer is absent or is nullptr.";
        log.push(log.log_info);
        return false;
    }
    if (!t)
    {
        log.log_info = "In load from text texture is absent or is nullptr.";
        log.push(log.log_info);
        return false;
    }
    if (!textToTexture)
    {
        log.log_info = "In load from text name is absetn or is nullptr.";
        log.push(log.log_info);
        return false;
    }
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* txtSurface = 
    TTF_RenderText_Solid(font->font,
                         textToTexture,
                         font->color);
    if (!txtSurface)
    {
        log.log_info = "Unable to render text surface.";
        log.push(log.log_info);
        return false;
    }
    newTexture = SDL_CreateTextureFromSurface(r, txtSurface);
    if (!newTexture)
    {
        log.log_info = "Unable to create texture from rendererd text " +
            string_(SDL_GetError());
        log.push(log.log_info);
        return false;
    }

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