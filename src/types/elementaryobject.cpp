#include "n_ob.h"


ElementaryObject::~ElementaryObject()
{
    //std::cout << "In ElementaryObject dtor.\n";

    obj_texture->texture = nullptr;
    delete obj_texture;
    obj_texture = nullptr;
    delete obj_velocities;
    obj_velocities = nullptr;
}


ElementaryObject::ElementaryObject(const texture_* t)
{
    //std::cout << "In ElementaryObject ctor.\n";
    if (!t)
    {
        init = false;
        return;
    }
    obj_texture = new (std::nothrow) texture_;
    if (!obj_texture)
    {
        init = false; return;
    }
    obj_center = new (std::nothrow) plot;
    if (!obj_center)
    {
        init = false; return;
    }
    obj_texture->texture = t->texture;
    obj_texture->main_rect.w = t->main_rect.w;
    obj_texture->main_rect.h = t->main_rect.h;
    obj_texture->main_rect.x = obj_texture->main_rect.y = 0;

    obj_center->x = obj_texture->main_rect.w / 2;
    obj_center->y = obj_texture->main_rect.h / 2;
    obj_velocities = new plot{0, 0};
    if (!obj_velocities) init = false;

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
    delete obj_center;
    delete obj_velocities;
    obj_texture = new (std::nothrow) texture_;
    obj_texture->texture = eo.obj_texture->texture;
    obj_texture->main_rect = eo.obj_texture->main_rect;
    obj_center = new (std::nothrow) plot;
    obj_center = eo.obj_center;
    obj_velocities = eo.obj_velocities;
    return *this;
}



void ElementaryObject::ShowObj(const Sdl* sdl) const
{
    sdl->TextureRender(obj_texture->texture, &obj_texture->main_rect);
    #ifdef SHOW_COL_R
        SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF, 0, 0, 0xFF);
        SDL_RenderDrawRect(sdl->Renderer(), &obj_texture->main_rect);
        SDL_SetRenderDrawColor(sdl->Renderer(), 0, 0, 0, 0);
    #endif
}

void ElementaryObject::resetCenter()
{
    obj_center->x = obj_texture->main_rect.x + obj_texture->main_rect.w / 2;
    obj_center->y = obj_texture->main_rect.y + obj_texture->main_rect.h / 2;
}

void ElementaryObject::resetUpLeftCorner()
{
    obj_texture->main_rect.x += obj_velocities->x;
    obj_texture->main_rect.y += obj_velocities->y;
    resetCenter();
}

void ElementaryObject::setUpLeftCorner(const int x, const int y)
{
    obj_texture->main_rect.x = x;
    obj_texture->main_rect.y = y;
    resetCenter();

}

void ElementaryObject::resetUpLeftCorner_x(const int x)
{
    obj_texture->main_rect.x += x;
    resetCenter();
}

void ElementaryObject::resetUpLeftCorner_y(const int y)
{
    obj_texture->main_rect.y += y;
    resetCenter();
}




