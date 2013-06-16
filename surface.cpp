/** All Headers **/
#include "surface.h"

/** Constructor **/
Surface :: Surface(char _imageID, int _x_pos, int _y_pos, int _height, int _width)
{
	imageID = _imageID;
	x_pos = _x_pos;
	y_pos = _y_pos;
	height = _height;
	width = _width;
}

int Surface :: get_x_pos()
{
	return x_pos; //get x-coord
}

int Surface :: get_y_pos()
{
	return y_pos; //get y-coord
}

char Surface :: get_imageID()
{
	return imageID; //get ID for identifying type
}

void Surface :: set_x_pos(int _x_pos)
{
	x_pos = _x_pos; //setting x-coord
}

void Surface :: set_y_pos(int _y_pos)
{
	y_pos = _y_pos; //setting y-coord
}

void Surface :: set_imageID(char _imageID)
{
	imageID = _imageID; //setting ID
}

SDL_Rect Surface :: get_rect() //Rect for collision detection
{
    SDL_Rect box;
    box.x = x_pos;
    box.y = y_pos;
    box.h = height;
    box.w = width;
    return box;
}
