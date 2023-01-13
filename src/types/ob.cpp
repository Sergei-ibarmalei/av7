#include "ob.h"

Object::Object(const texture_* t)
{
    obj_texture = new (std::nothrow) texture_;
    if (!obj_texture)
    {
        init = false; return;
    }
    obj_texture->texture = t->texture;
    obj_texture->main_rect.w = t->main_rect.w;
    obj_texture->main_rect.h = t->main_rect.h;
    obj_texture->main_rect.x = 0;
    obj_texture->main_rect.y = 0;
    ca = new (std::nothrow) Cca();
    if (!ca)
    {
        init = false;        
    }
    obj_velocities = new plot;
    obj_velocities->x = obj_velocities->y = 0;
}

Object::Object(const Object& o)
{
    obj_texture = new texture_;
    obj_texture->texture = o.obj_texture->texture;
    obj_texture->main_rect = o.obj_texture->main_rect;
}

Object& Object::operator=(const Object& o)
{
    if (this == &o) return *this;
    delete obj_texture;
    obj_texture = new texture_;
    obj_texture->texture = o.obj_texture->texture;
    obj_texture->main_rect = o.obj_texture->main_rect;
    ca = o.ca;
    delete obj_velocities;
    obj_velocities = new plot;
    obj_velocities->x = o.obj_velocities->x;
    obj_velocities->y = o.obj_velocities->y;
    return *this;
}



bool Object::operator==(const Object& o)
{
    return obj_texture->main_rect == o.obj_texture->main_rect;
}

bool Object::operator==(const Object* po)
{
    if (obj_texture->main_rect == po->obj_texture->main_rect)
    {
        return ca == po->ca;
    }
    return false;
}

Object::~Object()
{
    obj_texture->texture = nullptr;
    delete obj_texture;
    obj_texture = nullptr;
    delete obj_velocities;
    obj_velocities = nullptr;
}

void Object::ShowObj(Sdl* sdl)
{
    sdl->TextureRender(obj_texture->texture, &obj_texture->main_rect);
}

 
void Object::setUpLeftCorner(const int x, const int y)
{
    obj_texture->main_rect.x = x;
    obj_texture->main_rect.y = y;
}

/// @brief Перерасчет координат прямоугольников пересечений в двжиении по прямой
/// @param d направление движения
/// @param stopR  последний прямоугольник
/// @param delta  смещение
/// @param rects  массив прямоугольников пересечений
void Object::setRectsToNewPosStright(dir::direction d,
                                        const int stopR,
                                        const int delta,
                                        rect_* rects)
{
    for (int rect = 0; rect < stopR; ++rect)
    {
        switch (d)
        {
            case dir::right:
            {
                rects[rect].x += delta; break;
            }
            case dir::left:
            {
                rects[rect].x -= delta; break;
            }
            case dir::up:
            {
                rects[rect].y -= delta; break;
            }
            case dir::down:
            {
                rects[rect].y += delta; break;
            }
            default: {}
        }
    }
    resetUpLeftCorner(d, delta);
}

/// @brief Перерасчет верхнего левого угла главного прямоугольника пересечения
/// @param d      направление движения по прямой
/// @param delta  смещение
void Object::resetUpLeftCorner(dir::direction d, const int delta)
{
    switch (d)
    {
        case dir::right:
        {
            obj_texture->main_rect.x += delta; break;
        }
        case dir::left:
        {
            obj_texture->main_rect.x -= delta; break;
        }
        case dir::up:
        {
            obj_texture->main_rect.y -= delta; break;
        }
        case dir::down:
        {
            obj_texture->main_rect.y += delta; break;
        }
        default: {}
    }
}

void Object::resetUpLeftCorner()
{
    obj_texture->main_rect.x += obj_velocities->x;
    obj_texture->main_rect.y += obj_velocities->y;
}

/// @brief Перерасчет прямоугольников при движении ПО ПУТИ
/// @param rects_offSets массив смещений прямоугольников
/// @param stopR конец массива - последний прямоугольник
/// @param rects прямоугольники пересечений
void Object::setRectsToNewPosByPath(const plot* rects_offSets,
                                    const int stopR,
                                    rect_* rects)
{
    for (int r = 0; r < stopR; ++r)
    {
        rects[r].x = obj_texture->main_rect.x + rects_offSets[r].x;
        rects[r].y = obj_texture->main_rect.y + rects_offSets[r].y;
    }
}

