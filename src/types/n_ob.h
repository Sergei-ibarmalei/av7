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

/*#ifdef SHOW_COL_R
    void showCollisionMainRect(const Sdl* sdl) const;
#endif*/

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
    /*#ifdef SHOW_COL_R
        void ShowColR(const Sdl* sdl, const int len);
    #endif*/

    public:
    ComplexObject(const texture_* t, const int arrLen);
    ComplexObject& operator=(const ComplexObject& ) = delete;
    bool operator==(const ElementaryObject& eo);
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
    /*#ifdef SHOW_COL_R
        void ShowColR(const Sdl* sdl);
    #endif*/
};


class LongLazer: public ElementaryObject
{
    private:
    dir::direction direct;

    public:
    LongLazer(const plot* start, dir::direction d, const texture_* t);
    LongLazer& operator=(const LongLazer& ) = delete;
    LongLazer(const LongLazer& ) = delete;
    ~LongLazer()
    {
        //std::cout << "In LongLazer dtor.\n";
    }
    void Move();
    int GetLazer_x() const;
    int GetLazer_y() const;
    int GetLazer_w() const;
    int GetLazerW()  const;
    int GetLazerH()  const;
    void Show(const Sdl* sdl) const;
};



struct ObjectNode
{
    ElementaryObject* object;
    struct ObjectNode* next;
    ObjectNode(): object(nullptr), next(nullptr) 
    {
        //std::cout << "In ObjectNode ctor.\n";
    }
    ObjectNode(const ObjectNode& ) = delete;
    ObjectNode& operator=(const ObjectNode& ) = delete;
    ~ObjectNode()
    {
        //std::cout << "In ObjectNode dtor.\n";
        delete object;
    }
};

using obNode = ObjectNode;

/*Абстрактный класс - односвязный список объектов ElementaryObject*/
class E_listABC
{
    protected:
    obNode* first;
    obNode* last;
    obNode* root;
    const tc* tcollection;

    //void push(ElementaryObject* ob);
    virtual bool push(ElementaryObject* ob) = 0;
    

    public:
    E_listABC(const tc* collection);
    E_listABC(const E_listABC& ) = delete;
    E_listABC& operator=(const E_listABC& ) = delete;
    const obNode* GetFirst() const {return first;}
    
    virtual ~E_listABC();
    virtual void Show(const Sdl* sdl) = 0;

};

/*Односвязный список для лазеров героя*/
class HeroLazersList: public E_listABC
{
    private:
    void showLazer(const Sdl* sdl, obNode* first);
    void moveLazer(obNode* first);
    bool push(ElementaryObject* ob) override;

    public:
    HeroLazersList(const tc* collection): E_listABC(collection) 
    {
        //std::cout << "In HeroLazerList ctor.\n";
    }
    HeroLazersList(const HeroLazersList& ) = delete;
    HeroLazersList& operator=(const HeroLazersList& ) = delete;
    ~HeroLazersList()
    {
        //std::cout << "In HeroLazerList dtor.\n";
    }

    void Show(const Sdl* sdl) override;
    bool Push(const plot* start);
    void Move();

};





/*Класс - хранилище списков объектов ElementaryObject*/
class ObjectsStore
{
    private:
    bool init {true};
    HeroLazersList* heroLazers {nullptr};


    public:
    ObjectsStore(const tc* collection);
    ~ObjectsStore();
    ObjectsStore(const ObjectsStore& ) = delete;
    ObjectsStore& operator=(const ObjectsStore& ) = delete;
    bool Status() const {return init;}

    void MakeHeroLazer(const plot* start);
    void ShowHeroLazers(const Sdl* sdl);
    void MoveHeroLazers();
};


#endif


