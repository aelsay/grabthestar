#ifndef FOOD_H
#define FOOD_H
/** All Headers **/
#include<iostream>
#include<ctime>
#include<cstdlib>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Food
{
	public:
		Food();
		void newFood();
		int Get_food_x();
		int Get_food_y();
		SDL_Rect check1();
		int h, w;
	private:
		int x, y;
};
#endif
