#include "base.h"
#ifndef JOSEPH_H
#define JOSEPH_H
using namespace std;
class Joseph : public base {
public: 
	void playGame();
	virtual bool loadMusic();
};

bool Joseph::loadMusic(){
	return true;
}

void Joseph::playGame() 
{
	int scenario = 1;
	//Load media
	if(!loadMedia("scene1JY.png") && !loadMusic())
		printf( "Failed to load media!\n" );
	else{
		//Apply the image
		SDL_RenderClear( gRenderer );
		//Render texture to screen
		SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
		//Update screen
		SDL_RenderPresent( gRenderer );
		bool quit = false;
		Mix_PlayMusic(gMusic, -1);
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
							if((y < 160))
								scenario = 2;
							else if((y < 320 && y > 160))
								scenario = 3;
							else if(y > 320)
								scenario = 4;
							break;
						case 2:	
							loadMedia("scene2JY.jpg");
							if((y < 160))
								scenario = 5;	
							else if((y < 320 && y > 160))
								scenario = 6;
							else if(y > 320)
								scenario = 7;
							break;	
						case 3:
							loadMedia("scene3JY.png");
							if((y < 160))
								scenario = 6;	
							else if((y < 320 && y > 160))
								scenario = 8;
							else if(y > 320)
								scenario = 9;
							break;
						case 4:
							loadMedia("scene4JY.jpg");
							if((y < 160))
								scenario = 2;	
							else if((y < 320 && y > 160))
								scenario = 6;
							else if(y > 320)
								scenario = 6;
							break;
						case 5:
							loadMedia("scene5JY.jpg");
							if((y < 160))
								scenario = 10;	
							else if((y < 320 && y > 160))
								scenario = 8;
							else if(y > 320)
								scenario = 6;
							break;
						case 6:
							loadMedia("scene1JY.png");
							if((y < 160))
								scenario = 2;	
							else if((y < 320 && y > 160))
								scenario = 3;
							else if(y > 320)
								scenario = 4;
							break;
						case 7:
							loadMedia("scene7JY.jpg");
							if((y < 160))
								scenario = 7;	
							else if((y < 320 && y > 160))
								scenario = 5;
							else if(y > 320)
								scenario = 6;
							break;
						case 8:
							loadMedia("scene8JY.png");
							if(y < 240)
								scenario = 6;	
							else if(y > 240)
								scenario = 9;
							break;
						case 9:
							loadMedia("scene9JY.jpg");
							if(y < 240)
								scenario = 3;	
							else if(y > 240)
								scenario = 10;
							break;
						case 10:
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
