#ifndef N_OB_H
#define N_OB_H

//#include "elementaryobject.h"
//#include "complexobject.h"
//#include "nhero.h"
#include "objectslist.h"

//#include "sdlclass.h"
//#include "gametypes.h"
#include "../consts/gameconsts.h"
#include "test.h"
#include "texturescollection.h"
#include "gameInfoClass.h"
/*#include "sdlclass.h"*/
#include "diecomplex.h"



/*Сложный класс для объектов с прямоугольниками пересечений*/
/*class ComplexObject: public ElementaryObject
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
    bool operator==(const rect_& r);
    ComplexObject(const ComplexObject& co) = delete;
    plot* GetLazerStart() const {return lazerStart;}
    plot* GetCenter() const {return obj_center;}
    //virtual void Move() = 0;

    void Show(const Sdl* sdl) const;
    CRC* CR() const {return cr;}

};*/

/*Пересечения*/
/*namespace re
{
    enum  heros {one, two, three, four, five, allR};

    enum  alien_t1 {t1_one, t1_two, t1_three, t1_allR};
}

namespace scores
{
    enum weight {plainAlien = 5,};
}*/

/*class NHero: public ComplexObject
{
    private:
    plot*   heroStopIntro {nullptr};
    echelon* heroEchelon  {nullptr};
    void    recomputeHeroEchelon();
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
    void Move();
    
    echelon* GetHeroEchelon() const {return heroEchelon;}
    const plot* LazerStart() const {return ComplexObject::GetLazerStart();}
    bool Status() const {return ElementaryObject::Status();}
};*/




/*template<class T>
class ObjectsList
{
    private:
    template<class N>
    struct Node
    {
        N* data;
        struct Node* next;
        ~Node()
        {
            delete data;
            data = nullptr;
        }
    };
    struct Node<T>* first;
    struct Node<T>** current;

    public:
    ObjectsList();
    ~ObjectsList();
    ObjectsList(const ObjectsList&) = delete;
    ObjectsList& operator=(const ObjectsList&) = delete;
    void Push(T* data);
    void Show(const Sdl* sdl) const;
    void Check_and_clear();
    bool Check_withObject(NHero* hero);
    void Move();
    bool IsEmpty();


};

template<class T>
bool ObjectsList<T>::IsEmpty()
{
    return (first == nullptr);
}

template<class T>
ObjectsList<T>::ObjectsList()
{
    first = nullptr;
}

template<class T>
ObjectsList<T>::~ObjectsList()
{
    while (first)
    {
        struct Node<T>* tmp = first;
        first = first->next;
        delete tmp;
        tmp = nullptr;
    }
}

template<class T>
void ObjectsList<T>::Push(T* data)
{
    if (!data) return;
    struct Node<T>* tmp = new (std::nothrow) Node<T>;
    if (!tmp) return;
    tmp->data = data;
    if (!first)
    {
        tmp->next = nullptr;
        first = tmp;
        return; 
    }
    tmp->next = first;
    first = tmp;
    return;
}

template<class T>
void ObjectsList<T>::Show(const Sdl* sdl) const
{
    if (!first) 
    {
        return;
    }
    struct Node<T>* tmp = first;
    while (tmp)
    {
        tmp->data->Show(sdl);
        tmp = tmp->next;
    }

}

template<class T>
void ObjectsList<T>::Check_and_clear()
{
    current = &first;
    while (*current)
    {
        if ( (*current)->data->IsItGone())
        { 
            struct Node<T>* tmp = *current;
            *current = (*current)->next;
            delete tmp;
        }
        else current = &(*current)->next;
    }
}*/


/*Проверка на столкновение с героем*/
/*template<class T>
bool ObjectsList<T>::Check_withObject(NHero* hero)
{
    if (!first) return false;

    Если герой уже подбит, выходим
    if (hero->IsItGone() == true) return false;

    current = &first;
    while(*current)
    {
        if ( *((*current)->data) == *hero)
        {
            struct Node<T>* tmp = *current;
            *current = (*current)->next;
            delete tmp;
            //отмечаем,что героя подбили
            hero->ItIsGoneNow();
            return true;
        }
        else current = &(*current)->next;
    }
    return false;
}

template<class T>
void ObjectsList<T>::Move()
{
    if (!first) return;
    struct Node<T>* tmp = first;
    while(tmp)
    {
        tmp->data->Move();
        tmp = tmp->next;
    }
}*/






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
    void Show(const Sdl* sdl) const;
};

