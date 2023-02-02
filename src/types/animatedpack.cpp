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

void Apack::Show(const Sdl* sdl, const tn::flow f, bool stop)
{
    switch (f)
    {
        case tn::flow::repeated:
        {
            if (frame == packCapacity-1) frame = 0;
            sdl->TextureRender(tpack[frame].texture,
                                    &tpack[frame].main_rect);
            if (!stop) frame += 1;
            //frame += 1;
            break;
        }
        case tn::flow::once:
        {
            if (frame == packCapacity-1) return;
            sdl->TextureRender(tpack[frame].texture, 
                                                &tpack[frame].main_rect);
            if (!stop) frame += 1;
            //frame += 1;
            break;
        }
        default: {}
    }
}



