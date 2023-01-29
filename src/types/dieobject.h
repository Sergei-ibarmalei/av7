#ifndef DIEOBJECT_H
#define DIEOBJECT_H

#include "elementaryobject.h"
#include "../consts/gameconsts.h"

class DieObject: public ElementaryObject
{
    
   private:
   enum {pathLength = 60,};
   int stepsCount;
   void move_object();

   public:
   DieObject(const texture_* t);
   ~DieObject() {}
   DieObject(const DieObject&) = delete;
   DieObject& operator=(const DieObject&) = delete;
   void Move();
   void Show(const Sdl* sdl) const;

};


#endif