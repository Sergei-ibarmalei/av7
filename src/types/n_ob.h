#ifndef N_OB_H
#define N_OB_H

#include "sdlclass.h"
#include "gametypes.h"
#include "../loging/loging.h"
#include "../consts/gameconsts.h"
#include "test.h"
#include "texturescollection.h"

/*Абстрактный класс - основа всех объектов*/
class ElementaryObject
{
    protected:
    bool init {true};
    bool isOnScreen {false};
    bool isGone {false};
    texture_*  obj_texture    {nullptr};
    plot*      obj_velocities {nullptr};
    void setUpLeftCorner(const int x, const int y);
    void resetUpLeftCorner();
    void resetUpLeftCorner_x(const int x);
    void resetUpLeftCorner_y(const int y);
    void ShowObj(const Sdl* sdl) const;


    public:
    ElementaryObject(const texture_* t);
    ElementaryObject(const ElementaryObject& eo);
    ElementaryObject& operator=(const ElementaryObject& eo);
    //bool operator==(const ElementaryObject& eo);
    virtual ~ElementaryObject();
    bool Status() const {return init;}
    virtual void Move() = 0;

    rect_& MainRect() const {return obj_texture->main_rect;}
    rect_* GetMainRect() const {return &obj_texture->main_rect;}

    bool OnScreen() const {return isOnScreen;}
    void ResetOnScreen(bool visibility) {isOnScreen = visibility;}
    int  GetMainRect_x() const {return obj_texture->main_rect.x;}
    int  GetMainRect_y() const {return obj_texture->main_rect.y;}
    int  GetMainRect_w() const {return obj_texture->main_rect.w;}
    int  GetMainRect_h() const {return obj_texture->main_rect.h;}
    int  GetMainRectW() const {return obj_texture->main_rect.x+
                                obj_texture->main_rect.w;}
    int GetMainRectH()  const {return obj_texture->main_rect.y+
                                obj_texture->main_rect.h;}
    int GetMainRectH_Half() const {return obj_texture->main_rect.y+
                                obj_texture->main_rect.h / 2;}
    plot* Velocities() {return obj_velocities;}
    bool IsItGone() {return isGone;} 
    void ItIsGoneNow() {isGone = true;}
};

/*Сложный класс для объектов с прямоугольниками пересечений*/
class ComplexObject: public ElementaryObject
{
    protected:
    CRC* cr;
    plot* lazerStart {nullptr};
    int collisionArrLen;
    virtual void setToStartPos(const int x, const int y) = 0;
    virtual void setCr() = 0;
    virtual void initLazerStart() = 0;
    virtual void recomputeLazerStart() = 0;

    public:
    ComplexObject(const texture_* t, const int arrLen);
    ComplexObject& operator=(const ComplexObject& ) = delete;
    ~ComplexObject();
    ComplexObject(const ComplexObject& co) = delete;
    plot* GetLazerStart() const {return lazerStart;}
    virtual void Move() = 0;

    void Show(const Sdl* sdl) const;

};

/*Пересечения*/
namespace re
{
    /*прям. пересечений героя*/
    enum  heros {one, two, three, four, five, allR};

    /*алиен тип первый*/
    enum  alien_t1 {t1_one, t1_two, t1_three, t1_allR};
}

namespace scores
{
    enum weight {plainAlien = 5,};
}

class NHero: public ComplexObject
{
    private:
    plot*   heroStopIntro {nullptr};
    void    initHeroStopIntro();
    void    initLazerStart();
    void    recomputeLazerStart();
    void    setToStartPos(const int x, const int y); 
    void    setCr() override;

    bool    isGonnaCrossUp();
    bool    isGonnaCrossDown();
    bool    isGonnaCrossRight();
    bool    isGonnaCrossLeft();

    public:
    NHero(const texture_* t);
    ~NHero();
    NHero(const NHero& ) = delete;
    NHero& operator=(const NHero& ) = delete;

    void HeroMovesInIntro(status_t& status);
    void HeroUp();
    void HeroDown();
    void HeroRight();
    void HeroLeft();
    void HeroStop();
    void Move() override;
    const plot* LazerStart() const {return ComplexObject::GetLazerStart();}
    bool Status() const {return ElementaryObject::Status();}
};



class BaseLazer: public ElementaryObject
{
    protected:
    dir::direction direct;

