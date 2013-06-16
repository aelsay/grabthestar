/** All Headers **/
#include"Food.h"

/** Constructor **/
Food :: Food()
{
    /** Randomize x,y coordinates to anywhere on the screen **/
    srand(time(NULL));
    x = rand() % 611 + 4;
    y = rand() % 452 + 5;
}

void Food :: newFood() //get new coordinates
{
    x = rand() % 611 + 4;
    y = rand() % 452 + 5;
}

/*** Create Rect object for collision detection ***/
SDL_Rect Food :: check1()
{
    SDL_Rect f;
    f.x = x;
    f.y = y;
    f.h = 28;
    f.w = 28;
    return f;
}

int Food :: Get_food_x()
{
	return x; //get x-coord
}

int Food :: Get_food_y()
{
	return y; //get y-coord
}
