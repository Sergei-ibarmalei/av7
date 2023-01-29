#ifndef ALIENABC_H
#define ALIENABC_H

#include "complexobject.h"


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

#endif