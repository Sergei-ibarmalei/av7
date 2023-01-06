#ifndef GAMEFONTS_H
#define GAMEFONTS_H

#include "sdltypes.h"

struct GameFont
{
    TTF_Font* font = nullptr;
    int       size;
    SDL_Color color;
    rect_     rect;
    bool      isAlpha;
};


const SDL_Color DARKORANGE {0xFF, 0x8C, 0, 0xFF};
const SDL_Color FIREBRICK  {0xB2, 0x22, 0x22, 0xFF};
const SDL_Color INDIANRED  {0xCD, 0x5C, 0x5C, 0xFF};
const SDL_Color POWDERBLUE {0xB0, 0xE0, 0xE6,0xFF};
const SDL_Color LIGHTSTEELBLUE {0xB0, 0xC4, 0xDE, 0xFF};





#define MAINMENUFONTSIZE 100
#define SCORESFONTSIZE   30
#define SCORESBANNERFONTSIZE 40
#define PAUSEFONTSIZE       150
#define PRESSESCFONTSIZE    40
#define LIVEMULTFONTSIZE    40

#define GLOBALFONTNAME "tower-ruins/towerruins.ttf"

using gamefont_ = GameFont;



#endif