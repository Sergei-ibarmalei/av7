#ifndef GAMECONSTS_H
#define GAMECONSTS_H

#define HERO_LIVES 3
#define HERO_VELOCITY_X 3
#define HERO_VELOCITY_Y 3

#define BORDER_THICKNESS 5
#define UP_BORDER_X 0
#define UP_BORDER_Y 80
#define UP_BORDER_W   S_W
#define UP_BORDER_H   BORDER_THICKNESS 
#define DOWN_BORDER_X UP_BORDER_X 
#define DOWN_BORDER_Y S_H - BORDER_THICKNESS 
#define DOWN_BORDER_W UP_BORDER_W 
#define DOWN_BORDER_H BORDER_THICKNESS 
#define LEFT_BORDER_X 0
#define LEFT_BORDER_Y UP_BORDER_Y + BORDER_THICKNESS 
#define LEFT_BORDER_W BORDER_THICKNESS 
#define LEFT_BORDER_H DOWN_BORDER_Y 
#define RIGHT_BORDER_X S_W - BORDER_THICKNESS 
#define RIGHT_BORDER_Y LEFT_BORDER_Y 
#define RIGHT_BORDER_W BORDER_THICKNESS 
#define RIGHT_BORDER_H LEFT_BORDER_H

#define FAST_STAR_VELOCITY 2
#define SLOW_STAR_VELOCITY 1

#define PLAINLASER_VELOCITY 1
#define PLAINLASER_OFFSET 20


/*Направление движения*/
namespace dir
{
    enum direction {right, left, up, down};
}



#endif