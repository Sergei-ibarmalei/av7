#include "n_ob.h"

DieScoresComplex::DieScoresComplex(const plot* ship_center, const texture_* f,       
                                    const texture_* s)
{
    #define TEXTURES_ARE_ABSENT !f && !s
    #define TEXTURES_HERE f && s
    #define FIRSTTEXTURE_ABSENT !f

    #define FIRSTTEXTURE_X complex[firstTexture]->GetMainRect()->x
    #define FIRSTTEXTURE_W complex[firstTexture]->GetMainRect()->w
    #define FIRSTTEXTURE_Y complex[firstTexture]->GetMainRect()->y
    #define FIRSTTEXTURE_HALF_HEIGHT complex[firstTexture]->GetMainRect()->h/2
    #define FIRSTTEXTURE_HALF_WIDTH complex[firstTexture]->GetMainRect()->w/2
    #define SECONDTEXTURE_X complex[secondTexture]->GetMainRect()->x
    #define SECONDTEXTURE_Y complex[secondTexture]->GetMainRect()->y

    if ( (TEXTURES_ARE_ABSENT) || FIRSTTEXTURE_ABSENT)
    {
        init = false; return;
    }
    if (TEXTURES_HERE)
    {
        arrLen = maxTexture;
        complex = new (std::nothrow) DieScoresObject* [maxTexture] {nullptr};
        complex[firstTexture] = new (std::nothrow) DieScoresObject(f);
        if (!complex[firstTexture])
        {
            init = false; return;
        }
        FIRSTTEXTURE_X = ship_center->x - FIRSTTEXTURE_W;
        FIRSTTEXTURE_Y = ship_center->y - FIRSTTEXTURE_HALF_HEIGHT;
        complex[secondTexture] = new (std::nothrow) DieScoresObject(s);
        if (!complex[secondTexture])
        {
            init = false; return;
        }
        SECONDTEXTURE_X = ship_center->x;
        SECONDTEXTURE_Y = FIRSTTEXTURE_Y;
    }
    else
    {
        arrLen = 1;
        complex = new (std::nothrow) DieScoresObject* [1] {nullptr};
        complex[firstTexture] = new (std::nothrow) DieScoresObject(f);
        if (!complex[firstTexture])
        {
            init = false; return;
        }
        FIRSTTEXTURE_X = ship_center->x - FIRSTTEXTURE_HALF_WIDTH;
        FIRSTTEXTURE_Y = ship_center->y - FIRSTTEXTURE_HALF_HEIGHT;
    }

    #undef SECONDTEXTURE_Y
    #undef SECONDTEXTURE_X
    #undef FIRSTTEXTURE_HALF_HEIGHT
    #undef FIRSTTEXTURE_HALF_WIDTH
    #undef FIRSTTEXTURE_Y
    #undef FIRSTTEXTURE_X
    #undef FIRSTTEXTURE_W
    #undef TEXTURES_ARE_ABSENT
    #undef TEXTURES_HERE
    #undef FIRSTTEXTURE_ABSENT
}

DieScoresComplex::~DieScoresComplex()
{
    for (int t = firstTexture; t < arrLen;++t)
    {
        delete complex[t];
        complex[t] = nullptr;
    }
    delete complex;
    complex = nullptr;

}

void DieScoresComplex::Move()
{
    if (arrLen == maxTexture)
    {
        for (int t = firstTexture; t < maxTexture; ++t)
        {
            complex[t]->Move();
        }
        return;
    }
    complex[firstTexture]->Move();
}

void DieScoresComplex::Show(const Sdl* sdl) const
{
    if (arrLen == maxTexture)
    {
        for (int t = firstTexture; t < maxTexture; ++t)
        {
            complex[t]->Show(sdl);
        }
        return;
    }
    complex[firstTexture]->Show(sdl);

}

