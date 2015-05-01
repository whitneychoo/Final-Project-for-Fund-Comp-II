/*Sam Cho, Whitney Choo, So Yon(Alli) Kwon, Joseph Yoon
*CSE 20212, Spring 2015
*Final Project
*How to Kill Harry Pokemon
*/

#include "joseph.h"
#include "Whitney.h"
#include "sam.h"
#include "So.h"
#include <iostream>
using namespace std;

int main( int argc, char* args[] ){
	
	//four different derived classes that are used to make a compilation scenario game
	Joseph joe;
	Whitney whit;
	sam samuel;
	So soyon;
	//Start up SDL and create window
	if( !joe.init())
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{	
		joe.playGame(); //cannot lose
		if(whit.playGame()){ //if lose then no more
			samuel.playGame();//cannot lose
			soyon.playGame();//can lose, shows whether game is won or not for last world
		}	
	}
	//close all games
	whit.close();
	joe.close();
	samuel.close();
	soyon.close();
}
