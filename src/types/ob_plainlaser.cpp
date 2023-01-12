#include "ob.h"


LaserNode::LaserNode(plot* s, dir::direction d, const texture_* t)
{
    laser = new Laser(s, d, t);
    next = prev = nullptr;
}

Laser::Laser(plot* start, dir::direction d, 
                        const texture_* t): Object(t)
{
    direct = d;
    isOnScreen = true;
    if (direct == dir::left)
        setUpLeftCorner(start->x - obj_texture->main_rect.w, start->y);
    else 
        setUpLeftCorner(start->x, (start->y - obj_texture->main_rect.h / 2));


}

Laser::~Laser()
{

}

void Laser::Move()
{
    #define LASER_W obj_texture->main_rect.x + obj_texture->main_rect.w

    if (isOnScreen)
    {
        switch (direct)
        {
            case dir::left:
            {
                obj_texture->main_rect.x -= PLAINLASER_VELOCITY;
                if (LASER_W < BORDER_THICKNESS)
                    isOnScreen = false;
                break;
            }
            case dir::right:
            {
                obj_texture->main_rect.x += PLAINLASER_VELOCITY; 
                if (obj_texture->main_rect.x > RIGHT_BORDER_X)
                    isOnScreen = false;
                break;
            }
            default: {}
        }
    }

    #undef LASER_W
}

