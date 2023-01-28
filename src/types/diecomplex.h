#ifndef DIECOMPLEX_H
#define DIECOMPLEX_H

#include "dieobject.h"

class DieComplex
{
    private:
    enum {firstTexture, secondTexture, maxTexture,};
    bool init {true};
    int arrLen;
    DieObject** complex;

    public:
    DieComplex(const plot* ship_center, const texture_* first, 
                     const texture_* second = nullptr);
    DieComplex(const DieComplex&) = delete;
    DieComplex& operator=(const DieComplex&) = delete;
    ~DieComplex();
    bool Status() const {return init;}
    void Move();
    void Show(const Sdl* sdl) const;
    bool IsItGone() const {return complex[firstTexture]->IsItGone();}
    
};

#endif