#ifndef CHECKING_H
#define CHECKING_H


#include "../consts/gameconsts.h"



bool isGonnaCrossUp_check(const int mainrect_up_y, const int velocity_y);
bool isGonnaCrossDown_check(const int mainrect_height, const int velocity_y);
bool isGonnaCrossRight_check(const int mainrect_w, const int velocity_x);
bool isGonnaCrossLeft_check(const int mainrect_left, const int velocity_x);
bool hasCrossedLeft(const int mainrect_x);
#endif