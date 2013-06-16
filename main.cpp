/** All Headers **/
#include "Setup.h"
#include "Food.h"
#include "Snake.h"
#include "surface.h"
#include "Timer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

#define FILENAME "map.txt"
#define SCREEN_HEIGHT 	480
#define SCREEN_WIDTH	640
#define SCREEN_BPP 		32
#define FRAMES_PER_SECOND 40

/*** Main Functions ***/
void Intro();
void Menu();
void Game();
void GameOver();
void Controls();
void Credits();
bool check_collision( SDL_Rect A, SDL_Rect B );

int main(int argc, char** argv)
{
    Intro();
    Menu();
	return 0;
}

void Intro()
{
    /*** Introduction ***/
    Setup SetupF;
    SetupF.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface* screen = SetupF.getscreen();
	SDL_Surface* Intro1 = SetupF.load_image("gfx/Intro1.png");
	SDL_Surface* Intro2 = SetupF.load_image("gfx/Intro2.png");
	SetupF.apply_surface(0, 0, Intro1, screen);
	SetupF.update_screen();
	SDL_Delay(2500);
	SetupF.apply_surface(0, 0, Intro2, screen);
	SetupF.update_screen();
	SDL_Delay(2500);
	/*** deallocate unneeded images ***/
	SDL_FreeSurface(Intro1);
	SDL_FreeSurface(Intro2);
	SDL_FreeSurface(screen);
}

void Menu()
{
    /* Menu with 3 options
    *Play
    *Controls
    *Credits
    Accessable via arrow keys and return key
    */
    SDL_Event event; //Event structure
	Setup SetupF;
    SetupF.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface* screen = SetupF.getscreen();
	SDL_Surface* background = SetupF.load_image("gfx/bkground.png");
	SDL_Surface* GameTitle = SetupF.load_image_wcolor("gfx/Title.png", 0, 0xFF, 0xFF);
	SDL_Surface* Hand = SetupF.load_image_wcolor("gfx/pointer.png", 0, 0xFF, 0xFF);
	int hand_y = 270; //Y-coordinates of the cursor

	bool tempx = false;
	while(tempx == false)
	{
		SetupF.apply_surface( 0, 0, background, screen);
		SetupF.apply_surface( 0, 0, GameTitle, screen);
		SetupF.apply_surface( 228, hand_y, Hand, screen);
		SetupF.update_screen();

		while( SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) //quit program
				SetupF.clean_up();
			if( event.type == SDL_KEYDOWN ) //key is pushed
			{
				switch( event.key.keysym.sym )
				{
					case SDLK_UP:
								if(hand_y == 270) //limits the cursor, cant go any higher than Y-coordinate = 270
									break;
								hand_y-=36 ;
								break;
					case SDLK_DOWN:
								if(hand_y == 342) //limits the cursor, cant go any lower than Y-coordinate = 342
									break;
								hand_y+=36 ;
								break;
					case SDLK_RETURN:
								if(hand_y == 270) //if cursor is pointing at Play
								{
								    Game();
									break;
								}
								if(hand_y == 306) //if cursor is pointing at Controls
								{
								    Controls();
									break;
								}

								if(hand_y == 342) //if cursor is pointing at Credits
								{
								    Credits();
									break;
								}
                    default: ;
				}
			}
		}
	}
}

