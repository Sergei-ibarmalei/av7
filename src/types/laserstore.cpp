#include "ob.h"


LaserStore::LaserStore(const texture_* heroLaser)
{
    heroLasertexture = new texture_;
    heroLasertexture->texture = heroLaser->texture;
    heroLasertexture->main_rect.x = heroLasertexture->main_rect.y = 0;
    heroLasertexture->main_rect.w = heroLaser->main_rect.w;
    heroLasertexture->main_rect.h = heroLaser->main_rect.h;

    heroLasersNodes = new setLaserNodes;
    heroLasersNodes->first  = nullptr;
    heroLasersNodes->last   = nullptr;
    heroLasersNodes->curent = nullptr;
    heroLasersNodes->tmp    = nullptr;
    

}

LaserStore::~LaserStore()
{
    heroLasertexture->texture = nullptr;
    delete heroLasertexture;
    heroLasertexture = nullptr;
    if (heroLasersNodes->first) clearList(heroLasersNodes->first);
    delete heroLasersNodes;
    heroLasersNodes = nullptr;

}

void LaserStore::MakeHeroLaser(plot* start, dir::direction d)
{
    heroLasersNodes->tmp = new laserNode(start, d, heroLasertexture);
    heroLasersNodes->tmp->prev = nullptr;
    heroLasersNodes->tmp->next = heroLasersNodes->first;
    if (heroLasersNodes->first)
        heroLasersNodes->first->prev = heroLasersNodes->tmp;
    else    
        heroLasersNodes->last = heroLasersNodes->tmp;
    heroLasersNodes->first = heroLasersNodes->tmp;
}

void LaserStore::clearList(laserNode* first)
{
    if (!first) return;
    laserNode* tmp = first;
    if (!first->next)
    {
        delete tmp;
        return;
    }
    first = first->next;
    first->prev = nullptr;
    delete tmp;
    clearList(first);
}

void LaserStore::ShowLaserStore(Sdl* sdl)
{
    showLaser(heroLasersNodes->first, sdl);
}

void LaserStore::showLaser(laserNode* first, Sdl* sdl)
{
    if (!first) return;
    first->laser->ShowObj(sdl);
    showLaser(first->next, sdl);

}

void LaserStore::MoveLaserStore()
{
    if (!heroLasersNodes->first) return;
    moveLaser(heroLasersNodes->first);
}

void LaserStore::deletingShot(laserNode* current)
{
    std::cout << "In deleting---\n";
    if (current->prev)
        current->prev->next = current->next;
    else
        heroLasersNodes->first= current->next;
    if (current->next)
        current->next->prev = current->prev;
    else heroLasersNodes->last = current->prev;
    heroLasersNodes->tmp = current;
    current = current->next;

    std::cout << "deleted.\n";
    delete heroLasersNodes->tmp;
    heroLasersNodes->tmp = nullptr;
}

void LaserStore::moveLaser(laserNode* first)
{
    if (!first) return;
    first->laser->Move();
    if (!first->laser->OnScreen()) deletingShot(first);
    moveLaser(first->next);
}