class HeroLazer: public BaseLazer
{
    public:
    HeroLazer(const plot* start, const texture_* t);
};

class AlienLazer: public BaseLazer
{
    public:
    AlienLazer(const plot* start, const texture_* t);
    bool operator==(NHero& hero);
};


class AlienABC: public ComplexObject
{
    protected:
    int scoreWeight;
    int stepsWithoutFire;
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
    int GetStepsWithoutFire() const {return stepsWithoutFire;}
    void ResetStepsWithoutFire() {stepsWithoutFire = 0;}
    void StrightMove();

};


/// @brief Plain alien type one
class Alien: public AlienABC
{
    private:
    void setCr();
    public:
    Alien(const texture_* t, const plot* start, const texture_* lazer);
    ~Alien() {}
    Alien(const Alien&) = delete;
    Alien& operator=(const Alien&) = delete;
    bool operator==(const HeroLazer& hl);
    bool operator==(const echelon* heroEchelon);
    bool operator==(const NHero* hero);
    void Show(const Sdl* sdl);
};


class ArrStorageABC
{
    protected:
    bool init {true};
    int storageCapacity;
    int counter;
    int live_size;
    ElementaryObject** storage;

    public:
    ArrStorageABC(const int capacity);
    ArrStorageABC(const ArrStorageABC&) = delete;
    ArrStorageABC& operator=(const ArrStorageABC&) = delete;

    ElementaryObject* operator[](const int index);

    virtual ~ArrStorageABC() = 0;
    bool Status() const {return init;}
    void Clear();
    bool Push(ElementaryObject* ob);
    bool Clear_at(const int index);

    int GetCounter()   {return counter;}
    void  Remove(const int index);
    void Sort(const int arrLen);
    bool IsEmpty() const {return live_size == 0;}
    

};

class HeroLazerStorage: public ArrStorageABC
{
    public:
    explicit HeroLazerStorage(const int capacity);
    ~HeroLazerStorage() {}
    HeroLazerStorage(const HeroLazerStorage&) = delete;
    HeroLazerStorage& operator=(const HeroLazerStorage&) = delete;

    HeroLazer* operator[](const int index);
    void Move(bool& flag_toStartSort);
    void Show(const Sdl* sdl) const;
};


class AlienStorage: public ArrStorageABC
{
    public:
    explicit AlienStorage(const int capacity);
    ~AlienStorage() {}
    AlienStorage(const AlienStorage&) = delete;
    AlienStorage& operator=(const AlienStorage&) = delete;
    Alien* operator[](const int index);
};


/*class DieObject: public ElementaryObject
{
    
   private:
   enum {pathLength = 60,};
   int stepsCount;
   void move_object();

   public:
   DieObject(const texture_* t);
   ~DieObject() {}
   DieObject(const DieObject&) = delete;
   DieObject& operator=(const DieObject&) = delete;
   void Move();
   void Show(const Sdl* sdl) const;

};*/



/*class DieComplex
{
    private:
    enum {firstTexture, secondTexture, maxTexture,};
    bool init {true};
    int arrLen;
    DieObject** complex;

    public:
    DieComplex(const plot* ship_center, const texture_* first, 
                     const texture_* second = nullptr);
    DieComplex(const DieComplex&) = delete;
    DieComplex& operator=(const DieComplex&) = delete;
    ~DieComplex();
    bool Status() const {return init;}
    void Move();
    void Show(const Sdl* sdl) const;
    bool IsItGone() const {return complex[firstTexture]->IsItGone();}
    
};*/