void Game()
{
    int score = 0;

    /**** Setup the Rect objects ****/
    SDL_Rect Wall_Top;
    Wall_Top.x = 4;
    Wall_Top.y = 1;
    Wall_Top.h = 3;
    Wall_Top.w = 631;

    SDL_Rect Wall_Bot;
    Wall_Bot.x = 4;
    Wall_Bot.y = 476;
    Wall_Bot.h = 3;
    Wall_Bot.w = 631;

    SDL_Rect Wall_Left;
    Wall_Left.x = 0;
    Wall_Left.y = 5;
    Wall_Left.h = 470;
    Wall_Left.w = 3;

    SDL_Rect Wall_Right;
    Wall_Right.x = 636;
    Wall_Right.y = 5;
    Wall_Right.h = 470;
    Wall_Right.w = 3;

/**** Setup Class Objects and Event Structure ****/
    Setup SetupF;
    Food f;
    Snake sn;
    Timer fps;
	SDL_Event event;
    SetupF.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface* screen = SetupF.getscreen();

    /*** Load up images to SDL pointers ***/
	SDL_Surface* GameScreen = SetupF.load_image("gfx/GameScreen.png");
	SDL_Surface* Food = SetupF.load_image("gfx/Star.png");
	SDL_Surface* Snake = SetupF.load_image_wcolor("gfx/Snake.png", 0, 0xFF, 0xFF);
	SDL_Surface* Vwall = SetupF.load_image("gfx/Vwall.png");
	SDL_Surface* Hwall =SetupF.load_image("gfx/Hwall.png");

    /*** Load information to vector from file ***/
    ifstream load_file(FILENAME);
	vector<Surface> surfaces;
	if(load_file)
	{
		while(load_file)
		{
			char imageID;
			int x_pos, y_pos, height, width;
			load_file >> imageID >> x_pos >> y_pos >> height >> width;
			if(imageID == 'V' || imageID == 'H')
				surfaces.push_back(Surface(imageID, x_pos, y_pos, height, width));
		}
	}
	else
	{
		cout << "File " << FILENAME << "not found." << endl;
		exit(1);
	}
    /** end of loading in to vector **/

    /**** While loop checks for key inputs and collision detection ****/
	bool quit = false;
	while(quit == false)
	{
	    fps.start();
		while( SDL_PollEvent(&event))
        {
            switch( event.key.keysym.sym )
            {
                /** Key inputs for Directional change **/
                case SDLK_UP:
                            sn.change(0, -2);
                            break;
                case SDLK_DOWN:
                            sn.change(0, 2);
                            break;
                case SDLK_LEFT:
                            sn.change(-2, 0);
                            break;
                case SDLK_RIGHT:
                            sn.change(2, 0);
                            break;
                default : ;
            }
            if(event.type == SDL_QUIT)
            quit = true;
        }

    /** checks collions of player with Star **/
    if(check_collision(sn.check2(), f.check1()))
    {
        f.newFood();
        score++;
    }

    /** checks collision on the 4 walls of the screen **/
    if(check_collision(sn.check2(), Wall_Top) || check_collision(sn.check2(), Wall_Bot) || check_collision(sn.check2(), Wall_Right) || check_collision(sn.check2(), Wall_Left))

    {
        score = 0;
        GameOver();
    }

    /** check collision of the player with walls **/
    bool col = false;
    for(unsigned int poss = 0; poss < surfaces.size(); poss++) 	{
        col = check_collision(sn.check2(), surfaces.at(poss).get_rect());
        if(col == true)
        {
            score = 0;
            GameOver();
        }
	}

    /** check if any of the loaded walls are overlapping with the Star **/
    bool foodcheck = false;
    for(unsigned int poss = 0; poss < surfaces.size(); poss++)
    {
        foodcheck = check_collision(f.check1(), surfaces.at(poss).get_rect());
        if(foodcheck == true)
            f.newFood();
    }

    /*** Applying images to the screen ***/
    SetupF.apply_surface(0, 0, GameScreen, screen);
    for(unsigned int pos = 0; pos < surfaces.size(); pos++) //prints the images to screen using the data from vector
	{
	    if(surfaces.at(pos).get_imageID() == 'V')
            SetupF.apply_surface(surfaces.at(pos).get_x_pos(), surfaces.at(pos).get_y_pos(), Vwall, screen);
        if(surfaces.at(pos).get_imageID() == 'H')
            SetupF.apply_surface(surfaces.at(pos).get_x_pos(), surfaces.at(pos).get_y_pos(), Hwall, screen);
	}

	SetupF.apply_surface(f.Get_food_x(), f.Get_food_y(), Food, screen);
	sn.move();
	SetupF.apply_surface(sn.get_x(), sn.get_y(), Snake , screen);

    /** Keeps track of score on the window **/
    stringstream caption;
    caption << "Score: " << score;
    SDL_WM_SetCaption( caption.str().c_str(), NULL );

    /** capping frames per second **/
    if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );

    /** Update the screen **/
	SetupF.update_screen();
	}

    /** Shut off SDL and deallocate images **/
	SetupF.clean_up();
}

