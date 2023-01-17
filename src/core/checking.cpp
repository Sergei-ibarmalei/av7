#include "checking.h"

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

bool hasCrossedLeft(const int mainrect_x)
{
    return mainrect_x < LEFT_BORDER_X + LEFT_BORDER_W;
}

bool hasCrossedRight(const int mainrect_x)
{
    return mainrect_x < LEFT_BORDER_X;
}