    public:
    BaseLazer(const plot* start, dir::direction d, const texture_* t);
    BaseLazer(const BaseLazer&) = delete;
    BaseLazer& operator=(const BaseLazer&) = delete;
    virtual ~BaseLazer() {}
    void Move();
    int Lazer_x() const;
    int Lazer_y() const;
    int Lazer_w() const;
    void ShowLazer(const Sdl* sdl) const;
};

class HeroLazer: public BaseLazer
{
    public:
    HeroLazer(const plot* start, const texture_* t);
};


class AlienABC: public ComplexObject
{
    protected:
    int scoreWeight;
    rect_* lazerMainRect;

    void setToStartPos(const int x, const int y) override;
    virtual void setCr() = 0;
    void initLazerStart()      override;
    void recomputeLazerStart() override;
    void show(const Sdl* sdl) const;

    public:
    AlienABC(const texture_* t, const int arrLen, const plot* start,
                  const texture_* lazer);
    AlienABC(const AlienABC&) = delete;
    ~AlienABC();
    AlienABC& operator=(const AlienABC&) = delete;
    int GetScoreWeight() const {return scoreWeight;}

};


/// @brief Plain alien type one
class Alien: public AlienABC
{
    private:
    void setCr();

    public:
    Alien(const texture_* t, const plot* start, const texture_* lazer);
    ~Alien();
    Alien(const Alien&) = delete;
    Alien& operator=(const Alien&) = delete;
    bool operator==(const HeroLazer& hl);
    void Move();
    void Show(const Sdl* sdl);



};


class ArrStorageABC
{
    protected:
    bool init {true};
    int storageCapacity;
    int counter;
    ElementaryObject** storage;
    bool cleaning(const int indexClean);

    public:
    ArrStorageABC(const int capacity);
    ArrStorageABC(const ArrStorageABC&) = delete;
    ArrStorageABC& operator=(const ArrStorageABC&) = delete;
    virtual ~ArrStorageABC() = 0;
    bool Status() const {return init;}
    void Clear();
    //virtual bool Push(ElementaryObject* ob) = 0;
    bool Push(ElementaryObject* ob);

    int GetCapacity() const {return storageCapacity;}
    int GetCounter()   {return counter;}
    void  Remove(const int index);
    void Sort(const int arrLen);

};

class HeroLazerStorage: public ArrStorageABC
{
    public:
    explicit HeroLazerStorage(const int capacity);
    ~HeroLazerStorage() {}
    HeroLazerStorage(const HeroLazerStorage&) = delete;
    HeroLazerStorage& operator=(const HeroLazerStorage&) = delete;

    HeroLazer* operator[](const int index);
    //bool Push(ElementaryObject* ob) override;
    void Move(bool& flag_toStartSort);
    void Show(const Sdl* sdl) const;
};


class AlienFleet_oneStorage: public ArrStorageABC
{
    public:
    explicit AlienFleet_oneStorage(const int capacity);
    ~AlienFleet_oneStorage() {}
    AlienFleet_oneStorage(const AlienFleet_oneStorage&) = delete;
    AlienFleet_oneStorage& operator=(const AlienFleet_oneStorage&) = delete;
    Alien* operator[](const int index);
    //bool Push(ElementaryObject* ob) override;
};

//All aliens lazers storage
class AliensLazersStorage: public ArrStorageABC
{
    public:
    explicit AliensLazersStorage(const int capacity);
    ~AliensLazersStorage() {}
    AliensLazersStorage(const AliensLazersStorage&) = delete;
    AliensLazersStorage& operator=(const AliensLazersStorage&) = delete;
    ElementaryObject* operator[](const int index);
    //bool Push(ElementaryObject* ob) override;

};


/*Место для хранения объектов*/
class ObjectsStore
{
    private:
    bool init {true};
    const tc* tcollection;
    HeroLazerStorage* heroLazerStorage;
    AliensLazersStorage* aliensLazerStorage;
    AlienFleet_oneStorage* alienFleetOneStorage;

    bool makeAlienFleetOne(const tc* collection);
    
    

    public:
    ObjectsStore(const tc* collection);
    ~ObjectsStore();
    ObjectsStore(const ObjectsStore&) = delete;
    ObjectsStore& operator=(const ObjectsStore&) = delete;
    bool MakeHeroLazer(const plot* start);
    void MoveHeroLazers();
    void ShowHeroLazers(const Sdl* sdl) const;
    void MoveAlienFleetOne();
    void ShowAlienFleetOne(const Sdl* sdl) const;


    bool Status() const {return init;}
    bool  Checks_herolazer_plainAlien(status_t& status);



};





#endif


