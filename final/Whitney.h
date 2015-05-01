#include "base.h"
#include "WhitDot.h"
#include "LTimer.h"
#include "TextTexture.h"
#ifndef WHITNEY_H
#define WHITNEY_H
using namespace std;

//Current displayed texture
WhitDot whitdot;	// the pokemon for the mini game

LTimer wTimer;		// timer
LTexture fTexture;	// background texture
//Rendered texture
TextTexture fTextTexture;
class Whitney : public base {
public: 
	int playGame();
	virtual bool loadMusic();

private:
	int pokemon;
};

bool Whitney::loadMusic(){
	bool success = true;
	//Load music
	gMusic = Mix_LoadMUS( "pokemon.mp3" );
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	} 
	return success;
}

int Whitney::playGame() 
{
	int win = 0;
	int count = 1;
	int scenario = 1;
	bool mgPlay = false;
	//Load media

	if(!fTexture.loadMedia("pokemongrass.png") && !loadMusic() )
		printf( "Failed to load media!\n" );
	else{
		SDL_Rect wall, block, obstacle, thing, stuff;	// all the obstacles in the minigame
		wall.x = 100;
		wall.y = 0;
		wall.w = 40;
		wall.h = 200;

		obstacle.x = 200;
		obstacle.y = 340;
		obstacle.w = 40;
		obstacle.h = 100;

		thing.x = 300;
		thing.y = 0;
		thing.w = 40;
		thing.h = 400;

		block.x = 400;
		block.y = 200;
		block.w = 40;
		block.h = 100;

		stuff.x = 500;
		stuff.y = 100;
		stuff.w = 40;
		stuff.h = 380;


		//Apply the image
		SDL_RenderClear( gRenderer );
		//Render texture to screen
		//gTexture.render(0, 0);
		//Update screen
		SDL_RenderPresent( gRenderer );
		fTextTexture.loadFile("bebas.ttf");	// load font
		bool quit = false;
		loadMusic();						// play the music
		Mix_PlayMusic(gMusic, -1);
		SDL_Event e;
		while(!quit){						// if didnt exit window
			while(SDL_PollEvent(&e) !=0 || count){
				if(e.type == SDL_QUIT)
					quit = true;
				else if(e.type == SDL_MOUSEBUTTONDOWN && !mgPlay || count){
					//Clear Screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear(gRenderer);
					
					int x, y;
					if(!count){
					SDL_GetMouseState(&x, &y);
					switch(scenario){
						case 1:						// pokemon grass scene
							if(y < 125 && x > 200 && x < 400)
								scenario = 2;		// wild rattata
							else if(y > 240 && x < 320)
								scenario = 3;		// pokecenter
							break;
						case 2:						// wild rattata scene
							if( y > 330 && x > 330 && x < 500 && y < 400)
								scenario = 5;		// fight
							else if( y > 400 && x > 500)
								scenario = 4;		// flee
							break;
						case 3:						// pokecenter
							if(y > 300 && x < 213){
								scenario = 6;		// bulbasaur
								pokemon = 1;
							}else if(y > 300 && x > 213 && x < 426){
								scenario = 6;		// charmander
								pokemon = 2;
							}else if(y > 300 && x > 426){
								scenario = 6;		// squirtle
								pokemon = 3;
							}break;
						case 4:						// you throw berry scene
							scenario = 12;			// you die
							break;
						case 5:
							scenario = 1;			// you survive
							break;
						case 6:						// gary wants to fight scene
							if( y > 330 && x > 330 && x < 500 && y < 400)	
								scenario = 13;		// fight
							else if( y > 400 && x > 500)	
								scenario = 8;		// flee
							break;

						case 7:						// you win
							scenario = 9;								
							break;
						case 8:						// you lose/die
							scenario = 12;
							break;
						case 9:						// you win the mini game
							scenario = 10;			
							break;
						case 10:				// to close window
							break;
						case 11:				// go to minigame
							break;
						case 12:				// game over scene
							scenario = 10;
							break;	
						case 13:				// to display instructions
							scenario = 11;
					}//end switch
					}
					//Scene Choice
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
						case 10: 
							return win;				// return whether or not player died
							quit = true;			// in this level or not.. & exit screen
							break;
						case 11:
						
							fTexture.setAlpha(0);
							if(pokemon == 1){	// pokemon selection
								whitdot.loadMedia("bulbasaur.png");
							} else if(pokemon == 2){
								whitdot.loadMedia("charmander.png");
							} else if(pokemon == 3){
								whitdot.loadMedia("squirtle.png");
							}
							mgPlay = true;
							break;	
						case 12: 
							fTexture.loadMedia("gameover.jpg");
							break;
						case 13:
							fTexture.loadMedia("fight.png");
							break;

					}
					//Scene Draw
					//stretch backgrounds
					fTexture.setWidth(SCREEN_WIDTH);
					fTexture.setHeight(SCREEN_HEIGHT);
					//Draw textures
					fTexture.render(0,0);
					
					//Scene Text Draw
					switch(scenario){
						case 1:
							//Story
							fTextTexture.loadColors(255, 255, 255);
							fTextTexture.loadMedia("You have just entered the Pokemon world,");
							fTextTexture.render(0, 0);
							fTextTexture.loadMedia("slightly injured from your travels.");
							fTextTexture.render(0,20);
							fTextTexture.loadMedia("Click the patch of grass south west ");
							fTextTexture.render(0, 40);
							fTextTexture.loadMedia("to head to the nearest pokemon center.");
							fTextTexture.render(0, 60);
							fTextTexture.loadMedia("Click the flowers to lay down and rest."); 
							fTextTexture.render(0, 80);
							fTextTexture.loadColors(55, 3, 64);
							
							break;		
						case 2:
							
							//Story
							fTextTexture.loadMedia("You are awaken by a wild Rattata. Fight or Run?"); 
							fTextTexture.render(0, 0);
							
							break;	
						case 3:
							//Story
							fTextTexture.loadMedia("You arrive at the Pokemon Center and are healed immediately");
							fTextTexture.render(0, 0);
							fTextTexture.loadMedia("Professor Oak greets you and offers you the choice of 3 Pokemon");
							fTextTexture.render(0, 20);
							fTextTexture.loadMedia("to accompany you on your travels."); 
							fTextTexture.render(0, 40);
							fTextTexture.loadMedia("Choose your Pokemon!");
							fTextTexture.render(0, 60);
							break;	
						case 4:			
							//Story
							fTextTexture.loadMedia("You cannot flee!!");
							fTextTexture.render(0, 0);
					
							break;		
						case 5:
							//Story
							fTextTexture.loadMedia("You find some oran berries in your pocket!");
							fTextTexture.render(0, 0);
							break;	
						case 6:
							//Story
							fTextTexture.loadMedia("As you head north, you encounter an annoying punk...");
							fTextTexture.render(0, 0);

							break;	
						case 7:
							//Story
							fTextTexture.loadMedia("Wow you just won your first Pokemon Battle!");
							fTextTexture.render(0, 0);
							break;	
						case 8:
							//Story
							fTextTexture.loadMedia("You decide to chicken out ...");
							fTextTexture.render(0, 0);
							break;	
						case 9:			
							//Story
							fTextTexture.loadMedia("Impressed, Gary provides you with the directions ");
							fTextTexture.render(0, 0);
							fTextTexture.loadMedia("to move on to the next world");
							fTextTexture.render(0, 20);
							
							break;
						case 10:
							break;
						case 11:
							break;		
						case 12:
							break;
						case 13:
							fTextTexture.loadMedia("You have ten seconds to get to the other ");
							fTextTexture.render(0, 0);
							fTextTexture.loadMedia("side of the screen. Click to continue!");
							fTextTexture.render(0, 20);
							break;
					}
					count = 0;
					SDL_RenderPresent(gRenderer);
				}//mouse down event	
				if(mgPlay){
					if(!wTimer.isStarted()){		// if didnt start timer start it now
						wTimer.start();
					}
					
					
					if(whitdot.move(wall, block, obstacle, thing, stuff)){		
						win = 1;		// player won minigame = won level
						scenario = 9;		// display the new screen
						fTexture.loadMedia("map.png");
			

						fTexture.setAlpha(255);
						whitdot.setAlpha(0);
						mgPlay = false;
						wTimer.stop();
						count = 1;
					} 
					else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){	
						whitdot.handleEvent(e);
					}				
				}//if minigame is being played
			}//while there is an event
			
			if(mgPlay){
				if(wTimer.getTicks() > 11000){	// if more than 11 secs --> die
					scenario = 10;				// display gameover and quit
					fTexture.loadMedia("gameover.jpg");
					fTexture.setAlpha(255);
					whitdot.setAlpha(0);
					mgPlay = false;
					wTimer.stop();
					count = 1;
				}

				//Clear Screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear(gRenderer);
				whitdot.render();
				//Update screen
				

        			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );        
           	 		SDL_RenderFillRect( gRenderer, &wall );
					SDL_RenderFillRect( gRenderer, &block );
           	 		SDL_RenderFillRect( gRenderer, &thing );
					SDL_RenderFillRect( gRenderer, &obstacle );
					SDL_RenderFillRect( gRenderer, &stuff );
					SDL_RenderPresent(gRenderer);

			}
		}//while quit is not true
	}
	fTexture.free();
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
}

//The whitdot that will move around on the screen
#endif