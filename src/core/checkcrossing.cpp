#include "checkcrossing.h"

bool isGonnaCrossUp_check(const int mainrect_up_y, const int velocity_y)
{
    return (mainrect_up_y + velocity_y) < UP_BORDER_Y + BORDER_THICKNESS;
}

bool isGonnaCrossDown_check(const int mainrect_height, const int velocity_y)
{
    return (mainrect_height + velocity_y) > DOWN_BORDER_Y;
}

bool isGonnaCrossRight_check(const int mainrect_w, const int velocity_x)
{
    return (mainrect_w + velocity_x) > RIGHT_BORDER_X;
}

bool isGonnaCrossLeft_check(const int mainrect_left, const int velocity_x)
{
    return (mainrect_left + velocity_x) < LEFT_BORDER_X + LEFT_BORDER_W;
}


/*Пересечение ЛЕВОЙ границы с внутренней стороны*/
bool hasCrossedLeft_fromScreen(const int x)
{
    return x < LEFT_BORDER_X + LEFT_BORDER_W;
}


/*Пересечение ПРАВОЙ границы с внешней стороны*/
bool hasCrossedRight_fromOut(const int x)
{
    return x < RIGHT_BORDER_X;
}

/*Пересечение ПРАВОЙ границы с внутренней стороын*/
bool hasCrossedRight_fromScreen(const int x)
{
    return x > RIGHT_BORDER_X;
}