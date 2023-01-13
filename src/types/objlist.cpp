#include "ob.h"


/* ObjList::ObjList(tc* collection)
{
    tcollection = collection;
}

ObjList::~ObjList()
{
    if (!objList.empty())
    {
        for (auto& p: objList)
        {
            delete p;
        }
    }
    tcollection = nullptr;
}

void ObjList::pushPlainLaser(plot* start, dir::direction d)
{
    
    objList.push_front(new Laser(start, d, &tcollection->Pictures()[tn::blue_laser]));
}

void ObjList::show(Sdl* sdl)
{
    if (!objList.empty())
    {
        for (auto& o: objList)
        {
            o->ShowObj(sdl);
        }
    }
}

void ObjList::plainMove()
{
    for (auto& o: objList)
    {
        o->Move();
    }
}


Store::Store(tc* collection)
{
    heroLaserStore = new ObjList(collection);
}

Store::~Store()
{
    delete heroLaserStore;
}

void Store::MakeHeroLaser(plot* start)
{
    #define PREVLASER_X static_cast<Laser*>(*heroLaserStore->getList()\
            .begin())->GetLaser_x()
    #define PREVLASER_W static_cast<Laser*>(*heroLaserStore->getList()\
            .begin())->GetLaser_w()
    
    if (!heroLaserStore->getList().empty())
    {
        if (PREVLASER_X < PREVLASER_W * 3) return;
    }
    heroLaserStore->pushPlainLaser(start, dir::right);

    #undef PREVLASER_X 
    #undef PREVLASER_W
}

void Store::ShowHeroLasers(Sdl* sdl)
{
    heroLaserStore->show(sdl);
}

void Store::MoveHeroLasers()
{
    heroLaserStore->plainMove();
}
 */



/*----------------------------------------------------------------------*/
/*=======================================================*/
ObjectList::~ObjectList()
{
    tcollection = nullptr;
    if (!objectList.empty())
    {
        for (auto& o: objectList)
        {
            delete o;
        }
    }
}


HeroLasers::HeroLasers(tc* collection): ObjectList(collection) {}

void HeroLasers::Push(plot* start)
{
    /*Сперва проверяем на близость к прошлому выстрелу*/
    #define PREVLASER_X static_cast<Laser*>(*ObjectList::\
                getObjectList().begin())->GetLaser_x() 
    #define PREVLASER_W static_cast<Laser*>(*ObjectList::\
                getObjectList().begin())->GetLaser_w()

    if (!ObjectList::objectList.empty())
    {
        if (PREVLASER_X < PREVLASER_W * 3) return;
    }

    ObjectList::getObjectList().push_front(new Laser(start, dir::right,
                        &ObjectList::tcollection->Pictures()[tn::blue_laser]));

    #undef PREVLASER_X
    #undef PREVLASER_W
}

void HeroLasers::Show(Sdl* sdl)
{
    for (auto& herolaser: ObjectList::objectList)
    {
        herolaser->ShowObj(sdl);
        #ifdef SHOW_COL_R
            static_cast<Laser*>(herolaser)->ShowColR(sdl);
        #endif 
    }
}

void HeroLasers::MoveLasers()
{
    for(auto& herolaser: ObjectList::objectList)
    {
        static_cast<Laser*>(herolaser)->Move();
    }

    for (std::list<Object*>::iterator i = ObjectList::getObjectList().begin();
            i != ObjectList::getObjectList().end(); ++i)
    {
        static_cast<Laser*>(*i)->Move();
        /*Если вышли за пределы экрана, удаляем выстрел из списка*/
        if (static_cast<Laser*>(*i)->OnScreen() == false)
        {
            delete (*i);
            i = ObjectList::getObjectList().erase(i);
        }
    }
}



GameStore::GameStore(tc* collection)
{
    herolasers = new HeroLasers(collection);
}

GameStore::~GameStore()
{
    delete herolasers;
}

void GameStore::MakeHeroLaser(plot* start)
{
    herolasers->Push(start);
}

void GameStore::ShowAllHeroLasers(Sdl* sdl)
{
    herolasers->Show(sdl);
}

void GameStore::MoveAllHeroLasers()
{
    herolasers->MoveLasers();
}

/*=======================================================*/
/*----------------------------------------------------------------------*/