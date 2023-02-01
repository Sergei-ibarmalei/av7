#include "core.h"

bool mainCore()
{
    Sdl sdl("app");
    if (sdl.Status() == false) return false;

    tc collection(sdl.Renderer());
    if (collection.Status() == false) return false;
    GameClass gc(sdl, collection);
    if (gc.Status() == false) return false;
    if (!gc.flow(collection)) return false;


    return true;
}

DieComplex* Make_DieComplex(const plot* ship_center, const tc* collection)
{
    DieComplex* dsc = 
    new (std::nothrow) DieComplex(ship_center, 
                                &collection->Pictures()[tn::scull]);
    if (!dsc || dsc->Status() == false) return nullptr;
    return dsc;
}

DieComplex* Make_DieComplex(const texture_* digits, const plot* ship_center,
                                                const int score)
{

    if (score <= 0) return nullptr;

    int complexLength = score / 10;
    int hi, low;
    if (complexLength < 1) complexLength = 1;
    else complexLength = 2;


    switch (complexLength)
    {
        case 1:
        {

            DieComplex* dsc = 
            new (std::nothrow) DieComplex{ship_center, &digits[score]};
            if (!dsc || (dsc->Status() == false)) return nullptr;
            return dsc;
        }
        case 2:
        {

            hi = score / 10;
            low = score % 10;
            DieComplex* dsc = 
            new (std::nothrow) DieComplex{ship_center, &digits[hi],
                                                &digits[low]};
            if (!dsc || (dsc->Status() == false)) return nullptr;
            return dsc;
        }
        default: { return nullptr;}
    }
}


void borderSky_show_moving(const Sdl* sdl, Border* border, Sky* sky)
{
    border->ShowBorder(sdl);
    sky->ShowSky(sdl);
    sky->MoveSky();
}



