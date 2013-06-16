#ifndef SETUP_H
#define SETUP_H
/** All Headers **/
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
using namespace std;

class Setup
{
	public:
	Setup();
	bool init(int screen_width, int screen_height);
	SDL_Surface* load_image(string image);
	SDL_Surface* load_image_wcolor(string image, Uint8 red, Uint8 green, Uint8 blue);
	SDL_Surface* getscreen();
	void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
	void update_screen();
	void clean_up();

	private:
	SDL_Surface* screen;

};

#endif
