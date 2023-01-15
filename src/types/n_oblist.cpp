#include "n_ob.h"

ObjectList::ObjectList(const tc* collection)
{
    if (!collection)
    {
        init = false; return;
    }
    tcolleciton = collection;
}

ObjectList::~ObjectList()
{
    tcolleciton = nullptr;
    if (!objectList.empty())
    {
        for (auto& o: objectList)
        {
            delete o;
        }
    }
}


HeroLazers::HeroLazers(const tc* collection): ObjectList(collection)
{
    if (ObjectList::Status() == false) return;

}

void HeroLazers::Push(const plot* start)
{
    #define PREVLAZER_X static_cast<LongLazer*>(*ObjectList::\
                                    getObjectList().begin())->GetLazer_x()
    #define LAZER_W static_cast<LongLazer*>(*ObjectList::\
                                    getObjectList().begin())->GetLazer_w()

    if (ObjectList::getObjectList().empty() == false)
    {
        if (PREVLAZER_X - start->x < LAZER_W * 3) return;
    }
    ObjectList::getObjectList().push_front(new LongLazer(start, dir::right,
                        &ObjectList::tcolleciton->Pictures()[tn::blue_laser]));


    #undef PREVLAZER_X
    #undef PREVLAZER_W

}

void HeroLazers::Show(const Sdl* sdl)
{
    for (auto& herolazer: ObjectList::getObjectList())
    {
        static_cast<LongLazer*>(herolazer)->Show(sdl);
        #ifdef SHOW_COL_R
            static_cast<LongLazer*>(herolazer)->ShowColR(sdl);
        #endif
    }
}

void HeroLazers::Move()
{
    for (std::list<ElementaryObject*>::iterator i = ObjectList::getObjectList().begin();
         i != ObjectList::getObjectList().end(); ++i)
    {
        static_cast<LongLazer*>(*i)->Move();
        /*Если вышли за ганицу экрана, удаляем выстрел*/
        if (static_cast<LongLazer*>(*i)->OnScreen() == false)
        {
            delete (*i);
            i = ObjectList::getObjectList().erase(i);
        }
    }
}

ObjectsStore::ObjectsStore(const tc* collection)
{
    heroLazers = new (std::nothrow) HeroLazers(collection);
    if (!heroLazers || heroLazers->Status() == false)
    {
        init = false; return;
    }


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

