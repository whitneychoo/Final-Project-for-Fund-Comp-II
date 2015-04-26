#include "base.h"
#ifndef WHITNEY_H
#define WHITNEY_H
using namespace std;
//Current displayed texture
//LTexture fTexture;
LTexture fTexture;
class Whitney : public base {
	public: 
	void playGame();
	virtual bool loadMusic();
};

bool Whitney::loadMusic(){
	bool success = true;
//Load music
    gMusic = Mix_LoadMUS( "beat.wav" );
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
		if( !fTexture.loadMedia("scene1JY.png") && !loadMusic() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			loadMusic();
			Mix_PlayMusic(gMusic, -1);
			//Apply the image
				SDL_RenderClear( gRenderer );
				fTexture.render(0,0);
				//Render texture to screen
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
									fTexture.loadMedia("scene1JY.png");
									if((x < 320) && (y < 240)){
										fTexture.loadMedia("cats.jpg");	
									}
									else if((x < 320) && (y > 240)){
										fTexture.loadMedia("scene3JY.png");
										scenario = 2;
									}
									break;
								case 2:	
									fTexture.loadMedia("books.bmp");
									Mix_HaltMusic();
									scenario = 3;	
									break;	
								case 3:
									SDL_Delay(2000);
									quit = true;
									break;
						}
				SDL_RenderClear( gRenderer );
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				fTexture.setWidth(SCREEN_WIDTH);
				fTexture.setHeight(SCREEN_HEIGHT);
				//Render texture to screen
				fTexture.render(0, 0);
				//Update screen
				SDL_RenderPresent( gRenderer );
					}
				}
			}


	}
}
#endif
