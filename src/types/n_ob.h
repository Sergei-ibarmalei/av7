#ifndef N_OB_H
#define N_OB_H

#include "sdlclass.h"
#include "gametypes.h"
#include "../loging/loging.h"
#include "../consts/gameconsts.h"
#include "test.h"
#include "texturescollection.h"

#include <list>
#include <memory>

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

#ifdef SHOW_COL_R
    void showCollisionMainRect(Sdl* sdl);
#endif

    public:
    ElementaryObject(const texture_* t);
    ElementaryObject(const ElementaryObject& eo);
    ElementaryObject& operator=(const ElementaryObject& eo);
    bool operator==(const ElementaryObject& eo);
    bool operator==(const ElementaryObject* peo);
    virtual ~ElementaryObject();
    void ShowObj(Sdl* sdl);
    bool Status() const {return init;}
    virtual void Move() = 0;
    rect_& MainRect() const {return obj_texture->main_rect;}
    bool OnScreen() const {return isOnScreen;}
    int  GetMainRect_x() const {return obj_texture->main_rect.x;}
    int  GetMainRect_y() const {return obj_texture->main_rect.y;}
    int  GetMainRectW() const {return obj_texture->main_rect.x+
                                obj_texture->main_rect.w;}
    int GetMainRectH()  const {return obj_texture->main_rect.y+
                                obj_texture->main_rect.h;}
    plot* Velocities() {return obj_velocities;}
};

class ComplexObject: public ElementaryObject
{
    protected:
    CRC* cr;
    plot* lazerStart {nullptr};
    int collisionArrLen;
    virtual void setToStartPos() = 0;
    virtual void setCr() = 0;
    virtual void initLazerStart() = 0;
    virtual void recomputeLazerStart() = 0;
    #ifdef SHOW_COL_R
        void ShowColR(Sdl* sdl, const int len);
    #endif

    public:
    ComplexObject(const texture_* t, const int arrLen);
    ComplexObject& operator=(const ComplexObject& ) = delete;
    bool operator==(const ElementaryObject& eo);
    bool operator==(const ComplexObject& co);
    ~ComplexObject();
    ComplexObject(const ComplexObject& co);
    virtual void Move() = 0;

};

/*Пересечения*/
namespace re
{
    /*прям. пересечений героя*/
    enum heros {one, two, three, four, five, allR};
}

class NHero: public ComplexObject
{
    private:
    plot*   heroStopIntro {nullptr};
    void    initHeroStopIntro();
    void    initLazerStart();
    void    recomputeLazerStart();
    void    setToStartPos(); 
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
    bool Status() const {return ElementaryObject::Status();}
    #ifdef SHOW_COL_R
        void ShowColR(Sdl* sdl);
    #endif
};


class LongLazer: public ElementaryObject
{
    private:
    dir::direction direct;

    public:
    LongLazer(const plot* start, dir::direction d, const texture_* t);
    void Move();
    #ifdef SHOW_COL_R
        void ShowColR(Sdl* sdl);
    #endif
};


class ObjectList
{
    protected:
    bool init {true};
    const tc* tcolleciton;
    std::list<ElementaryObject*> objectList;


    public:
    ObjectList(const tc* collection);
    bool Status() const {return init;}
};


#endif


