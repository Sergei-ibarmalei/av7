#include "borderclass.h"

Border::Border()
{
    border = new (std::nothrow) rect_[allBorderSides];
    if (!border)
    {
        init = false;
        return;
    }
    setBorder();


}

Border::~Border()
{
    delete[] border;
    border = nullptr;
}

void Border::ShowBorder(Sdl* sdl)
{
    SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF, 0, 0, 0xFF);
    SDL_RenderFillRect(sdl->Renderer(), &border[borderUp]);
    SDL_RenderFillRect(sdl->Renderer(), &border[borderDown]);
    SDL_RenderFillRect(sdl->Renderer(), &border[borderLeft]);
    SDL_RenderFillRect(sdl->Renderer(), &border[borderRight]);
    SDL_SetRenderDrawColor(sdl->Renderer(), 0, 0, 0, 0xFF);   
    SDL_RenderFillRect(sdl->Renderer(), &border[blackBanner]);
}

void Border::setBorder()
{
    border[borderUp].x = UP_BORDER_X;
    border[borderUp].y = UP_BORDER_Y;
    border[borderUp].w = UP_BORDER_W;
    border[borderUp].h = UP_BORDER_H;

    border[borderDown].x = DOWN_BORDER_X;
    border[borderDown].y = DOWN_BORDER_Y;
    border[borderDown].w = DOWN_BORDER_W;
    border[borderDown].h = DOWN_BORDER_H;

    border[borderLeft].x = LEFT_BORDER_X;
    border[borderLeft].y = LEFT_BORDER_Y;
    border[borderLeft].w = LEFT_BORDER_W;
    border[borderLeft].h = LEFT_BORDER_H;

    border[borderRight].x = RIGHT_BORDER_X;
    border[borderRight].y = RIGHT_BORDER_Y;
    border[borderRight].w = RIGHT_BORDER_W;
    border[borderRight].h = RIGHT_BORDER_H;

    border[blackBanner].x = 0;
    border[blackBanner].y = 0;
    border[blackBanner].w = border[borderUp].w;
    border[blackBanner].h = border[borderUp].y;
}