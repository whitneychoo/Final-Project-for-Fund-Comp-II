#ifndef JOSEPH_H
#define JOSEPH_H
#include "scenario.h"

class Joseph : public Scenario { //Joseph inherits from Scenario
	public:
		Joseph();//constructor
		int playLevel();
		void close(); //Frees media and shuts down SDL
		bool init(); //Starts up SDL and creates window
		bool loadMedia(char*); //Loads media






	protected:
	//Data Members
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;

};

#endif
