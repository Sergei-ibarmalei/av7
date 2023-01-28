#ifndef ELEMENTARYOBJECT_H
#define ELEMENTARYOBJECT_H

/*#include "gametypes.h"
#include "../consts/gameconsts.h"
#include "test.h"
#include "texturescollection.h"
#include "gameInfoClass.h"*/
#include "sdlclass.h"




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
    ElementaryObject(const ElementaryObject&) = delete;
    ElementaryObject& operator=(const ElementaryObject& ) = delete;
    virtual ~ElementaryObject();
    bool Status() const {return init;}
    bool operator==(const echelon* heroEchelon);

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
#endif