#ifdef SHOW_COL_R
    void Object::showCollisionRects(Sdl* sdl, rect_* rects,
                                    int start, int end)
    {
        SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF,  0, 0, 0xFF);
        for (int r = start; r < end; ++r)
        {
            SDL_RenderDrawRect(sdl->Renderer(), &rects[r]);
        }
        SDL_RenderDrawRect(sdl->Renderer(), &obj_texture->main_rect);
        SDL_SetRenderDrawColor(sdl->Renderer(), 0, 0, 0, 0);
    }

    void Object::showCollisionMainRect(Sdl* sdl)
    {
        SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF,  0, 0, 0xFF);
        SDL_RenderDrawRect(sdl->Renderer(), &obj_texture->main_rect);
        SDL_SetRenderDrawColor(sdl->Renderer(), 0, 0, 0, 0);
    }
#endif



//--------------HERO-------------------------------------

#define MAINRECT_UPLEFT_X obj_texture->main_rect.x
#define MAINRECT_UPLEFT_Y obj_texture->main_rect.y
 
Hero::Hero(const texture_* t):
    Object(t)
{
    if (!t)
    {
        init = false;
        return;
    }
    collisionRects = new rect_[allRects];
    initHeroStopIntro();
    setToStartPosition();
    initLaserStart();
}

void Hero::initLaserStart()
{
    laserStart = new plot;
    recomputeLaserStart();
}

void Hero::recomputeLaserStart()
{
    #define HERO_W obj_texture->main_rect.x + obj_texture->main_rect.w
    #define HERO_H_HALF obj_texture->main_rect.y + obj_texture->main_rect.h / 2

    laserStart->x = HERO_W + PLAINLASER_OFFSET;
    laserStart->y = HERO_H_HALF;

    #undef HERO_W
    #undef HERO_H_HALF
}



void Hero::initHeroStopIntro()
{
    heroStopIntro = new plot;
    #define HERO_WIDTH obj_texture->main_rect.w
    heroStopIntro->x = BORDER_THICKNESS + (4 * HERO_WIDTH);
    heroStopIntro->y = obj_texture->main_rect.y;
    #undef HERO_WIDTH
}

void Hero::setToStartPosition()
{
    Object::setUpLeftCorner(-BORDER_THICKNESS-obj_texture->main_rect.w,
                            S_H / 2 - obj_texture->main_rect.h / 2);
    setCollisionsRects();
}

void Hero::setCollisionsRects()
{
   
    collisionRects[one].x = MAINRECT_UPLEFT_X + 2;
    collisionRects[one].y = MAINRECT_UPLEFT_Y + 4;
    collisionRects[one].w = 45;
    collisionRects[one].h = 17;

    collisionRects[two].x = MAINRECT_UPLEFT_X + 19;
    collisionRects[two].y = collisionRects[one].y + collisionRects[one].h;
    collisionRects[two].w = 68;
    collisionRects[two].h = 16;

    collisionRects[three].x = collisionRects[two].x;
    collisionRects[three].y = collisionRects[two].y + collisionRects[two].h;
    collisionRects[three].w = 117;
    collisionRects[three].h = 36;

    collisionRects[four].x = collisionRects[two].x;
    collisionRects[four].y = collisionRects[three].y + collisionRects[three].h;
    collisionRects[four].w = collisionRects[two].w;
    collisionRects[four].h = 16;

    collisionRects[five].x = collisionRects[one].x;
    collisionRects[five].y = collisionRects[four].y + collisionRects[four].h;
    collisionRects[five].w = collisionRects[one].w;
    collisionRects[five].h = collisionRects[one].h;


}

/*Выход героя на экран*/
void Hero::HeroMovesInIntro(status_t& status)
{
    if ((MAINRECT_UPLEFT_X + obj_texture->main_rect.w) >= heroStopIntro->x) 
    {
        status.heroIntro = false;
        setCollisionsRects();
        return;
    }
    obj_texture->main_rect.x += HERO_VELOCITY_X;
}



Hero::~Hero()
{
    delete[] collisionRects;
    collisionRects = nullptr;
    delete heroStopIntro;
    heroStopIntro = nullptr;
    delete laserStart;
    laserStart = nullptr;
}

#ifdef SHOW_COL_R
    void Hero::showColR(Sdl* sdl)
    {
        Object::showCollisionRects(sdl, collisionRects, one, allRects);
    }
#endif




#undef MAINRECT_UPLEFT_X
#undef MAINRECT_UPLEFT_Y

