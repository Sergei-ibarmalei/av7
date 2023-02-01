/*Класс GameInfoClass для отображения счета и количества жизней*/

#ifndef GAMEINFOCLASS_H
#define GAMEINFOCLASS_H

#include "texturescollection.h"
#include "sdlclass.h"
#include "gametypes.h"
#include "../consts/gameconsts.h"

class GameInfoClass
{
    private:
    enum {scoreBannerLen = 6};
    enum {heroLivesLen = 4};
    enum {textureOfZero};
    enum {x0, x1, x2, x3, all_x};
    enum {allDigits = 10,};
    texture_*  heap_scoreBanner {nullptr};
    texture_*  heap_heroLivesMult   {nullptr};
    texture_*  hero_texture {nullptr};
    texture_*  scoreBanner {nullptr};
    texture_*  heroLivesMult   {nullptr};
    bool       init {true};
    bool       initScoreBanner_heap(const tc& collection);
    bool       initHeroLives_heap(const tc& collection);
    bool       initScoreBanner();
    bool       initHeroLives(const tc& collection, status_t& status);
    void       setScoreBannerCoords();
    void       setHeroLivesCoords();
    void       clearScoreBanner();

    public:
    explicit GameInfoClass(const tc& collection, status_t& status);
    GameInfoClass(const GameInfoClass& gi) = delete;
    GameInfoClass& operator=(const GameInfoClass& ) = delete;
    ~GameInfoClass();
    bool Status() const {return init;}
    void ShowGameInfo(const Sdl* sdl, status_t& gameStatus);
    void ChangeScore(status_t& status);
    texture_* HeapDigits() const {return heap_scoreBanner;}
};


#endif