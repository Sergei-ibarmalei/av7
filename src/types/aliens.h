#ifndef ALIENS_H
#define ALIENS_H

#include "n_ob.h"

class PlainAlienABC: public ComplexObject
{
    protected:
    rect_* lazerMainRect;

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


};

#endif