class GameFleet_ABC
{
    protected:
    bool init {true};
    const tc* tcollection;
    const texture_* digits;
    int fleetStorage_livesize;
    int tmp_fleetStorage_livesize;
    AlienStorage* fleetStorage;
    AlienStorage* tmp_fleetStorage;
    ObjectsList<AlienLazer>* fleetLazerStorage;


    public:
    GameFleet_ABC(const tc* collection, const texture_* heap_digits);
    virtual ~GameFleet_ABC() = 0;

    bool Status() const {return init;}
    bool FleetStorageEmpty()    const {return fleetStorage_livesize == 0;}
    bool TmpFleetStorageEmpty() const {return tmp_fleetStorage == 0;}

    virtual void MoveFleet(NHero* hero, status_t&  status) = 0;
    virtual void MoveFleetLazers() = 0;

    virtual void ShowFleet(const Sdl* sdl) const = 0;
    virtual void ShowFleetLazers(const Sdl* sdl) const = 0;

    virtual void CheckFleetCrashHero(NHero* hero, status_t& status,
                                ObjectsList<DieComplex>* dieStorage) = 0;
    virtual void CheckFleetLazerHitsHero(NHero* hero, status_t& status,
                                ObjectsList<DieComplex>* dieStorage) = 0;

    virtual void ClearFleetLazers() = 0;
    ArrStorageABC* Fleet() {return fleetStorage;}


};


class FirstFleet: public GameFleet_ABC
{
    private:
    bool makeFirstFleet(tc* collection);

    public:
    FirstFleet(const tc* collection, const texture_* heap_digits);
    FirstFleet(const FirstFleet&) = delete;
    FirstFleet& operator=(const FirstFleet&) = delete;

    void MoveFleet(NHero* hero, status_t& status) override;
    void MoveFleetLazers() override;

    void ShowFleet(const Sdl* sdl) const override;
    void ShowFleetLazers(const Sdl* sdl) const override;

    void CheckFleetCrashHero(NHero* hero, status_t& status,
                            ObjectsList<DieComplex>* dieStorage) override;
    void CheckFleetLazerHitsHero(NHero* hero, status_t& status,
                            ObjectsList<DieComplex>* dieStorage) override;
    void ClearFleetLazers() override;
                    
};


/*Место для хранения объектов*/
class Engine
{
    private:
    bool init {true};
    const tc* tcollection;
    const texture_* digits;
    HeroLazerStorage* heroLazerStorage;
    AlienStorage* alienFleetOneStorage;
    AlienStorage* alienFleetTmpStorage;


    ObjectsList<DieComplex>* dieStorage;
    ObjectsList<AlienLazer>* alienLazerStorage;

    DieComplex* make_DieComplex(const plot* ship_center, const int score);
    DieComplex* make_DieComplex(const plot* ship_center);

    bool make_tmpAlienFleetOneStorage(status_t& status);
    bool makeAlienFleetOne(const tc* collection);
    bool makeHeroLazer(const plot* start);

    void MoveHeroLazers();
    void MoveAlienFleetOne(NHero* hero, status_t& status);
    void MoveDieScores();
    void MoveAlienFleetOneLazers();

    void ShowHeroLazers(const Sdl* sdl) const;
    void ShowAlienFleetOne(const Sdl* sdl) const;
    void ShowAlienFleetOneLazers(const Sdl* sdl) const;
    void ShowDieScores(const Sdl* sdl) const;

    void Checks_AleinFleetOneHitsHero(NHero* hero, status_t& status);
    bool Checks_herolazer_hitsAlien(status_t& status);
    void Checks_alienlazer_hitsHero(NHero* hero, status_t& status);
    void Checks_isHeroDead(status_t& status);

    void ClearDieScores();
    void ClearAlienLazers();   
    

    public:
    Engine(const tc* collection, const texture_* heap_digits);
    ~Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    bool Status() const {return init;}
    void DoGameAlgorithm(NHero* hero, const Sdl* sdl, status_t& status,
                            GameInfoClass* gameInfo);
    bool MakeHeroLazer(const plot* start);
    void InPause(const Sdl* sdl, status_t& status, GameInfoClass* gameInfo);


};





#endif


