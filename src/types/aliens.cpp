#include "aliens.h"
#include "../core/checking.h"


PlainAlienABC::PlainAlienABC(const texture_* t, 
                             const int arrLen, 
                             const plot* start,
                             const texture_* lazer): ComplexObject(t, arrLen)
{
    //std::cout << "In PlainAlienABC ctor.\n";
    lazerMainRect = new rect_;
    lazerMainRect->w = lazer->main_rect.w;
    lazerMainRect->h = lazer->main_rect.h;
    setToStartPos(start->x, start->y);
    initLazerStart();
    ElementaryObject::ResetOnScreen(false);
}

PlainAlienABC::~PlainAlienABC()
{
    //std::cout << "In PlainAlienABC dtor.\n";
    delete lazerMainRect;
    lazerMainRect = nullptr;
    delete lazerStart;
    lazerStart = nullptr;
}

void PlainAlienABC::setToStartPos(const int x, const int y)
{
    ElementaryObject::setUpLeftCorner(x, y);
}

void PlainAlienABC::initLazerStart()
{
    ComplexObject::lazerStart = new plot;
    recomputeLazerStart();
}

void PlainAlienABC::recomputeLazerStart()
{
    #define PLAINALIEN_X ElementaryObject::GetMainRect_x()
    #define PLAINALIEN_H_HALF ElementaryObject::GetMainRectH_Half()

    ComplexObject::lazerStart->x = 
            PLAINALIEN_X - lazerMainRect->w - PLAINALIENLASER_OFFSET;
    ComplexObject::lazerStart->y = PLAINALIEN_H_HALF;

    #undef  PLAINALIEN_X
    #undef  PLAINALIEN_H_HALF
}

void PlainAlienABC::show(const Sdl* sdl) const
{
    ComplexObject::Show(sdl);
}




PlainAlien_t1::PlainAlien_t1(const texture_* t,
                             const plot* start,
                             const texture_* lazer):PlainAlienABC(t,
                             re::alien_t1::t1_allR, start, lazer)
{
    //std::cout << "In PlainAlien_t1 ctor.\n";
    ElementaryObject::Velocities()->x = -ALIENFLEET_1_VELOCITY;
    ElementaryObject::Velocities()->y = 0;
}

PlainAlien_t1::~PlainAlien_t1()
{
    //std::cout << "In PlainAlien_t1 dtor.\n";

}

void PlainAlien_t1::Show(const Sdl* sdl)
{
    PlainAlienABC::Show(sdl);
}

void PlainAlien_t1::setCr()
{
    #define CR ComplexObject::cr->Array()
    #define ONE re::alien_t1::t1_one
    #define TWO re::alien_t1::t1_two
    #define THREE re::alien_t1::t1_three
    #define MAINR_UPLEFT_X ElementaryObject::GetMainRect_x()
    #define MAINR_UPLEFT_Y ElementaryObject::GetMainRect_y()


    CR[ONE].x = MAINR_UPLEFT_X + 32;
    CR[ONE].y = MAINR_UPLEFT_Y;
    CR[ONE].w = 39;
    CR[ONE].h = 31;

    CR[TWO].x = MAINR_UPLEFT_X + 4;
    CR[TWO].y = CR[ONE].y + CR[ONE].h;
    CR[TWO].w = 87;
    CR[TWO].h = 32;

    CR[THREE].x = CR[ONE].x;
    CR[THREE].y = CR[TWO].y + CR[TWO].h;
    CR[THREE].w = CR[ONE].w;
    CR[THREE].h = CR[ONE].h;



    #undef CR
    #undef ONE
    #undef TWO
    #undef THREE
}

void PlainAlien_t1::Move()
{
    //if (ElementaryObject::OnScreen() == false) return;
    ElementaryObject::resetUpLeftCorner();
    setCr();
    if (hasCrossedLeft(ElementaryObject::GetMainRect_x()))
    {
        ElementaryObject::ResetOnScreen(false);
        return;
    }
}