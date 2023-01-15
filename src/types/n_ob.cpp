#include "n_ob.h"

ElementaryObject::~ElementaryObject()
{
    obj_texture->texture = nullptr;
    delete obj_texture;
    obj_texture = nullptr;
    delete obj_velocities;
    obj_velocities = nullptr;
}


ElementaryObject::ElementaryObject(const texture_* t)
{
    if (!t)
    {
        init = false;
        return;
    }
    obj_texture = new (std::nothrow) texture_;
    obj_texture->texture = t->texture;
    obj_texture->main_rect.w = t->main_rect.w;
    obj_texture->main_rect.h = t->main_rect.h;
    obj_texture->main_rect.x = obj_texture->main_rect.y = 0;
    obj_velocities = new plot{0, 0};

}

ElementaryObject::ElementaryObject(const ElementaryObject& eo)
{
    obj_texture = new (std::nothrow) texture_;
    obj_texture->texture = eo.obj_texture->texture;
    obj_texture->main_rect = eo.obj_texture->main_rect;
    obj_velocities = new (std::nothrow) plot;
    obj_velocities->x = eo.obj_velocities->x;
    obj_velocities->y = eo.obj_velocities->y;
}

ElementaryObject& ElementaryObject::operator=(const ElementaryObject& eo)
{
    if (this == &eo) return *this;
    obj_texture->texture = nullptr;
    delete obj_texture;
    obj_texture = new (std::nothrow) texture_;
    obj_texture->texture = eo.obj_texture->texture;
    obj_texture->main_rect = eo.obj_texture->main_rect;
    return *this;
}

bool ElementaryObject::operator==(const ElementaryObject& eo)
{
    return obj_texture->main_rect == eo.obj_texture->main_rect;
}

bool ElementaryObject::operator==(const ElementaryObject* peo)
{
    return obj_texture->main_rect == peo->obj_texture->main_rect;
}

void ElementaryObject::ShowObj(const Sdl* sdl)
{
    sdl->TextureRender(obj_texture->texture, &obj_texture->main_rect);
}

#ifdef SHOW_COL_R
void ElementaryObject::showCollisionMainRect(const Sdl* sdl)
{
    SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF, 0, 0, 0xFF);
    SDL_RenderDrawRect(sdl->Renderer(), &obj_texture->main_rect);
    SDL_SetRenderDrawColor(sdl->Renderer(), 0, 0, 0, 0);
}
#endif

void ElementaryObject::resetUpLeftCorner()
{
    obj_texture->main_rect.x += obj_velocities->x;
    obj_texture->main_rect.y += obj_velocities->y;
}

void ElementaryObject::setUpLeftCorner(const int x, const int y)
{
    obj_texture->main_rect.x = x;
    obj_texture->main_rect.y = y;
}

void ElementaryObject::resetUpLeftCorner_x(const int x)
{
    obj_texture->main_rect.x += x;
}

void ElementaryObject::resetUpLeftCorner_y(const int y)
{
    obj_texture->main_rect.y += y;
}


ComplexObject::ComplexObject(const ComplexObject& co): ElementaryObject(co)
{
    delete cr;
    cr = new (std::nothrow) CRC(co.collisionArrLen);
    *cr = *co.cr;
}

ComplexObject::~ComplexObject()
{
    delete cr;
    cr = nullptr;
    
}




ComplexObject::ComplexObject(const texture_* t, const int al): ElementaryObject(t)
{
    if (al <= 0)
    {
        init = false; return;
    }
    collisionArrLen = al;
    cr = new (std::nothrow) CRC(collisionArrLen);
    if (cr->Status() == false)
    {
        init = false; return;
    }
}

bool ComplexObject::operator==(const ElementaryObject& eo)
{
    return ElementaryObject::obj_texture->main_rect == eo.MainRect();
}

bool ComplexObject::operator==(const ComplexObject& co)
{
    if (ElementaryObject::obj_texture->main_rect == co.MainRect())
    {
        return *cr == *co.cr;
    }
    return false;
}

#ifdef SHOW_COL_R
    void ComplexObject::ShowColR(const Sdl* sdl, const int len)
    {
        SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF, 0, 0, 0xFF);
        for (int r = 0; r < len; ++r)
        {
            SDL_RenderDrawRect(sdl->Renderer(), &cr->Array()[r]);
        }
        ElementaryObject::showCollisionMainRect(sdl);
    }
#endif




NHero::NHero(const texture_* t): ComplexObject(t, re::heros::allR)
{
    if (ComplexObject::init == false) return;
    initHeroStopIntro();
    setToStartPos();
    setCr();
    initLazerStart();
}

