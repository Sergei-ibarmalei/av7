#ifndef NHERO_H
#define NHERO_H

#include "complexobject.h"
#include "gametypes.h"

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
    void Move();
    
    echelon* GetHeroEchelon() const {return heroEchelon;}
    const plot* LazerStart() const {return ComplexObject::GetLazerStart();}
    bool Status() const {return ElementaryObject::Status();}
};

#endif