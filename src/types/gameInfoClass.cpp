#include "gameInfoClass.h"

GameInfoClass::GameInfoClass(tc& collection, log_::Log& log)
{

    if (!(initScoreBanner(collection, log)))
    {
        log.log_info = "Cannot create gameInfo class.\n";
        log.push(log.log_info);
        init = false;
        return;
    }
    if (!(initHeroLives(collection, log)))
    {
        log.log_info = "Cannot create gameInfo class.\n";
        log.push(log.log_info);
        init = false;
        return;
    }
}

GameInfoClass::~GameInfoClass()
{
    if (heap_scoreBanner)
    {
        for (int t = 0; t < scoreBannerLen; ++t)
        {
            heap_scoreBanner[t].texture = nullptr;
        }
        delete[] heap_scoreBanner;
        heap_scoreBanner = nullptr;
    }
    if (heap_heroLives)
    {
        for (int t = 0; t < heroLivesLen; ++t)
        {
            heap_heroLives[t].texture = nullptr;
        }
        delete[] heap_heroLives;
        heap_heroLives = nullptr;
    }
    hero_texture = nullptr;
}

bool GameInfoClass::initScoreBanner(tc& collection, log_::Log& log)
{
    int offSet = tn::zeroScoreB;
    heap_scoreBanner = new (std::nothrow) texture_[scoreBannerLen];
    if (!heap_scoreBanner)
    {
        log.log_info = "Cannot allocate memory for score banner.\n";
        log.push(log.log_info); 
        return false;
    }
    for (int t = 0; t < scoreBannerLen; ++t)
    {
        heap_scoreBanner[t] = collection.Strings()[t+offSet];
    }
    return true;
}

bool GameInfoClass::initHeroLives(tc& collection, log_::Log& log)
{
    int offSet = tn::x1;
    heap_heroLives = new (std::nothrow) texture_[heroLivesLen];
    if (!heap_heroLives)
    {
        log.log_info = "Cannot allocate memory for hero lives multiplivate.\n";
        log.push(log.log_info);
        return false;
    }
    hero_texture = &collection.Pictures()[tn::hero];
    for (int t = 0; t < heroLivesLen; ++t)
    {
        heap_heroLives[t] = collection.Pictures()[t+offSet];
    }
    return true;
}