/** All Headers **/
#include "Setup.h"
using namespace std;

/** Constructor **/
Setup :: Setup()
{
}

/** Initiate all functions of SDL **/
/** Sets up Window **/
bool Setup :: init(int screen_width, int screen_height)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) //initiate all SDL functions
		return false; //if failed return false
	screen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE); //create a window with height and width
	if(screen == NULL) //if screen did not load return false
		return false;
	SDL_WM_SetCaption("Grab the Star!", NULL); //setup a caption for window
	return true;
}

/** create SDL surface pointers to loaded images after optimizing image **/
SDL_Surface* Setup :: load_image(string image)
{
    SDL_Surface* loaded_image = NULL;
    SDL_Surface* optimizedImage = NULL;

	loaded_image = IMG_Load(image.c_str());
	if(loaded_image)
	{
		SDL_Surface* optimized_image = SDL_DisplayFormat(loaded_image); //converts image to same item type
		SDL_FreeSurface(loaded_image); //deallocate unneeded image
		return optimized_image;
	}
	return NULL;
}

/** Load image function with color key **/
SDL_Surface* Setup :: load_image_wcolor(string image, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_Surface* loaded_image = load_image(image);
	if(loaded_image)
	{
		Uint32 color_key = SDL_MapRGB(loaded_image->format, red, green, blue);
		SDL_SetColorKey(loaded_image, SDL_SRCCOLORKEY, color_key); //set color key according to red, green, blue that makes up the color
		return loaded_image;
	}
	return NULL;
}

SDL_Surface* Setup :: getscreen()
{
	return screen; //return screen pointer
}

/** Function to put image to screen at certain x, y coordinates **/
void Setup :: apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset); //puts image to screen
}

/** Update the screen **/
void Setup :: update_screen()
{
	SDL_Flip(screen);
}

/** Shut off SDL and quit program **/
void Setup :: clean_up()
{
	SDL_Quit();
}
