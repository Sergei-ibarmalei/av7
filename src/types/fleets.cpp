#include "n_ob.h"
#include "../core/rand.h"

bool ObjectsStore::makeAlienFleetOne(const tc* collection)
{
    #define RIGHT_SIDE RIGHT_BORDER_X+RIGHT_BORDER_W
    #define SHIP_MAINRECT_H collection->Pictures()[tn::alien_one].main_rect.h
    #define UP (UP_BORDER_Y+UP_BORDER_H)+SHIP_MAINRECT_H
    #define DOWN DOWN_BORDER_Y-SHIP_MAINRECT_H
    #define ALIEN_TEXTURE &collection->Pictures()[tn::alien_one]
    #define ALIEN_LASER_TEXTURE &collection->Pictures()[tn::alien_laser01]

    plot alien_start;
    for (int count = 0; count < ALIENFLEET_ONE_CAP; ++count)
    {
        alien_start.x = RIGHT_SIDE +
            (count * ALIENFLEET_ONE_SPACE_BETWEEN);
        alien_start.y = getRand(UP, DOWN);
        if (!alienFleetOneStorage->
            Push(new PlainAlien_t1{ALIEN_TEXTURE, &alien_start, 
                                   ALIEN_LASER_TEXTURE})) return false;
    }
    return true;

    #undef ALIEN_TEXTURE
    #undef ALIEN_LASER_TEXTURE
    #undef RIGHT_SIDE
    #undef SHIP_MAINRECT_H
    #undef DOWN
}

/* AlienFleet_oneStorage::AlienFleet_oneStorage(const int capacity): 
                                                ArrStorageABC(capacity)
{
    if (init == false) return;
    //storage = new ElementaryObject*[capacity] {nullptr};
}

PlainAlien_t1* AlienFleet_oneStorage::operator[](const int index)
{
    if (index < 0 || index >= counter) return nullptr;
    return static_cast<PlainAlien_t1*>(storage[index]);
}

bool AlienFleet_oneStorage::Push(ElementaryObject* ob)
{
    if (counter >= storageCapacity) return false;
    storage[counter++] = static_cast<PlainAlien_t1*>(ob);
    return true;
} */


/*bool Alien_t1_fleetList::Push(ElementaryObject* ob)
{
    if (!push(ob)) return false;
    return true;
}

void Alien_t1_fleetList::Show(const Sdl* sdl)
{
    showAlien(sdl, Alien_t1_fleetList::first);
}

void Alien_t1_fleetList::showAlien(const Sdl* sdl, obNode* first)
{
    if (!first) return;
    if (toPlainAlien_t1(first->object)->OnScreen() == false)
        showAlien(sdl, first->next);
    toPlainAlien_t1(first->object)->Show(sdl);
    showAlien(sdl, first->next);
}*/

/*void Alien_t1_fleetList::moveNode(obNode* first)
{
    while (first)
    {
        toPlainAlien_t1(first->object)->Move();
        if ( first->IsAlive == false || toPlainAlien_t1(first->object)->Gone() == true)
        {
            if (first == root)
            {
                delete E_listABC::first;
                E_listABC::root = E_listABC::first = nullptr;
                return;
            }
            first = deleteItem(first, root);
            continue;
        }
        first = first->next;
    }
}

void Alien_t1_fleetList::Move()
{
    if (first) moveNode(first);
}*/



/*Fleets::Fleets(const tc* collection)
{
    //std::cout << "In Fleets ctor.\n";
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
    //std::cout << "In Fleets dtor.\n";
    delete alien_t1_fleet;
    alien_t1_fleet = nullptr;
}*/

/*bool Fleets::makeAlien_t1_fleet(const tc* collection)
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
        if (!(alien_t1_fleet->
            Push(new PlainAlien_t1{&collection->Pictures()[tn::alien_one],
            &alien_start, &collection->Pictures()[tn::alien_laser01]}))) 
            return false;
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


void Fleets::Alien_t1_Show(const Sdl* sdl)
{
    alien_t1_fleet->Show(sdl);
}


void Fleets::FleetMove()
{
    alien_t1_fleet->Move();
}*/

