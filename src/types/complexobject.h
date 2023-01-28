#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H

#include "elementaryobject.h"

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
    bool operator==(const rect_& r);
    ComplexObject(const ComplexObject& co) = delete;
    plot* GetLazerStart() const {return lazerStart;}
    plot* GetCenter() const {return obj_center;}

    void Show(const Sdl* sdl) const;
    CRC* CR() const {return cr;}

};

#endif