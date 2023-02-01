#include "complexobject.h"

ComplexObject::~ComplexObject()
{

    //В этом конструкторе не удаляем lazerStart, поскольку
    //lazerStart может быть массивом для нескольких точек
    //Удаляем в конкретном классе
    
}



/// @brief Абстрактный класс
/// @param t текстура
/// @param arrLen длинна массива прям. пересечений
ComplexObject::ComplexObject(const texture_* t, const int arrLen): 
                                                    ElementaryObject(t)
{
    //std::cout << "In ComplexObject ctor.\n";
    if (arrLen <= 0)
    {
        init = false; return;
    }
    collisionArrLen = arrLen;
    cr = new (std::nothrow) CRC(collisionArrLen);
    if (cr->Status() == false)
    {
        init = false; return;
    }
}


void ComplexObject::Show(const Sdl* sdl) const
{
    if (isGone == true) return;
    ElementaryObject::ShowObj(sdl);
    #ifdef SHOW_COL_R
        SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF, 0, 0, 0xFF);
        for (int r = 0; r < collisionArrLen; ++r)
        {
            SDL_RenderDrawRect(sdl->Renderer(), &cr->Array()[r]);
        }
        SDL_SetRenderDrawColor(sdl->Renderer(), 0, 0, 0, 0xFF);
    #endif
}

bool ComplexObject::operator==(const rect_& r)
{
    return *cr == r;
}




