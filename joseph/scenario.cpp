#include "scenario.h"

Scenario::Scenario(){
}
int Scenario::playLevel(){
	
	return 0;
}


/*SDL_Surface* setBackground( std::string path ){

	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL ){
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	} else {
		optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL);
		if(optimizedSurface == NULL){
			printf("unable to optimize image %s! SDL ERROR: %s\n", path.c_str(), SDL_GetError() );
		}
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

void endGame(){

	setBackground(		"game over image"			);

	//Apply the image
	SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
			
	//Update the surface
	SDL_UpdateWindowSurface( gWindow );	

	SDL_Delay ( 2000 );

	SDL_FreeSurface(currentSurface);
	currentSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

void levelUp(){

	setBackground(		"next level image"			);

	//Apply the image
	SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
			
	//Update the surface
	SDL_UpdateWindowSurface( gWindow );	

	SDL_Delay ( 2000 );

	SDL_FreeSurface(currentSurface);
	currentSurface = NULL;

}

	



void Scenario::setBackground(string){
	
}
*/
