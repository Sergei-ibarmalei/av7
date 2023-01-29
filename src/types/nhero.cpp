#include "nhero.h"
#include "../core/checkcrossing.h"


NHero::NHero(const texture_* t): ComplexObject(t, re::heros::allR)
{
    if (ComplexObject::init == false) return;

    #define HEROSTART_X -BORDER_THICKNESS\
             - ElementaryObject::obj_texture->main_rect.w
    #define HEROSTART_Y S_H / 2\
             - ElementaryObject::obj_texture->main_rect.h / 2

    Velocities()->x = Velocities()->y = 0;
    initHeroStopIntro();
    setToStartPos(HEROSTART_X, HEROSTART_Y);
    setCr();
    initLazerStart();
    heroEchelon = new (std::nothrow) echelon;
    if (!heroEchelon) init = false;
    #undef HEROSTART_X
    #undef HEROSTART_Y
}

void NHero::Reincarnate()
{
    #define HEROSTART_X -BORDER_THICKNESS\
             - ElementaryObject::obj_texture->main_rect.w
    #define HEROSTART_Y S_H / 2\
             - ElementaryObject::obj_texture->main_rect.h / 2


    Velocities()->x = Velocities()->y = 0;
    initHeroStopIntro();
    setToStartPos(HEROSTART_X, HEROSTART_Y);
    setCr();
    initLazerStart();
    
    #undef HEROSTART_X
    #undef HEROSTART_Y
}


void NHero::recomputeHeroEchelon()
{
    heroEchelon->hi = obj_texture->main_rect.y - HERO_ECHELON_HI;
    heroEchelon->low = (obj_texture->main_rect.y + obj_texture->main_rect.h) +
        HERO_ECHELON_LOW;
}

void NHero::initHeroStopIntro()
{
    #define HERO_W ElementaryObject::obj_texture->main_rect.w

    heroStopIntro = new plot;
    heroStopIntro->x = BORDER_THICKNESS + (4 * HERO_W);
    heroStopIntro->y = ElementaryObject::obj_texture->main_rect.y;

    #undef HERO_W
}


void NHero::setToStartPos(const int startx, const int starty)
{
    ElementaryObject::setUpLeftCorner(startx, starty);
}


/*Определение прям. пересечений*/
void NHero::setCr()
{
    #define CR ComplexObject::cr->Array()
    #define ONE re::heros::one
    #define TWO re::heros::two
    #define THREE re::heros::three
    #define FOUR re::heros::four
    #define FIVE re::heros::five

    #define MAINR_UPLEFT_X GetMainRect_x()
    #define MAINR_UPLEFT_Y GetMainRect_y()

    CR[ONE].x = MAINR_UPLEFT_X + 2;
    CR[ONE].y = MAINR_UPLEFT_Y + 4;
    CR[ONE].h = 17;
    CR[ONE].w = 45;


    CR[TWO].x = MAINR_UPLEFT_X + 19;
    CR[TWO].y = CR[ONE].y + CR[ONE].h;
    CR[TWO].h = 16;
    CR[TWO].w = 68;

    CR[THREE].x = CR[TWO].x;
    CR[THREE].y = CR[TWO].y + CR[TWO].h;
    CR[THREE].h = 36;
    CR[THREE].w = 117;

    CR[FOUR].x = CR[TWO].x;
    CR[FOUR].y = CR[THREE].y + CR[THREE].h;
    CR[FOUR].h = 16;
    CR[FOUR].w = CR[TWO].w;

    CR[FIVE].x = CR[ONE].x;
    CR[FIVE].y = CR[FOUR].y + CR[FOUR].h;
    CR[FIVE].h = CR[ONE].h;
    CR[FIVE].w = CR[ONE].w;


    #undef MAINR_UPLEFT_X
    #undef MAINR_UPLEFT_Y
    #undef CR
    #undef FIVE
    #undef FOUR
    #undef THREE
    #undef TWO
    #undef ONE
}

