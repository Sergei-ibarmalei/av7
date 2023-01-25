#include "n_ob.h"


AlienABC::AlienABC(const texture_* t, 
                             const int arrLen, 
                             const plot* start,
                             const texture_* lazer): ComplexObject(t, arrLen)
{
    //std::cout << "In AlienABC ctor.\n";
    lazerMainRect = new rect_;
    lazerMainRect->w = lazer->main_rect.w;
    lazerMainRect->h = lazer->main_rect.h;
    setToStartPos(start->x, start->y);
    initLazerStart();
    ElementaryObject::ResetOnScreen(false);
}

AlienABC::~AlienABC()
{
    //std::cout << "In AlienABC dtor.\n";
    delete lazerMainRect;
    lazerMainRect = nullptr;
    delete lazerStart;
    lazerStart = nullptr;
}

void AlienABC::setToStartPos(const int x, const int y)
{
    ElementaryObject::setUpLeftCorner(x, y);
}

void AlienABC::initLazerStart()
{
    ComplexObject::lazerStart = new plot;
    recomputeLazerStart();
}

void AlienABC::recomputeLazerStart()
{
    #define PLAINALIEN_X GetMainRect_x()
    #define PLAINALIEN_H_HALF GetMainRectH_Half()

    lazerStart->x = 
            PLAINALIEN_X - PLAINALIENLASER_OFFSET;
    lazerStart->y = PLAINALIEN_H_HALF - lazerMainRect->h / 2;

    #undef  PLAINALIEN_X
    #undef  PLAINALIEN_H_HALF
}

void AlienABC::show(const Sdl* sdl) const
{
    ComplexObject::Show(sdl);
}



