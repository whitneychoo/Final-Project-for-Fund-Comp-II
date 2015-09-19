#include "base.h"
#include "Dot.h"
#include "LTimer.h"
#ifndef JOSEPH_H
#define JOSEPH_H
using namespace std;

//Current displayed texture
Dot dot(0, 0);
Dot otherDot(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
LTimer timer;
LTexture gTexture;
//Rendered texture
LTexture gTextTexture;
class Joseph : public base {
public: 
	void playGame();
	virtual bool loadMusic();
};

bool Joseph::loadMusic(){
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

void Joseph::playGame() 
{
	int scenario = 1;
	bool mgPlay = false;
	//Load media
	if(!gTexture.loadMedia("scene1JY.png") && !loadMusic())
		printf( "Failed to load media!\n" );
	else{
		//Apply the image
		SDL_RenderClear( gRenderer );
		//Render texture to screen
		gTexture.render(0, 0);
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
				else if(e.type == SDL_MOUSEBUTTONDOWN && !mgPlay){
					int x, y;
					SDL_GetMouseState(&x, &y);
					switch(scenario){
						case 1:
							if((y < 160))
								scenario = 2;
							else if((y < 320 && y > 160))
								scenario = 3;
							else if(y > 320)
								scenario = 4;
							break;
						case 2:	
							if((y < 160))
								scenario = 5;	
							else if((y < 320 && y > 160))
								scenario = 6;
							else if(y > 320)
								scenario = 7;
							break;	
						case 3:
							if((y < 160))
								scenario = 6;	
							else if((y < 320 && y > 160))
								scenario = 11;
							else if(y > 320)
								scenario = 11;
							break;
						case 4:
							if((y < 160))
								scenario = 2;	
							else if((y < 320 && y > 160))
								scenario = 6;
							else if(y > 320)
								scenario = 6;
							break;
						case 5:
							if((y < 160))
								scenario = 10;	
							else if((y < 320 && y > 160))
								scenario = 8;
							else if(y > 320)
								scenario = 6;
							break;
						case 6:
							if((y < 160))
								scenario = 2;	
							else if((y < 320 && y > 160))
								scenario = 3;
							else if(y > 320)
								scenario = 4;
							break;
						case 7:
							if((y < 160))
								scenario = 7;	
							else if((y < 320 && y > 160))
								scenario = 5;
							else if(y > 320)
								scenario = 6;
							break;
						case 8:
							if(y < 240)
								scenario = 6;	
							else if(y > 240)
								scenario = 9;
							break;
						case 9:
							if(y < 240)
								scenario = 3;	
							else if(y > 240)
								scenario = 10;
							break;
						case 10:
							break;
						case 11://minigame case
							break;
					}//end switch
					switch(scenario){
						case 1:
							gTexture.loadMedia("scene1JY.png");
							break;		
						case 2:
							gTexture.loadMedia("scene2JY.jpg");
							break;	
						case 3:
							gTexture.loadMedia("scene3JY.png");
							break;	
						case 4:
							gTexture.loadMedia("scene4JY.jpg");
							break;	
						case 5:
							gTexture.loadMedia("scene5JY.jpg");
							break;	
						case 6:
							gTexture.loadMedia("scene1JY.png");
							break;	
						case 7:
							gTexture.loadMedia("scene7JY.jpg");
							break;	
						case 8:
							gTexture.loadMedia("scene8JY.png");
							break;	
						case 9:
							gTexture.loadMedia("scene9JY.jpg");
							break;
						case 10:
							quit = true;
						case 11:
							gTexture.setAlpha(0);
							dot.loadMedia("dot.bmp");
							mgPlay = true;
							break;		
					}
				}//mouse down event	
				if(mgPlay){
					if(!timer.isStarted()){
						timer.start();
					}
					int hit = dot.move(otherDot.getColliders());	
					if(timer.getTicks() > 10000){
						scenario = 8;
						gTexture.loadMedia("scene8JY.png");
						dot.reset();
						gTexture.setAlpha(255);
						gDotTexture.setAlpha(0);
						otherDot.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
						mgPlay = false;
						timer.stop();
					}
					else if(hit){
						scenario = 6;
						gTexture.loadMedia("scene1JY.png");
						dot.reset();
						otherDot.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
						gTexture.setAlpha(255);
						gDotTexture.setAlpha(0);
						mgPlay = false;
						timer.stop();
					} 
					else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){	
						dot.handleEvent(e);
					}				
				}//if minigame is being played
			}//while there is an event
			if(mgPlay && otherDot.randMove(dot.getColliders(), dot.getX(), dot.getY())){
					scenario = 6;
					gTexture.loadMedia("scene1JY.png");
					dot.reset();
					otherDot.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
					gTexture.setAlpha(255);
					gDotTexture.setAlpha(0);
					mgPlay = false;
					timer.stop();
			}//makes sure that otherdot continues to move even though player dot doesn't move during mini game	
			//Clear Screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear(gRenderer);

			//stretch backgrounds
			gTexture.setWidth(SCREEN_WIDTH);
			gTexture.setHeight(SCREEN_HEIGHT);

			//Draw textures
			gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
			gTexture.render(0,0);
			dot.render();
			otherDot.render();

			//Update screen
			SDL_RenderPresent(gRenderer);
		}//while quit is not true
	}
	gTexture.free();
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
}

//The dot that will move around on the screen
#endif


