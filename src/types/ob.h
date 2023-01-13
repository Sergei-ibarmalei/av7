#ifndef OB_H
#define OB_H

#include "sdlclass.h"
#include "gametypes.h"
#include "../loging/loging.h"
#include "../consts/gameconsts.h"
#include "test.h"


#include<list>
#include <memory>


class Object
{
    protected:
    bool init {true};
    Cca* ca;
    texture_* obj_texture;
    plot*     obj_velocities;
    void resetUpLeftCorner(dir::direction d, const int delta);
    void resetUpLeftCorner();
    void setUpLeftCorner(const int x, const int y);
    void setRectsToNewPosStright(dir::direction d,
                                   const int stopRect,
                                   const int delta,
                                   rect_* rects);
    void setRectsToNewPosByPath(const plot* rects_offSets,
                                const int stopR,
                                rect_* rects);

    virtual void setCollisionsRects() = 0;
    virtual void setToStartPosition() = 0;

    #ifdef SHOW_COL_R
        void showCollisionRects(Sdl* sdl,
                                rect_* rects,
                                int start, int end);
    #endif

    public:
    Object(const texture_* t);
    Object(const Object& o);
    Object& operator=(const Object& o);
    bool operator==(const Object& o);
    bool operator==(const Object* po);
    virtual ~Object();
    void ShowObj(Sdl* sdl);
    bool Status() const {return init;}
    virtual void Move() = 0;
};

class Laser: public Object 
{
    private:
    bool isOnScreen;
    dir::direction direct;

    void setCollisionsRects() {}
    void setToStartPosition() {}

    public:
    Laser(plot* start, dir::direction d, 
                const texture_* t);
    ~Laser();
    Laser(const Laser& ) = delete;
    Laser& operator=(const Laser&) = delete;
    void Move() override;

    bool OnScreen() const {return isOnScreen;}
    int GetLaser_x() const {return Object::obj_texture->main_rect.x;};
    int GetLaser_w() const {return Object::obj_texture->main_rect.w;}


};




class Hero: public Object
{
    private:
    enum {one, two, three, four, five, allRects};
    rect_* collisionRects {nullptr};
    plot*   heroStopIntro {nullptr};
    plot*   laserStart {nullptr};

    void setCollisionsRects() override;
    void setToStartPosition() override;
    void initHeroStopIntro();
    bool isGonnaCrossRight();
    bool isGonnaCrossLeft();
    bool isGonnaCrossUp();
    bool isGonnaCrossDown();
    void recomputeLaserStart();
    void initLaserStart();
    

    public:
    Hero(const texture_* t);
    Hero(const Hero& ) = delete;
    Hero& operator=(const Hero& ) = delete;
    ~Hero();

    #ifdef SHOW_COL_R
        void showColR(Sdl* sdl);
    #endif
    void HeroMovesInIntro(status_t& status);
    void HeroUp();
    void HeroDown();
    void HeroRight();
    void HeroLeft();
    void HeroStop();
    void Move() override;
    plot* LaserStart() const {return laserStart;}
};



class Std_LaserStore
{
    private:
    std::list<Laser*> herolasers;
    texture_*  textureHeroLaser;

    public:
    ~Std_LaserStore();
    Std_LaserStore(texture_* t);
    Std_LaserStore(const Std_LaserStore& ) = delete;
    Std_LaserStore& operator=(const Std_LaserStore& ) = delete;
    void MakeHeroLaser(plot* start, dir::direction d);
    void ShowLaserStore(Sdl* sdl);
    void MoveLaserStore();
    void ClearLaserStore();

};


#endif