NHero::~NHero()
{
    delete heroStopIntro;
    heroStopIntro = nullptr;
    delete lazerStart;
    lazerStart = nullptr;
    delete heroEchelon;
    heroEchelon = nullptr;
}

void NHero::initLazerStart()
{
    ComplexObject::lazerStart = new plot;
    recomputeLazerStart();

}

void NHero::recomputeLazerStart()
{
    #define HERO_W ElementaryObject::GetMainRectW()

    #define HERO_H_HALF ElementaryObject::GetMainRectH_Half()

    lazerStart->x = HERO_W + PLAINLASER_OFFSET;
    lazerStart->y = HERO_H_HALF;

    #undef HERO_H_HALF
    #undef HERO_W
}

void NHero::HeroMovesInIntro(status_t& status)
{
    #define HERO_MR_X ElementaryObject::GetMainRect_x()
    #define HERO_W ElementaryObject::GetMainRectW()

    if ( (HERO_MR_X + HERO_W) >= heroStopIntro->x)
    {
        status.heroIntro = false;
        setCr();
        return;
    }
    ElementaryObject::resetUpLeftCorner_x(HERO_VELOCITY_X);

    #undef HERO_W
    #undef HERO_MR_X
}



void NHero::HeroUp()
{
    ElementaryObject::Velocities()->y -= HERO_VELOCITY_Y;
    NHero::Move();
}

void NHero::HeroDown()
{
    ElementaryObject::Velocities()->y += HERO_VELOCITY_Y;
    NHero::Move();
}

void NHero::HeroRight()
{
    ElementaryObject::Velocities()->x += HERO_VELOCITY_X;
    NHero::Move();
}

void NHero::HeroLeft()
{
    ElementaryObject::Velocities()->x -= HERO_VELOCITY_X;
    NHero::Move();
}

void NHero::HeroStop()
{
    ElementaryObject::Velocities()->x = ElementaryObject::Velocities()->y = 0;
}

void NHero::Move()
{
    if (IsItGone() == true) return;
    if (isGonnaCrossUp())    return;
    if (isGonnaCrossDown())  return;
    if (isGonnaCrossRight()) return;
    if (isGonnaCrossLeft())  return;
    resetUpLeftCorner();

    setCr();

    recomputeLazerStart();
    recomputeHeroEchelon();
}




bool NHero::isGonnaCrossUp()
{
    #define MAIN_RECT_UP ElementaryObject::GetMainRect_y()
    #define VELOCITY_Y ElementaryObject::Velocities()->y

    return isGonnaCrossUp_check(MAIN_RECT_UP, VELOCITY_Y);

    #undef MAIN_RECT_UP
    #undef VELOCITY_Y
}


bool NHero::isGonnaCrossDown()
{
    #define MAIN_RECT_HEIGHT ElementaryObject::GetMainRectH()
    #define VELOCITY_Y ElementaryObject::Velocities()->y

    return isGonnaCrossDown_check(MAIN_RECT_HEIGHT, VELOCITY_Y);

    #undef MAIN_RECT_HEIGHT
    #undef VELOCITY_Y

}

bool NHero::isGonnaCrossRight()
{
    #define MAIN_RECT_WIDTH ElementaryObject::GetMainRectW()
    #define VELOCITY_X ElementaryObject::Velocities()->x

    return isGonnaCrossRight_check(MAIN_RECT_WIDTH, VELOCITY_X);

    #undef MAIN_RECT_WIDTH 
    #undef VELOCITY_X 
}

bool NHero::isGonnaCrossLeft()
{
    
    #define MAIN_RECT_LEFT ElementaryObject::GetMainRect_x()
    #define VELOCITY_X ElementaryObject::Velocities()->x

    return isGonnaCrossLeft_check(MAIN_RECT_LEFT, VELOCITY_X);

    #undef MAIN_RECT_LEFT 
    #undef VELOCITY_X 
}



