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
    bool operator==(const ElementaryObject& eo);
    bool operator==(const ElementaryObject* peo);
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
    bool operator==(const ElementaryObject& eo);
    bool operator==(const ElementaryObject* eo);
    bool operator==(const ComplexObject& co);
    ~ComplexObject();
    ComplexObject(const ComplexObject& co);
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

class PlainAlienABC: public ComplexObject
{
    protected:
    rect_* lazerMainRect;
    bool isGone {false};

    void setToStartPos(const int x, const int y) override;
    virtual void setCr() = 0;
    void initLazerStart()      override;
    void recomputeLazerStart() override;
    void show(const Sdl* sdl) const;

    public:
    PlainAlienABC(const texture_* t, const int arrLen, const plot* start,
                  const texture_* lazer);
    PlainAlienABC(const PlainAlienABC&) = delete;
    ~PlainAlienABC();
    PlainAlienABC& operator=(const PlainAlienABC&) = delete;
    virtual void Move() = 0;

};



class PlainAlien_t1: public PlainAlienABC
{
    private:
    void setCr();

    public:
    PlainAlien_t1(const texture_* t, const plot* start, const texture_* lazer);
    ~PlainAlien_t1();
    PlainAlien_t1(const PlainAlien_t1&) = delete;
    PlainAlien_t1& operator=(const PlainAlien_t1&) = delete;
    void Move() override;
    void Show(const Sdl* sdl);

    bool& Gone() {return isGone;} 


};


class LongLazer: public ElementaryObject
{
    private:
    dir::direction direct;

    public:
    LongLazer(const plot* start, dir::direction d, const texture_* t);
    LongLazer& operator=(const LongLazer& ) = delete;
    LongLazer(const LongLazer& ) = delete;
    ~LongLazer(){}
    void Move();
    int GetLazer_x() const;
    int GetLazer_y() const;
    int GetLazer_w() const;
    int GetLazerW()  const;
    int GetLazerH()  const;
    void Show(const Sdl* sdl) const;
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
    virtual ~ArrStorageABC();
    bool Status() const {return init;}
    void Clear();
    virtual bool Push(ElementaryObject* ob) = 0;

    int GetCapacity() const {return storageCapacity;}
    int& GetCounter()   {return counter;}
    bool Remove(const int index);
    void Sort(const int arrLen, int& counter);

};

class HeroLazerStorage: public ArrStorageABC
{
    public:
    explicit HeroLazerStorage(const int capacity);
    ~HeroLazerStorage() {}
    HeroLazerStorage(const HeroLazerStorage&) = delete;
    HeroLazerStorage& operator=(const HeroLazerStorage&) = delete;
    LongLazer* operator[](const int index);
    bool Push(ElementaryObject* ob) override;
    void Move(bool& flag_toStartSort);
    void Show(const Sdl* sdl) const;
};


class AlienFleet_oneStorage: public ArrStorageABC
{
    protected:
    public:
    explicit AlienFleet_oneStorage(const int capacity);
    ~AlienFleet_oneStorage() {}
    AlienFleet_oneStorage(const AlienFleet_oneStorage&) = delete;
    AlienFleet_oneStorage& operator=(const AlienFleet_oneStorage&) = delete;
    PlainAlien_t1* operator[](const int index);
    bool Push(ElementaryObject* ob) override;

};



class ObjectsStore
{
    private:
    bool init {true};
    const tc* tcollection;
    HeroLazerStorage* heroLazerStorage;
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


    bool Status() const {return init;}


};





#endif


