#include "ob.h"

Object::Object(const texture_* t, log_::Log& log)
{
    obj_texture = new (std::nothrow) texture_;
    if (!obj_texture)
    {
        log.log_info = "Cannot allocate memory for abc object.\n";
        log.push(log.log_info);
        init = false; return;
    }
    obj_texture->texture = t->texture;
    obj_texture->rect.w = t->rect.w;
    obj_texture->rect.h = t->rect.h;
    obj_texture->rect.x = 0;
    obj_texture->rect.y = 0;
    ca = new (std::nothrow) Cca();
    if (!ca)
    {
        log.log_info = "Cannot allocate memory for cca.\n";
        log.push(log.log_info);
        init = false;        
    }
}

Object::Object(const Object& o)
{
    obj_texture = new texture_;
    obj_texture->texture = o.obj_texture->texture;
    obj_texture->rect = o.obj_texture->rect;
}

Object& Object::operator=(const Object& o)
{
    if (this == &o) return *this;
    delete obj_texture;
    obj_texture = new texture_;
    obj_texture->texture = o.obj_texture->texture;
    obj_texture->rect = o.obj_texture->rect;
    ca = o.ca;
    return *this;
}



bool Object::operator==(const Object& o)
{
    return obj_texture->rect == o.obj_texture->rect;
}

bool Object::operator==(const Object* po)
{
    //return obj_texture->rect == po->obj_texture->rect;
    if (obj_texture->rect == po->obj_texture->rect)
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
}

void Object::ShowObj(Sdl* sdl)
{
    sdl->TextureRender(obj_texture->texture, &obj_texture->rect);
}

//--------------HERO-------------------------------------


Hero::Hero(const plot& center, const texture_* t, log_::Log& log):
    Object(t, log)
{
    if (!t)
    {
        log.log_info = "Cannot create hero, texture is absent.\n";
        log.push(log.log_info);
        init = false;
        return;
    }
    collisionRects = new rect_[allRects];

    setCollisionsRects(center);
}

void Hero::setCollisionsRects(const plot& center)
{
    
    obj_texture->rect.x = center.x - obj_texture->rect.w / 2;
    obj_texture->rect.y = center.y - obj_texture->rect.h / 2;

    collisionRects[one].x = obj_texture->rect.x + 2;
    collisionRects[one].y = obj_texture->rect.y + 4;
    collisionRects[one].w = 45;
    collisionRects[one].h = 17;

    collisionRects[two].x = obj_texture->rect.x + 19;
    collisionRects[two].y = collisionRects[one].y + collisionRects[one].h;
    collisionRects[two].w = 68;
    collisionRects[two].h = 16;//collisionRects[two].y + 37;

    collisionRects[three].x = collisionRects[two].x;
    collisionRects[three].y = collisionRects[two].y + collisionRects[two].h;
    collisionRects[three].w = 117;
    collisionRects[three].h = 36;//collisionRects[three].y + 74;

    collisionRects[four].x = collisionRects[two].x;
    collisionRects[four].y = collisionRects[three].y + collisionRects[three].h;
    collisionRects[four].w = collisionRects[two].w;
    collisionRects[four].h = 16;//collisionRects[four].y + 89;

    collisionRects[five].x = collisionRects[one].x;
    collisionRects[five].y = collisionRects[four].y + collisionRects[four].h;
    collisionRects[five].w = collisionRects[one].w;
    collisionRects[five].h = collisionRects[one].h;

}

#ifdef SHOW_COL_R
    void Hero::showColR(Sdl* sdl)
    {
        SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF,  0, 0, 0xFF);
        for (int r = one; r < allRects; ++r)
        {
            SDL_RenderDrawRect(sdl->Renderer(), &collisionRects[r]);
        }
        SDL_SetRenderDrawColor(sdl->Renderer(), 0, 0, 0, 0);
    }
#endif

Hero::~Hero()
{
    delete[] collisionRects;
    collisionRects = nullptr;
}



