#include "n_ob.h"


ObjectsStore::ObjectsStore(const tc* collection)
{
    heroLazers = new (std::nothrow) HeroLazersList(collection);
}

ObjectsStore::~ObjectsStore()
{
    delete heroLazers;
    heroLazers = nullptr;
}

void ObjectsStore::MakeHeroLazer(const plot* start)
{
    heroLazers->Push(start);
}

void ObjectsStore::ShowHeroLazers(const Sdl* sdl)
{
    heroLazers->Show(sdl);
}

void ObjectsStore::MoveHeroLazers()
{
    heroLazers->Move();
}

