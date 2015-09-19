

bool initialize(){
	//initialization flag
	bool success = true;

	if(SDL_Init( SDL_INIT_VIDEO /*| SDL_INIT_AUDIO */) < 0 ){
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		window = SDL_CreateWindow( "Scenario Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(window == NULL){
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			screenSurface = SDL_GetWindowSurface( window );
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF) );
			SDL_UpdateWindowSurface( window );
		}
	}
	
	return success;
}

SDL_Surface* setBackground( std::string path ){

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
