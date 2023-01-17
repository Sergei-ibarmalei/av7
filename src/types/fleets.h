#ifndef FLEETS_H
#define FLEETS_H

#include "aliens.h"

class Alien_t1_fleetList: public E_listABC
{
    private:
    bool push(ElementaryObject* ob) override;
    void showAlien(const Sdl* sdl, obNode* first);

    public:
    Alien_t1_fleetList(const tc* collection):E_listABC(collection)
    {
        //std::cout << "In Alien_t1_fleetList ctor.\n";
    }
    Alien_t1_fleetList(const Alien_t1_fleetList&) = delete;
    Alien_t1_fleetList& operator=(const Alien_t1_fleetList&) = delete;
    ~Alien_t1_fleetList()
    {
        //std::cout << "In Alien_t1_fleetList dtor.\n";
    }
    void Show(const Sdl* sdl) override;
    obNode* GetFirstForAction() {return Alien_t1_fleetList::first;}
    bool Push(ElementaryObject* ob);
    //void Move() - 
    // не определяем, воспользуемся позже при помощи
    // obNode* GetfirstForAction()

};



class Fleets
{
    protected:
    bool init {true};
    Alien_t1_fleetList* alien_t1_fleet {nullptr};
    bool makeAlien_t1_fleet(const tc* collection);

    public:
    Fleets() {}
    Fleets(const tc* collection);
    ~Fleets();
    Fleets(const Fleets&) = delete;
    Fleets& operator=(const Fleets& ) = delete;
    bool Status() const {return init;}
    obNode* Alien_t1_fleet_first();
    void Alien_t1_Show(const Sdl* sdl);
};




#endif