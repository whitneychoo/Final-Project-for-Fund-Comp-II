#include "ex.h"
#ifndef DERIVE_H
#define DERIVE_H
using namespace std;



class whitney : public whit {

	public: 
	whitney();

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia(std::string);

	//Frees media and shuts down SDL
	void close();

	void playGame() ;

private:

};


whitney::whitney() : whit() {

}

bool whitney::init()
{
	return whit::init();
}

bool whitney::loadMedia(std::string pic)
{
	//Loading success flag
	bool success = true;

	//Load splash image
    gHelloWorld = SDL_LoadBMP( pic.c_str() );
	if( gHelloWorld == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void whitney::close()
{
	whit::close();	
}

void whitney::playGame() 
{
//Load media
		if( !loadMedia("cats.bmp") )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{

			//Apply the image
			SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
			
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );

			bool quit = false;

			SDL_Event e;

			while(!quit){
				while(SDL_PollEvent(&e) !=0){
					if(e.type == SDL_QUIT){
						quit = true;
					}
					if(e.type == SDL_MOUSEBUTTONDOWN){
						int x, y;
						SDL_GetMouseState(&x, &y);

						if((x < 320) && (y < 240)){

							loadMedia("house.bmp");		
						}	

			//Apply the image
			SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
			
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );

					}
				}
			}


	}
}

#endif
