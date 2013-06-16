/** All Headers **/
#include"Snake.h"

/** Constructor **/
Snake :: Snake()
{
    x = 300; //x-coord
	y = 100; //y-coord
	xVel = 0; //speed traveling left and right
	yVel = 0; //speed traveling up and down
}

/** Function for movement **/
void Snake :: move()
{
    x += xVel;
    y += yVel;
}

void Snake :: reset()
{
    x = 300;
    y = 100;
    xVel = 0;
    yVel = 0;
}

int Snake :: get_x()
{
    return x;
}

int Snake :: get_y()
{
    return y;
}

/** Function to change directions **/
int Snake :: change(int x_Vel, int y_Vel)
{
    xVel = x_Vel;
    yVel = y_Vel;
}

SDL_Rect Snake :: check2() //create Rect object for collision test
{
    SDL_Rect sn;
    sn.x = x;
    sn.y = y;
    sn.h = 20;
    sn.w = 22;
    return sn;
}
