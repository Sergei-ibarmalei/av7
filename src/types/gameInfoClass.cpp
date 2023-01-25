#include "gameInfoClass.h"
#include "../consts/gameconsts.h"

GameInfoClass::GameInfoClass(tc& collection, log_::Log& log)
{

    if (!(initScoreBanner_heap(collection, log)))
    {
        log.log_info = "Cannot create gameInfo class.\n";
        log.push(log.log_info);
        init = false;
        return;
    }
    if (!(initHeroLives_heap(collection, log)))
    {
        log.log_info = "Cannot create gameInfo class.\n";
        log.push(log.log_info);
        init = false;
        return;
    }


    initHeroLives(collection);

    initScoreBanner(log);
}

GameInfoClass::~GameInfoClass()
{
    for (int t = 0; t < allDigits; ++t)
    {
        heap_scoreBanner[t].texture = nullptr;
    }
    delete[] heap_scoreBanner;
    heap_scoreBanner = nullptr;

    for (int t = 0; t < heroLivesLen; ++t)
    {
        heap_heroLivesMult[t].texture = nullptr;
    }
    delete[] heap_heroLivesMult;
    heap_heroLivesMult = nullptr;

    for (int segment = 0; segment < scoreBannerLen; ++segment)
    {
        scoreBanner[segment].texture = nullptr;
    }
    delete[] scoreBanner;
    scoreBanner = nullptr;
    heroLivesMult = nullptr;
    hero_texture = nullptr;
}

bool GameInfoClass::initScoreBanner(log_::Log& log)
{
    scoreBanner = new (std::nothrow) texture_[scoreBannerLen];
    if (!scoreBanner)
    {
        log.log_info = "Cannot allocate memory for score banner.";
        log.push(log.log_info);
        return false;
    }
    /*Устанавливаем все шесть сегментов scoreBanner в текстуру "0"*/
    for (int segment = 0; segment < scoreBannerLen; ++segment)
    {
        scoreBanner[segment] = heap_scoreBanner[textureOfZero];
    }
    setScoreBannerCoords();
    return true;

}

void GameInfoClass::initHeroLives(tc& collection)
{

    /*Берем уменьшенную текстуру героя из коллекции*/
    hero_texture = &collection.Pictures()[tn::hero_scale_mult];
    /*Множитель изначально ставим в х3*/
    heroLivesMult = &heap_heroLivesMult[x3];
    setHeroLivesCoords();
}

void GameInfoClass::setScoreBannerCoords()
{
    #define SPACE 4
    #define WIDTH scoreBanner[textureOfZero].main_rect.w
    #define BORDER_UP_Y UP_BORDER_Y
    #define HEIGHT scoreBanner[textureOfZero].main_rect.h

    int scoreBanner_x = S_W - (scoreBannerLen * WIDTH) -
        ((scoreBannerLen-1) * SPACE);
    int scoreBanner_y = BORDER_UP_Y - SPACE - HEIGHT;

    for (int s = 0; s < scoreBannerLen; ++s)
    {
        scoreBanner[s].main_rect.x = 
            scoreBanner_x + (WIDTH + SPACE)*s;
        scoreBanner[s].main_rect.y = scoreBanner_y;
    }

    #undef SPACE
    #undef WIDTH
    #undef BORDER_UP_Y
    #undef HEIGHT

}

void GameInfoClass::setHeroLivesCoords()
{

    #define LEFT_SIDE LEFT_BORDER_W + BORDER_THICKNESS
    #define UP_SIDE UP_BORDER_Y //- hero_texture->rect.h
    #define HEROTEXTURE_H hero_texture->rect.h
    #define XTEXTURE_H heap_heroLivesMult[textureOfZero].main_rect.h 
    #define HEROTEXTURE_W  hero_texture->main_rect.x + hero_texture->main_rect.w


    /*Устанавливаем координаты х у для уменьшенной текстуры героя*/
    hero_texture->main_rect.x = LEFT_SIDE + BORDER_THICKNESS;
    hero_texture->main_rect.y = UP_SIDE - hero_texture->main_rect.h;
    for (int t = x1; t < all_x; ++t)
    {
        heap_heroLivesMult[t].main_rect.x = 
            HEROTEXTURE_W + 2 * BORDER_THICKNESS;
        heap_heroLivesMult[t].main_rect.y = 
            UP_SIDE - XTEXTURE_H - BORDER_THICKNESS;

    }

    #undef HEROTEXTURE_W
    #undef XTEXTURE_H
    #undef HEROTEXTURE_H
    #undef UP_SIDE
    #undef LEFT_SIDE
}

void GameInfoClass::ShowGameInfo(const Sdl* sdl, status_t& gameStatus)
{
    /*Рисуем счет справа*/
    for (int segment = 0; segment < scoreBannerLen; ++segment)
    {
        sdl->TextureRender(scoreBanner[segment].texture,
                            &scoreBanner[segment].main_rect);
    }
    
    /*Рисуем оставшиеся жизни слева*/
    /*Сперва рисуем уменьшенную копию героя*/
    sdl->TextureRender(hero_texture->texture, &hero_texture->main_rect);

    /*Рисуем множитель*/
    heroLivesMult = &heap_heroLivesMult[gameStatus.HeroLives-1];

    sdl->TextureRender(heroLivesMult->texture, &heroLivesMult->main_rect);

}

/*Куча текстур цифр для отображения счета*/
bool GameInfoClass::initScoreBanner_heap(tc& collection, log_::Log& log)
{
    int offSet = tn::zeroScoreB;
    heap_scoreBanner = new (std::nothrow) texture_[allDigits];
    if (!heap_scoreBanner)
    {
        log.log_info = "Cannot allocate memory for score banner_heap.\n";
        log.push(log.log_info); 
        return false;
    }
    /*Кидаем в кучу текстуры цифр от 0 до 9*/
    for (int t = 0; t < allDigits; ++t)
    {
        heap_scoreBanner[t] = collection.Strings()[t+offSet];
    }
    return true;
}

bool GameInfoClass::initHeroLives_heap(tc& collection, log_::Log& log)
{
    int offSet = tn::x1;
    heap_heroLivesMult = new (std::nothrow) texture_[heroLivesLen];
    if (!heap_heroLivesMult)
    {
        log.log_info = "Cannot allocate memory for hero lives_heap.\n";
        log.push(log.log_info);
        return false;
    }


    for (int t = 0; t < heroLivesLen; ++t)
    {
        
        heap_heroLivesMult[t] = collection.Strings()[t+offSet];
    }
    return true;
}

/*Изменение счета на велечину delta*/
void GameInfoClass::ChangeScore(status_t& status)
{
    int segment;
    int count {100'000};
    int first;
    int remainder; //остаток
    clearScoreBanner();

    #define SCORE status.gameScore

    first = SCORE / count;
    remainder = SCORE % count;
    for (segment = 0; segment < scoreBannerLen; ++segment)
    {
        count /= 10;
        if (heap_scoreBanner[first].texture == nullptr)
        {
            std::cout << "nullptr\n";
        }
        scoreBanner[segment].texture = heap_scoreBanner[first].texture;
        if (count)
        {
            first = remainder / count;
            remainder %= count;
        }
        else first = remainder;
    } 

    #undef SCORE

}


/*Очистка текстур в ScoreBanner*/
void GameInfoClass::clearScoreBanner()
{
    //if (!scoreBanner) return;
    for (int segment = 0; segment < scoreBannerLen; ++segment)
    {
        scoreBanner[segment].texture = nullptr;
    }
}

