#include "n_ob.h"


ObjectsStore::ObjectsStore(const tc* collection)
{
    //std::cout << "In ObjectsStore ctor.\n";
    heroLazers = new (std::nothrow) HeroLazersList(collection);
}

ObjectsStore::~ObjectsStore()
{
    //std::cout << "In ObjectsStore dtor.\n";
    delete heroLazers;
    heroLazers = nullptr;
}

void ObjectsStore::MakeHeroLazer(const plot* start)
{
    //heroLazers->Push(start);
    if (!heroLazers->Push(start)) return;
}

void ObjectsStore::ShowHeroLazers(const Sdl* sdl)
{
    heroLazers->Show(sdl);
}

void ObjectsStore::MoveHeroLazers()
{
    heroLazers->Move();
}