void GameOver()
{
	Setup SetupF;
	SDL_Event event;
    SetupF.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface* screen = SetupF.getscreen();
	SDL_Surface* Hand = SetupF.load_image_wcolor("gfx/pointer.png", 0, 0xFF, 0xFF);
	SDL_Surface* GameOver = SetupF.load_image("gfx/GameOver.png");
	int y_pos = 313; //Y-coordinate of crusor

	bool Devin_Is_Quiet = false; //Devin you're never quiet Lol jk jk
	while (Devin_Is_Quiet == false)
	{
	    /** Apply images to screen and check for key inputs **/
		SetupF.apply_surface(0, 0, GameOver, screen);
		SetupF.apply_surface(249, y_pos, Hand, screen);
		SetupF.update_screen();
		while( SDL_PollEvent(&event))
		{
			if( event.type == SDL_QUIT ) //quit
				SetupF.clean_up();
            else if(event.type == SDL_KEYDOWN)
            {
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP: y_pos = 313; break;
                    case SDLK_DOWN: y_pos = 343; break;
                    case SDLK_RETURN:
                                if(y_pos == 313)
                                {
                                    Game(); //play again
                                    break;
                                }

                                if(y_pos == 343)
                                {
                                    Menu(); //quit to menu
                                    break;
                                }
                    default: ;
                }
            }
		}
	}
}

void Controls()
{
	SDL_Event event;
	Setup SetupF;
    SetupF.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface* screen = SetupF.getscreen();
	SDL_Surface* background = SetupF.load_image("gfx/bkground.png");
	SDL_Surface* GameTitle = SetupF.load_image_wcolor("gfx/Controls.png", 0, 0xFF, 0xFF);
	SDL_Surface* Back = SetupF.load_image("gfx/Back.png");

	SDL_Rect button;
	button.x = 517;
	button.y = 437;
	button.h = 43;
	button.w = 123;
	int mouse_x = 0;
	int mouse_y = 0;

	bool tempx = false;
	while(tempx == false)
	{
		SetupF.apply_surface( 0, 0, background, screen);
		SetupF.apply_surface( 0, 0, GameTitle, screen);
		SetupF.apply_surface(517, 437, Back, screen);
		SetupF.update_screen();

		while( SDL_PollEvent(&event))
		{
            if(event.type == SDL_QUIT)
				SetupF.clean_up();
            if(event.type == SDL_MOUSEBUTTONDOWN) //check if mouse is pressed
            {
                if( event.button.button == SDL_BUTTON_LEFT ) //if mouse left key is pressed
                {
                    mouse_x = event.motion.x; //set mouse's x coord
                    mouse_y = event.motion.y;// set mouse's y coord
                    if( ( mouse_x > button.x ) && ( mouse_x < button.x + button.w ) && ( mouse_y > button.y ) && ( mouse_y < button.y + button.h ) ) //check if mouse crusor is over the button
                    {
                        Menu(); //back to menu
                        break;
                    }
                }
            }
		}
	}
}

void Credits()
{
	SDL_Event event;
	Setup SetupF;
    SetupF.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface* screen = SetupF.getscreen();
	SDL_Surface* background = SetupF.load_image("gfx/bkground.png");
	SDL_Surface* GameTitle = SetupF.load_image_wcolor("gfx/Credits.png", 0xFF, 0xFF, 0xFF);
	SDL_Surface* Back = SetupF.load_image("gfx/back.png");

	SDL_Rect button;
	button.x = 517;
	button.y = 437;
	button.h = 43;
	button.w = 123;
	int mouse_x = 0;
	int mouse_y = 0;

	bool tempx = false;
	while(tempx == false)
	{
		SetupF.apply_surface( 0, 0, background, screen);
		SetupF.apply_surface( 0, 0, GameTitle, screen);
		SetupF.apply_surface(517, 437, Back, screen);
		SetupF.update_screen();

		while( SDL_PollEvent(&event))
		{
            if(event.type == SDL_QUIT)
				SetupF.clean_up();
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                    if( ( mouse_x > button.x ) && ( mouse_x < button.x + button.w ) && ( mouse_y > button.y ) && ( mouse_y < button.y + button.h ) )
                    {
                        Menu(); //back to menu
                        break;
                    }
                }
            }
		}
	}
}

/** Collision detection function **/
bool check_collision( SDL_Rect A, SDL_Rect B ) //takes in 2 rect objects as argument
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    /** sets the dimensions for object A and B **/
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    /** Check if any part of the object is overlapping **/
    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
    {
        return false;
    }
    return true;
}
