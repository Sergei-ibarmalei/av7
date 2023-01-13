#include "ob.h"
#include <iterator>


Std_LaserStore::Std_LaserStore(texture_* t)
{
    textureHeroLaser = t;
}

Std_LaserStore::~Std_LaserStore()
{
    for (auto& p: herolasers)
    {
        delete p;
    }
    textureHeroLaser = nullptr;
}


void Std_LaserStore::MakeHeroLaser(plot* start, dir::direction d)
{
    /*Проверяем не слишком ли близко предыдущий выстрел*/
    if (!herolasers.empty())
    {
        std::list<Laser*>::iterator it = herolasers.begin();
        /*Если ближе чем 3 лазера, то не стреляем*/
        if ( ((*it)->GetLaser_x() - start->x) < 3 *(*it)->GetLaser_w())
            return;
    }
    herolasers.push_front(new Laser(start, d, textureHeroLaser));
}

void Std_LaserStore::ShowLaserStore(Sdl* sdl)
{

    for (std::list<Laser*>::iterator it = herolasers.begin(); 
            it != herolasers.end(); ++it)
    {
        (*it)->ShowObj(sdl);
        #ifdef SHOW_COL_R
            (*it)->ShowColR(sdl);
        #endif
    }
}

/*Движение всех выстреляных лазеров*/
void Std_LaserStore::MoveLaserStore()
{
    for (std::list<Laser*>::iterator it = herolasers.begin(); 
            it != herolasers.end(); ++it)
    {
        (*it)->Move();
        if ((*it)->OnScreen() == false)
        {
            delete (*it);
            it = herolasers.erase(it);
        }
    }
}

/*Очистка LaserStore*/
void Std_LaserStore::ClearLaserStore()
{
    if (!herolasers.empty())
    {
        for (std::list<Laser*>::iterator it = herolasers.begin(); 
                it != herolasers.end(); ++it)
        {
            delete (*it);
            it = herolasers.erase(it);
        }
    }
}

