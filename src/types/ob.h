#ifndef OB_H
#define OB_H

#include "sdlclass.h"
#include "../loging/loging.h"
#include "test.h"

class Object
{
    protected:
    bool init {true};
    Cca* ca;
    texture_* obj_texture;

    virtual void setCollisionsRects(const plot& c) = 0;

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

    void setCollisionsRects(const plot& center);
    

    public:
    Hero(const plot& center, const texture_* t, log_::Log& log);
    ~Hero();
    #ifdef SHOW_COL_R
        void showColR(Sdl* sdl);
    #endif


};


#endif