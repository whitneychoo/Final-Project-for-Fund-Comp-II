Base Class: Scenario
/* Samuel Cho, Whitney Choo, So Yon Kwon, Joseph Yoon -- Final Project -- (.h file)
Defines the functions used in this program to create a scenario based video game */

#ifndef SCENARIO_H
#define SCENARIO_H
#include <iostream>
#include <string>
#include <SDL2/SDL2.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* currentSurface = NULL;

/*Mix_Music *music = NULL;
Mix_Chunk *Scratch = NULL;
Mix_Chunk *High = NULL;
Mix_Chunk *Medium = NULL;
Mix_Chunk *Low = NULL;*/

class scenario
{
	public:
		//Constructor
		scenario();
		//Member Functions
		bool initialize();					//Starts up SDL & Creates window
		void setBackground(string);			//Sets up background
		void music(string);					//Sets up music
		void endGame();						//Ends the Game
		void levelUp(int);					//Changes the level
		void makeButtons();					//Create buttons
		void setCharacter(int x, int y);	//Position the character
		int playLevel();					//Play the level
		int playMinigame();					//Play the minigame

		//Load Individual Image
		SDL_Surface* loadSurface( std::string path );

		//Load Individual Image as Texture
		SDL_Texture* loadTexture( std:: string path );

	private:
		//Data Members
		
		
};



