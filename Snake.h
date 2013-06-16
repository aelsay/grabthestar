#ifndef SNAKE_H

#define SNAKE_H
/** All Headers **/
#include"Setup.h"

class Snake
{
	public:
	Snake();
	void move();
	void reset();
	int get_x();
	int get_y();
	int change(int x_Vel, int y_Vel);
	SDL_Rect check2();
    int h, w;

	private:
    int x, y;
	int xVel, yVel;

};

#endif
