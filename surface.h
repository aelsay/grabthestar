#ifndef SURFACE_H

#define SURFACE_H
/** All Headers **/
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Surface
{
	public:
	Surface(char _imageID, int x_pos, int y_pos, int _height, int _width);
	int get_x_pos();
	int get_y_pos();
	char get_imageID();
	void set_x_pos(int _x_pos);
	void set_y_pos(int _y_pos);
	void set_imageID(char _imageID);
	SDL_Rect get_rect();
	private:
	char imageID;
	int x_pos, y_pos, height, width;
};

#endif