void NHero::initHeroStopIntro()
{
    #define HERO_W ElementaryObject::obj_texture->main_rect.w

    heroStopIntro = new plot;
    heroStopIntro->x = BORDER_THICKNESS + (4 * HERO_W);
    heroStopIntro->y = ElementaryObject::obj_texture->main_rect.y;

    #undef HERO_W
}

void NHero::ShowHero(const Sdl* sdl)
{
    ElementaryObject::ShowObj(sdl);
}

void NHero::setToStartPos()
{
    #define HEROSTART_X -BORDER_THICKNESS\
             - ElementaryObject::obj_texture->main_rect.w
    #define HEROSTART_Y S_H / 2\
             - ElementaryObject::obj_texture->main_rect.h / 2

    ElementaryObject::setUpLeftCorner(HEROSTART_X, HEROSTART_Y);

    #undef HEROSTART_X
    #undef HEROSTART_Y
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

    #define MAINR_UPLEFT_X ElementaryObject::obj_texture->main_rect.x
    #define MAINR_UPLEFT_Y ElementaryObject::obj_texture->main_rect.y

    CR[ONE].x = MAINR_UPLEFT_X + 2;
    CR[ONE].y = MAINR_UPLEFT_Y + 4;
    CR[ONE].w = 45;
    CR[ONE].h = 17;


    CR[TWO].x = MAINR_UPLEFT_X + 19;
    CR[TWO].y = CR[ONE].y + CR[ONE].h;
    CR[TWO].h = 16;
    CR[TWO].w = 68;

    CR[THREE].x = CR[TWO].x;
    CR[THREE].y = CR[TWO].y + CR[TWO].h;
    CR[THREE].w = 117;
    CR[THREE].h = 36;

    CR[FOUR].x = CR[TWO].x;
    CR[FOUR].y = CR[THREE].y + CR[THREE].h;
    CR[FOUR].w = CR[TWO].w;
    CR[FOUR].h = 16;

    CR[FIVE].x = CR[ONE].x;
    CR[FIVE].y = CR[FOUR].y + CR[FOUR].h;
    CR[FIVE].w = CR[ONE].w;
    CR[FIVE].h = CR[ONE].h;


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
}

void NHero::initLazerStart()
{
    ComplexObject::lazerStart = new plot;
    recomputeLazerStart();

}

void NHero::recomputeLazerStart()
{
    #define HERO_W ComplexObject::obj_texture->main_rect.x+\
                    ComplexObject::obj_texture->main_rect.w

    #define HERO_H_HALF ComplexObject::obj_texture->main_rect.y+\
                        ComplexObject::obj_texture->main_rect.h / 2

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
    if (isGonnaCrossUp())    return;
    if (isGonnaCrossDown())  return;
    if (isGonnaCrossRight()) return;
    if (isGonnaCrossLeft())  return;
    ElementaryObject::resetUpLeftCorner();

    NHero::setCr();

    NHero::recomputeLazerStart();
}




bool NHero::isGonnaCrossUp()
{
    #define MAIN_RECT_UP ElementaryObject::GetMainRect_y()
    #define VELOCITY_Y ElementaryObject::Velocities()->y

    return (MAIN_RECT_UP + VELOCITY_Y) < UP_BORDER_Y + BORDER_THICKNESS;

    #undef MAIN_RECT_UP
    #undef VELOCITY_Y
}


bool NHero::isGonnaCrossDown()
{
    #define MAIN_RECT_DOWN ElementaryObject::GetMainRectH()
    #define VELOCITY_Y ElementaryObject::Velocities()->y

    return (MAIN_RECT_DOWN + VELOCITY_Y) > DOWN_BORDER_Y;

    #undef MAIN_RECT_DOWN
    #undef VELOCITY_Y

}

bool NHero::isGonnaCrossRight()
{
    #define MAIN_RECT_WIDTH ElementaryObject::GetMainRectW()
    #define VELOCITY_X ElementaryObject::Velocities()->x

    return (MAIN_RECT_WIDTH + VELOCITY_X) > RIGHT_BORDER_X;

    #undef MAIN_RECT_WIDTH 
    #undef VELOCITY_X 
}

bool NHero::isGonnaCrossLeft()
{
    
    #define MAIN_RECT_LEFT ElementaryObject::GetMainRect_x()
    #define VELOCITY_X ElementaryObject::Velocities()->x

    return (MAIN_RECT_LEFT + VELOCITY_X) < LEFT_BORDER_X + LEFT_BORDER_W;

    #undef MAIN_RECT_LEFT 
    #undef VELOCITY_X 
}

#ifdef SHOW_COL_R
    void NHero::ShowColR(const Sdl* sdl)
    {
        ComplexObject::ShowColR(sdl, re::heros::allR);
    }
#endif