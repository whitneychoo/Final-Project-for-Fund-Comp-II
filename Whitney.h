#include "base.h"
#include "Dot.h"
#include "LTimer.h"
#ifndef WHITNEY_H
#define WHITNEY_H
using namespace std;

//Current displayed texture
//Dot dot(0, 0);
//Dot otherDot(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//LTimer timer;
LTexture fTexture;
class Whitney : public base {
public: 
	void playGame();
	virtual bool loadMusic();
};

bool Whitney::loadMusic(){
	bool success = true;
	//Load music
	gMusic = Mix_LoadMUS( "httyd.mp3" );
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
//	bool mgPlay = false;
	//Load media
	if(!fTexture.loadMedia("pokemongrass.png") && !loadMusic())
		printf( "Failed to load media!\n" );
	else{
		//Apply the image
		SDL_RenderClear( gRenderer );
		//Render texture to screen
		fTexture.render(0, 0);
		//Update screen
		SDL_RenderPresent( gRenderer );
		bool quit = false;
		cout << "should play music" << endl;
		loadMusic();
		Mix_PlayMusic(gMusic, -1);
		SDL_Event e;
		while(!quit){
			while(SDL_PollEvent(&e) !=0){
				if(e.type == SDL_QUIT)
					quit = true;
				else if(e.type == SDL_MOUSEBUTTONDOWN){
					int x, y;
					SDL_GetMouseState(&x, &y);
					switch(scenario){
						case 1:						// pokemon grass scene
							if((y < 320))
								scenario = 2;		// wild rattata
							else if(y > 320)
								scenario = 3;		// pokecenter
							break;
						case 2:						// wild rattata scene
							if((y < 320))	
								scenario = 4;		// fight
							else if(y > 320)
								scenario = 5;		// flee
							break;
						case 3:						// pokecenter
							if((x < 160))
								scenario = 6;		// bulbasaur
							else if((x < 320 && x > 160))
								scenario = 6;		// charmander
							else if(x > 320)
								scenario = 6;		// squirtle
							break;
						case 4:						// you throw berry scene
						scenario = 1;			// return to pokemon grass scene
							break;
						case 5:
							scenario = 1;			// you supposed to die here
							break;
						case 6:						// gary wants to fight scene
							if((y < 320))	
								scenario = 7;		// fight
							else if(y < 320)
								scenario = 8;		// flee
							break;

						case 7:						// you win
							scenario = 9;								
							break;
						case 8:						// you lose/die
							scenario = 1;
							break;
						case 9:
							scenario = 1;
							break;

					}//end switch
					switch(scenario){
						case 1:
							fTexture.loadMedia("pokemongrass.png");
							break;		
						case 2:
							fTexture.loadMedia("wildrattata.png");
							break;	
						case 3:
							fTexture.loadMedia("choosepokemon.png");
							break;	
						case 4:
							fTexture.loadMedia("deadrat.png");
							break;	
						case 5:
							fTexture.loadMedia("berryescape.png");
							break;	
						case 6:
							fTexture.loadMedia("fight.png");
							break;	
						case 7:
							fTexture.loadMedia("garywin.png");
							break;	
						case 8:
							fTexture.loadMedia("battleforfeit.png");
							break;	
						case 9:
							fTexture.loadMedia("map.png");
							break;	
					}//end switch
				}//mouse down event
			}//while there are events
			//Clear Screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear(gRenderer);

			//stretch backgrounds
			fTexture.setWidth(SCREEN_WIDTH);
			fTexture.setHeight(SCREEN_HEIGHT);

			//Draw textures
			fTexture.render(0,0);
			//Update screen
			SDL_RenderPresent(gRenderer);
		}//while quit is not true
	}
	fTexture.free();
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
}

//The dot that will move around on the screen
#endif


