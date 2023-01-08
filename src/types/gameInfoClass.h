/*Класс GameInfoClass для отображения счета и количества жизней*/

#ifndef GAMEINFOCLASS_H
#define GAMEINFOCLASS_H

#include "texturescollection.h"
#include "../loging/loging.h"

class GameInfoClass
{
    private:
    enum {scoreBannerLen = 6};
    enum {heroLivesLen = 3};
    texture_*  heap_scoreBanner {nullptr};
    texture_*  heap_heroLives   {nullptr};
    texture_*  hero_texture {nullptr};
    bool       init {true};
    bool       initScoreBanner(tc& collection, log_::Log& log);
    bool       initHeroLives(tc& collection, log_::Log& log);

    public:
    explicit GameInfoClass(tc& collection, log_::Log& log);
    GameInfoClass(const GameInfoClass& gi) = delete;
    GameInfoClass& operator=(const GameInfoClass& ) = delete;
    ~GameInfoClass();
    bool Status() const {return init;}
};


#endif