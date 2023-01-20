#ifndef CHECKCROSSING_H
#define CHECKCROSSING_H


#include "../consts/gameconsts.h"



bool isGonnaCrossUp_check(const int mainrect_up_y, const int velocity_y);
bool isGonnaCrossDown_check(const int mainrect_height, const int velocity_y);
bool isGonnaCrossRight_check(const int mainrect_w, const int velocity_x);
bool isGonnaCrossLeft_check(const int mainrect_left, const int velocity_x);
bool hasCrossedLeft_fromScreen(const int x);
bool hasCrossedRight_fromOut(const int x);
bool hasCrossedRight_fromScreen(const int x);
#endif