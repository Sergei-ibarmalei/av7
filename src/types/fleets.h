#ifndef FLEETS_H
#define FLEETS_H

#include "aliens.h"


/* class AlienFleet_oneStorage: public ArrStorageABC
{
    protected:
    public:
    explicit AlienFleet_oneStorage(const int capacity);
    ~AlienFleet_oneStorage() {}
    AlienFleet_oneStorage(const AlienFleet_oneStorage&) = delete;
    AlienFleet_oneStorage& operator=(const AlienFleet_oneStorage&) = delete;
    PlainAlien_t1* operator[](const int index);
    bool Push(ElementaryObject* ob) override;

}; */

/*class Alien_t1_fleetList: public E_listABC
{
    private:
    void showAlien(const Sdl* sdl, obNode* first);
    void moveNode(obNode* first) override;

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
    bool Push(ElementaryObject* ob);
    obNode* GetFirstForAction() {return Alien_t1_fleetList::first;}
    void Move() override;

};*/



/*class Fleets
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
    void FleetMove();
};*/




#endif