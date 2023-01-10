#ifndef OB_H
#define OB_H

#include "sdlclass.h"
#include "gametypes.h"
#include "../loging/loging.h"
#include "../consts/gameconsts.h"
#include "test.h"

class Object
{
    protected:
    bool init {true};
    Cca* ca;
    texture_* obj_texture;
    void resetUpLeftCorner(dir::direction d, const int delta);
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
    Object(const texture_* t, log_::Log& log);
    Object(const Object& o);
    Object& operator=(const Object& o);
    bool operator==(const Object& o);
    bool operator==(const Object* po);
    virtual ~Object();
    void ShowObj(Sdl* sdl);
    bool Status() const {return init;}
};


class Hero: public Object
{
    private:
    enum {one, two, three, four, five, allRects};
    rect_* collisionRects {nullptr};
    //plot   heroCenter;
    plot   heroStopIntro;

    void setCollisionsRects() override;
    void setToStartPosition() override;

    

    public:
    Hero(const texture_* t, log_::Log& log);
    Hero(const Hero& ) = delete;
    Hero& operator=(const Hero& ) = delete;
    ~Hero();

    #ifdef SHOW_COL_R
        void showColR(Sdl* sdl);
    #endif
    void HeroMovesInIntro(status_t& status);

};


#endif