#include "animatedpack.h"

Apack::Apack(texture_* animPack, const int animPackCap, plot* center)
{
    if (!animPack || animPackCap <= 0)
    {
        init = false; return;
    }
    tpack = animPack;
    packCapacity = animPackCap;
    frame = 0;
    setCoords(center);
}

Apack::~Apack()
{
    tpack = nullptr;
}

void Apack::setCoords(plot* center)
{
    if (!center) return;
    for (int a = 0; a < packCapacity; ++a)
    {
        tpack[a].main_rect.x = center->x - tpack[a].main_rect.w/2;
        tpack[a].main_rect.y = center->y - tpack[a].main_rect.h/2;
    }

}

void Apack::Show(const Sdl* sdl, const tn::flow f)
{
    switch (f)
    {
        case tn::flow::repeated:
        {
            if (frame == packCapacity-1) frame = 0;
            sdl->TextureRender(tpack[frame].texture,
                                    &tpack[frame].main_rect);
            frame += 1;
            break;
        }
        case tn::flow::once:
        {
            if (frame == packCapacity-1) return;
            sdl->TextureRender(tpack[frame].texture, 
                                                &tpack[frame].main_rect);
            frame += 1;
            break;
        }
        default: {}
    }
}

/*ApackList::ApackList()
{
    first = nullptr;
}

ApackList::~ApackList()
{
    while (first)
    {
        struct Node* tmp = first;
        first = first->next;
        delete tmp;
        tmp = nullptr;
    }
}

void ApackList::Push(Apack* data)
{
    if (!data) return;
    struct Node* tmp = new (std::nothrow) Node;
    if (!tmp) return;
    tmp->data = data;
    if (!first)
    {
        tmp->next = nullptr;
        first = tmp;
        return;
    }
    tmp->next = first;
    first = tmp;
}

void ApackList::Show(const Sdl* sdl, const tn::flow f)
{
    if (!first) return;
    struct Node* tmp = first;
    while (tmp)
    {
        tmp->data->ShowApack(sdl, f);
        tmp = tmp->next;
    }
}

void ApackList::Check_and_clear()
{
    current = &first;
    while (*current)
    {
        if ( (*current)->data->ShowIsGone())
        {
            struct Node* tmp = *current;
            *current = (*current)->next;
            delete tmp;
        }
        else current = &(*current)->next;
    }
}*/






