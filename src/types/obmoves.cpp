#include "ob.h"

#define UP UP_BORDER_Y + BORDER_THICKNESS
#define DOWN DOWN_BORDER_Y
#define RIGHT RIGHT_BORDER_X
#define LEFT LEFT_BORDER_X + LEFT_BORDER_W
#define OBJ_RIGHT obj_texture->main_rect.x + obj_texture->main_rect.w
#define OBJ_LEFT obj_texture->main_rect.x
#define OBJ_UP obj_texture->main_rect.y
#define OBJ_DOWN obj_texture->main_rect.y + obj_texture->main_rect.h

bool Hero::isGonnaCrossRight()
{
    return (OBJ_RIGHT + Object::obj_velocities->x) > RIGHT;
}

bool Hero::isGonnaCrossLeft()
{
    return (OBJ_LEFT + Object::obj_velocities->x) < LEFT;
}

bool Hero::isGonnaCrossUp()
{
    return (OBJ_UP + Object::obj_velocities->y) < UP;
}

bool Hero::isGonnaCrossDown()
{
    return (OBJ_DOWN + Object::obj_velocities->y) > DOWN;
}


void Hero::HeroUp()
{
    Object::obj_velocities->y -= HERO_VELOCITY_Y;
    Hero::Move();
}

void Hero::HeroDown()
{
    Object::obj_velocities->y += HERO_VELOCITY_Y;
    Hero::Move();
}

void Hero::HeroRight()
{
    Object::obj_velocities->x += HERO_VELOCITY_X;
    Hero::Move();
}

void Hero::HeroLeft()
{
    Object::obj_velocities->x -= HERO_VELOCITY_X;
    Hero::Move();
}

void Hero::HeroStop()
{
    Object::obj_velocities->x = Object::obj_velocities->y = 0;
}

void Hero::Move()
{
    if (isGonnaCrossUp()) return;
    if (isGonnaCrossDown()) return;
    if (isGonnaCrossRight()) return;
    if (isGonnaCrossLeft()) return;
    resetUpLeftCorner();
    setCollisionsRects();
    recomputeLaserStart();

}



#undef UP
#undef DOWN
#undef RIGHT
#undef LEFT
#undef OBJ_RIGHT
#undef OBJ_LEFT
#undef OBJ_UP
#undef OBJ_DOWN




