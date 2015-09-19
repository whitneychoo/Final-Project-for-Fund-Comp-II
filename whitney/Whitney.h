#include "base.h"
#ifndef WHITNEY_H
#define WHITNEY_H
using namespace std;

class Whitney : public base {
	public: 
	void playGame();
	virtual bool loadMusic();
};

bool Whitney::loadMusic(){
	bool success = true;
//Load music
    gMusic = Mix_LoadMUS( "what.mp3" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    } 
	return success;

}

void Whitney::playGame() 
{
	int scenario = 1;

//Load media
		if( !loadMedia("scene1JY.png") && !loadMusic() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			cout << "what" << endl;
			Mix_PlayMusic(gMusic, -1);
			//Apply the image
				SDL_RenderClear( gRenderer );

				//Render texture to screen
				SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

				//Update screen
				SDL_RenderPresent( gRenderer );

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

						switch(scenario){
								case 1:
									loadMedia("scene1JY.png");
									if((x < 320) && (y < 240)){
										loadMedia("cats.jpg");	
									}
									else if((x < 320) && (y > 240)){
										loadMedia("scene3JY.png");
										scenario = 2;
									}
									break;
								case 2:	
									loadMedia("books.bmp");
									//Mix_HaltMusic();
									SDL_UpdateWindowSurface(gWindow);
									scenario = 3;	
									break;	
								case 3:
									SDL_Delay(2000);
									quit = true;
									break;
						}
				SDL_RenderClear( gRenderer );

				//Render texture to screen
				SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

				//Update screen
				SDL_RenderPresent( gRenderer );
					}
				}
			}


	}
}
#endif
