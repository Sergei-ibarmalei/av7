#include "fleets.h"
#include "../core/rand.h"


//в конец списка
bool Alien_t1_fleetList::push(ElementaryObject* ob)
{
    obNode* tmp = new (std::nothrow) obNode;
    if (!tmp) return false;
    tmp->object = ob;
    tmp->next = nullptr;
    if (E_listABC::last)
    {
        E_listABC::last->next = tmp;
        E_listABC::last = E_listABC::last->next;
    }
    else
    {
        E_listABC::first = E_listABC::last;
    }
    return true;
}

bool Alien_t1_fleetList::Push(ElementaryObject* ob)
{
    if (!push(ob)) return false;
    return true;
}

void Alien_t1_fleetList::Show(const Sdl* sdl)
{
    showAlien(sdl, first);
}

void Alien_t1_fleetList::showAlien(const Sdl* sdl, obNode* first)
{
    if (!first) return;
    static_cast<PlainAlien_t1*>(first->object)->Show(sdl);
    showAlien(sdl, first->next);
}



Fleets::Fleets(const tc* collection)
{
    if (!collection)
    {
        init = false; return;
    }
    alien_t1_fleet = new (std::nothrow) Alien_t1_fleetList{collection};
    if (!alien_t1_fleet)
    {
        init = false; return;
    }
    if (!(makeAlien_t1_fleet(collection))) 
    {
        init = false; return;
    }

}

Fleets::~Fleets()
{
    delete alien_t1_fleet;
    alien_t1_fleet = nullptr;
}

bool Fleets::makeAlien_t1_fleet(const tc* collection)
{
     //Высота одного алиена
    #define SHIP_MAINRECT_H collection->Pictures()[tn::alien_one].main_rect.h
    //Координата по х правого края экрана
    #define RIGHT_SIDE RIGHT_BORDER_X+RIGHT_BORDER_W
    //Верхняя крайняя координата появления алиена по у
    #define UP (UP_BORDER_Y+UP_BORDER_H)+SHIP_MAINRECT_H
    //Нижняя крайняя координата появление алиена по у
    #define DOWN DOWN_BORDER_Y-SHIP_MAINRECT_H

    plot alien_start;
    for (int count = 0; count < ALIENFLEET_1_SIZE; ++count)
    {
        alien_start.x = RIGHT_SIDE + 
            (count * ALIENFLEET_1_SPACE_BETWEEN);
        alien_start.y = getRand(UP, DOWN);
        if (!(alien_t1_fleet->Push(new PlainAlien_t1{&collection->Pictures()[tn::alien_one],
            &alien_start, &collection->Pictures()[tn::alien_laser01]}))) return false;
    }

    #undef SHIP_MAINRECT_H
    #undef RIGHT_SIDE
    #undef UP
    #undef DOWN  
    return true; 


}

obNode* Fleets::Alien_t1_fleet_first()
{
    return alien_t1_fleet->GetFirstForAction();
}



