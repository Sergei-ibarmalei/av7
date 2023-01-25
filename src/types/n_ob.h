#ifndef N_OB_H
#define N_OB_H

//#include "sdlclass.h"
#include "template_objectslist.hpp"
#include "gametypes.h"
#include "../loging/loging.h"
#include "../consts/gameconsts.h"
#include "test.h"
#include "texturescollection.h"
#include "gameInfoClass.h"

/*Абстрактный класс - основа всех объектов*/
class ElementaryObject
{
    protected:
    bool init {true};
    bool isOnScreen {false};
    bool isGone {false};
    texture_*  obj_texture    {nullptr};
    plot*      obj_velocities {nullptr};
    plot*      obj_center     {nullptr};
    void setUpLeftCorner(const int x, const int y);
    void resetUpLeftCorner();
    void resetUpLeftCorner_x(const int x);
    void resetUpLeftCorner_y(const int y);
    void ShowObj(const Sdl* sdl) const;
    void resetCenter();


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
    plot* GetCenter() const {return obj_center;}
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
    void Move() override;
    echelon* GetHeroEchelon() const {return heroEchelon;}
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
    bool operator==(const echelon* heroEchelon);
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
};


class DieScoresObject: public ElementaryObject
{
    
   private:
   enum {pathLength = 40,};
   int stepsCount;
   void move_object();

   public:
   DieScoresObject(const texture_* t);
   ~DieScoresObject() {}
   DieScoresObject(const DieScoresObject&) = delete;
   DieScoresObject& operator=(const DieScoresObject&) = delete;
   void Move();
   void Show(const Sdl* sdl) const;

};

class DieScoresComplex
{
    private:
    enum {firstTexture, secondTexture, maxTexture,};
    bool init {true};
    int arrLen;
    DieScoresObject** complex;

    public:
    DieScoresComplex(const plot* ship_center, const texture_* first, 
                     const texture_* second = nullptr);
    DieScoresComplex(const DieScoresComplex&) = delete;
    DieScoresComplex& operator=(const DieScoresComplex&) = delete;
    ~DieScoresComplex();
    bool Status() const {return init;}
    void Move();
    void Show(const Sdl* sdl) const;
    bool IsItGone() const {return complex[firstTexture]->IsItGone();}
    
};





/*Место для хранения объектов*/
class Engine
{
    private:
    bool init {true};
    const tc* tcollection;
    const texture_* digits;
    HeroLazerStorage* heroLazerStorage;
    AlienFleet_oneStorage* alienFleetOneStorage;

    ObjectsList<DieScoresComplex>* dieScoresStorage;
    ObjectsList<AlienLazer>*       alienLazerStorage;
    DieScoresComplex* make_scoreComplex(const plot* ship_center, 
                                        const int score);

    bool makeAlienFleetOne(const tc* collection);
    bool makeHeroLazer(const plot* start);
    void MoveHeroLazers();
    void ShowHeroLazers(const Sdl* sdl) const;
    void MoveAlienFleetOne(const echelon* heroEchelon);
    void ShowAlienFleetOne(const Sdl* sdl) const;
    void ShowAlienFleetOneLazers(const Sdl* sdl) const;
    bool Checks_herolazer_plainAlien(status_t& status);
    void ShowDieScores(const Sdl* sdl) const;
    void MoveDieScores();
    void MoveAlienFleetOneLazers();
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


