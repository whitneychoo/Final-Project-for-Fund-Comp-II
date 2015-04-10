/* Samuel Cho, Whitney Choo, So Yon Kwon, Joseph Yoon -- Final Project -- (.h file)
Defines the functions used in this program to create a scenario based video game */

#ifndef SCENARIO_H
#define SCENARIO_H
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>

using namespace std;

class Scenario
{
	public:
		Scenario(); //Constructor
		int playLevel(); //Play the level

		//Member Functions
							//Starts up SDL & Creates window
/*		void setBackground(string);			//Sets up background
		void music(string);					//Sets up music
		void endGame();						//Ends the Game
		void levelUp(int);					//Changes the level
		void makeButtons();					//Create buttons
		void setCharacter(int x, int y);	//Position the character
*/		

		/*		int playMinigame();					//Play the minigame

		//Load Individual Image
		SDL_Surface* loadSurface( std::string path );

		//Load Individual Image as Texture
		SDL_Texture* loadTexture( std:: string path );
*/
	private:
		//Data Members
		
		
};
#endif
