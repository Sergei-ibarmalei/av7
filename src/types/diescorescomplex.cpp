#include "n_ob.h"

DieScoresComplex::DieScoresComplex(const plot* ship_center, const texture_* f,       
                                    const texture_* s)
{
    if ( (!f && !s) || !f)
    {
        init = false; return;
    }
    if (f && s)
    {
        arrLen = maxTexture;
        complex = new (std::nothrow) DieScoresObject* [maxTexture] {nullptr};
        complex[firstTexture] = new (std::nothrow) DieScoresObject(f);
        if (!complex[firstTexture])
        {
            init = false; return;
        }
        complex[firstTexture]->GetMainRect()->x = 
            ship_center->x - complex[firstTexture]->GetMainRect()->w;
        complex[firstTexture]->GetMainRect()->y =
            ship_center->y - complex[firstTexture]->GetMainRect()->h / 2;
        complex[secondTexture] = new (std::nothrow) DieScoresObject(s);
        if (!complex[secondTexture])
        {
            init = false; return;
        }
        complex[secondTexture]->GetMainRect()->x = ship_center->x;
        complex[secondTexture]->GetMainRect()->y = 
            complex[firstTexture]->GetMainRect()->y;
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
        complex[firstTexture]->GetMainRect()->x =
            ship_center->x - complex[firstTexture]->GetMainRect()->w / 2;
        complex[firstTexture]->GetMainRect()->y = 
            ship_center->y - complex[firstTexture]->GetMainRect()->h / 2;
    }
}

DieScoresComplex::~DieScoresComplex()
{
    for (int t = firstTexture; t < arrLen; ++t)
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

