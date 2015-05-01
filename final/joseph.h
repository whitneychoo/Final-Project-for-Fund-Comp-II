/*Sam Cho, Whitney Choo, So Yon(Alli) Kwon, Joseph Yoon
*CSE 20212, Spring 2015
*Final Project
*How to Kill Harry Pokemon
*/
#include "base.h"
#include "Dot.h"
#include "LTimer.h"
#include "TextTexture.h"
#ifndef JOSEPH_H
#define JOSEPH_H
using namespace std;

//Dots used for mini game
Dot hiccup(0, 0);
Dot fishlegs(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
Dot fishlegs2(SCREEN_WIDTH/4, SCREEN_HEIGHT/4);
Dot goblet(590, 430);
//timer used for mini game
LTimer timer;
//background texture
LTexture joeTexture;
//button textures
LTexture choice;
//text texture
TextTexture joeTextTexture;
class Joseph : public base { //extends base class
public: 
	int playGame(); //plays the game
	bool loadMusic(); //loads the music
};

//loads music
bool Joseph::loadMusic(){
	bool success = true;
	//Load music
	gMusic = Mix_LoadMUS( "httyd.mp3" ); //how to train your dragon music
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	} 
	return success;
}

//joseph yoons play game function
int Joseph::playGame() 
{
	int count = 1; //used for mini game to make sure that program doesnt re-enter and change background
	int scenario = 1;//scenario variable to keep track of where in the game the user is
	bool mgPlay = false; //mini-game play variable
	//load the media
	if(!joeTexture.loadMedia("scene1JY.png") && !loadMusic())
		printf( "Failed to load media!\n" );
	else{
		//Clear the renderer
		SDL_RenderClear( gRenderer );
		//Update screen
		SDL_RenderPresent( gRenderer );
		bool quit = false; //variable to quit the game
		loadMusic(); //load music
		Mix_PlayMusic(gMusic, -1); //play music
		SDL_Event e; //sdl event variable
		joeTextTexture.loadFile("ironbrine.ttf"); //load the font file
		joeTextTexture.loadColors(255, 255, 255); //make all font white
		while(!quit){ //while the program shouldn't quit 
			while(SDL_PollEvent(&e) !=0 || count){ //while there is an event or the mini game is not being played
				if(e.type == SDL_QUIT) //if we hit the x button in the corner, quit
					quit = true; 
				else if(e.type == SDL_MOUSEBUTTONDOWN && !mgPlay || count){ //else if we hit the mouse & not mini game or count
					//Clear Screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear(gRenderer);
					int x, y; //mouse location
					if(!count){ //if count = 0
					SDL_GetMouseState(&x, &y); //get the mouse location
					switch(scenario){ //choose which scene to go to depending on mouse click
						case 1: //all locations are similar and scenes vary on programmers choice where to go
							if(x <= 40 && x >= 10 && y >= 340 && y <= 370)
								scenario = 2;
							else if(x <= 40 && x >= 10 && y >= 380 && y <= 410)
								scenario = 3;
							else if(x <= 40 && x >= 10 && y >= 420 && y <= 450)
								scenario = 4;
							break;
						case 2:	
							if(x <= 40 && x >= 10 && y >= 340 && y <= 370)
								scenario = 5;	
							else if(x <= 40 && x >= 10 && y >= 380 && y <= 410)
								scenario = 6;
							else if(x <= 40 && x >= 10 && y >= 420 && y <= 450)
								scenario = 7;
							break;	
						case 3:
							if(x <= 40 && x >= 10 && y >= 340 && y <= 370)
								scenario = 6;	
							else if(x <= 40 && x >= 10 && y >= 380 && y <= 410)
								scenario = 12;
							else if(x <= 40 && x >= 10 && y >= 420 && y <= 450)
								scenario = 12;
							break;
						case 4:
							if(x <= 40 && x >= 10 && y >= 340 && y <= 370)
								scenario = 2;	
							else if(x <= 40 && x >= 10 && y >= 380 && y <= 410)
								scenario = 6;
							else if(x <= 40 && x >= 10 && y >= 420 && y <= 450)
								scenario = 6;
							break;
						case 5:
							if(x <= 595 && x >= 578  && y >= 434 && y <= 450)
								scenario = 10;	
							else if(x <= 620 && x >= 10 && ((y >= 342 && y <= 357) || ( y >= 373 && y <= 390)))
								scenario = 8;
							else if(x <= 620 && x >= 10 && ((y >= 404 && y <= 418) || ( y >= 434 && y <= 448)))
								scenario = 6;
							break;
						case 6:
							if(x <= 40 && x >= 10 && y >= 340 && y <= 370)
								scenario = 2;	
							else if(x <= 40 && x >= 10 && y >= 380 && y <= 410)
								scenario = 3;
							else if(x <= 40 && x >= 10 && y >= 420 && y <= 450)
								scenario = 4;
							break;
						case 7:
							if(x <= 40 && x >= 10 && y >= 340 && y <= 370)
								scenario = 7;	
							else if(x <= 40 && x >= 10 && y >= 380 && y <= 410)
								scenario = 5;
							else if(x <= 40 && x >= 10 && y >= 420 && y <= 450)
								scenario = 6;
							break;
						case 8:
							if(x <= 40 && x >= 10 && y >= 340 && y <= 370)
								scenario = 6;	
							else if(x <= 40 && x >= 10 && y >= 380 && y <= 410)
								scenario = 9;
							break;
						case 9:
							if(x <= 40 && x >= 10 && y >= 340 && y <= 370)
								scenario = 3;	
							else if(x <= 40 && x >= 10 && y >= 380 && y <= 410)
								scenario = 10;
							break;
						case 10:
							scenario = 13;
							break;
						case 11://minigame case - goes nowhere, playing mini game
							break;
						case 12:
							scenario = 11;
							break;
						}//end switch
					}//count == 0
					//load media for the scenes 
					switch(scenario){
						case 1:
							joeTexture.loadMedia("scene1JY.png");
							break;		
						case 2:
							joeTexture.loadMedia("scene2JY.jpg");
							break;	
						case 3:
							joeTexture.loadMedia("scene3JY.png");
							break;	
						case 4:
							joeTexture.loadMedia("scene4JY.jpg");
							break;	
						case 5:
							joeTexture.loadMedia("scene5JY.jpg");
							break;	
						case 6:
							joeTexture.loadMedia("scene1JY.png");
							break;	
						case 7:
							joeTexture.loadMedia("scene7JY.jpg");
							break;	
						case 8:
							joeTexture.loadMedia("scene8JY.png");
							break;	
						case 9:
							joeTexture.loadMedia("scene9JY.jpg");
							break;
						case 10:
							joeTexture.loadMedia("scene10JY.png");
							break;
						case 11://mini game case
							joeTexture.setAlpha(0); //set background to transparent
							hiccup.loadMedia("hiccuphead.png");
							fishlegs.loadMedia("fishlegshead.png");
							fishlegs2.loadMedia("fishlegshead.png");
							goblet.loadMedia("goblet.png");
							mgPlay = true; //mini game is set to be played
							break;	
						case 12:
							joeTexture.loadMedia("scene3JY.png");
							break;
						case 13:
							quit = true; //game will close
							break;
					}
					//stretch backgrounds
					joeTexture.setWidth(SCREEN_WIDTH);
					joeTexture.setHeight(SCREEN_HEIGHT);
					//Draw background
					joeTexture.render(0,0);
					//choose which scenarios have the buttons
					if(scenario != 5 && scenario != 11 && scenario != 12 && scenario !=10){
						choice.loadMedia("bluesquare.png");
						choice.render(10, 340);
						choice.render(10, 380);
						//these scenarios dont have the third button
						if(scenario != 8 && scenario != 9 && scenario != 12 && scenario != 10)
						choice.render(10, 420);	
					}
					//render the texts onto screen
					switch(scenario){
						case 1:
							//Story
							joeTextTexture.loadMedia("You wake up to Toothless (your dragon) licking your face. The roosters are"); 
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("crowing and the Isle of Berk is waking up. It's finally the day of your");
							joeTextTexture.render(0, 20);
							joeTextTexture.loadMedia("birthday and a well-deserved rest day from all the exploration trips your"); 
							joeTextTexture.render(0, 40);
							joeTextTexture.loadMedia("dad has been sending you on. You eat the special birthday breakfast on your");
							joeTextTexture.render(0, 60);
							joeTextTexture.loadMedia("bedside table and decide what to do now... ");
							joeTextTexture.render(0, 80);
							
							//Choices
							joeTextTexture.loadMedia("Rest a bit more from your week long journey of mapping unexplored");
							joeTextTexture.render(50, 340);
							joeTextTexture.loadMedia("lands and return to that awesome dream.");
							joeTextTexture.render(80, 360);
							joeTextTexture.loadMedia("Start your day early with coffee made from the new coffee beans");
							joeTextTexture.render(50, 380);
							joeTextTexture.loadMedia("your brought back from journey and relax with Toothless.");
							joeTextTexture.render(80, 400);
							joeTextTexture.loadMedia("Go find Astrid (your significant other), and hurry over to the");
							joeTextTexture.render(50, 420);
							joeTextTexture.loadMedia("best cliff to watch the sunrise.");
							joeTextTexture.render(80, 440);
							break;		
						case 2:
							//Story
							joeTextTexture.loadMedia("Everyone is bustling around Berk. What do you want to do?"); 
							joeTextTexture.render(0, 0);
							
							//Choices
							joeTextTexture.loadMedia("Go to the local tavern to see who's around.");
							joeTextTexture.render(50, 340);
							joeTextTexture.loadMedia("Hide under your blanket because the sun is too bright and fall back asleep.");
							joeTextTexture.render(50, 380);
							joeTextTexture.loadMedia("Go for a quick flight with Toothless.");
							joeTextTexture.render(50, 420);
							break;	
						case 3:
							//Story
							joeTextTexture.loadMedia("You feel energized and race Toothless to the harbor because you want to");
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("see the fisherman. On the way there, you see your good friend Fishlegs.");
							joeTextTexture.render(0, 20);
							joeTextTexture.loadMedia("He calls out to you as you're getting closer and asks if you want to"); 
							joeTextTexture.render(0, 40);
							joeTextTexture.loadMedia("play a quick game of Dragon Cup.");
							joeTextTexture.render(0, 60);
							
							//Choices
							joeTextTexture.loadMedia("Continue to run by him because now Toothless has gained a");
							joeTextTexture.render(50, 340);
							joeTextTexture.loadMedia("lead on you!");
							joeTextTexture.render(80, 360);
							joeTextTexture.loadMedia("Stop and play a quick game of Dragon Cup.");
							joeTextTexture.render(50, 380);
							joeTextTexture.loadMedia("Steal Fishlegs' helmet and continue to run.");
							joeTextTexture.render(50, 420);
							break;	
						case 4:			
							//Story
							joeTextTexture.loadMedia("You're at the cliff with Astrid. The sunrise is awesome. Best decision to");
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("start your day off with spending time with her. What move to make next..?");
							joeTextTexture.render(0, 20);

							//Choices
							joeTextTexture.loadMedia("Take a quick nap with Astrid.");
							joeTextTexture.render(50, 340);
							joeTextTexture.loadMedia("Ask Astrid to marry you.");
							joeTextTexture.render(50, 380);
							joeTextTexture.loadMedia("Challenge Astrid to a race around Berk with their dragons.");
							joeTextTexture.render(50, 420);
							break;		
						case 5:
							//Story
							joeTextTexture.loadMedia("For some reason, there's not that many people at the tavern. Well, there's");
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("a person you haven't seen before. Being the son of the chieftain and all,");
							joeTextTexture.render(0, 20);
							joeTextTexture.loadMedia("you go and introduce yourself. 'I'm Hiccup. What's your name?' The person"); 
							joeTextTexture.render(0, 40);
							joeTextTexture.loadMedia("looks at you and asks you to choose a number between 1 and 100.");
							joeTextTexture.render(0, 60);

							//Choices
							joeTextTexture.loadMedia("1    2   3   4   5   6   7   8   9   10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25");
							joeTextTexture.render(10, 340);
							joeTextTexture.loadMedia("26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50");
							joeTextTexture.render(10, 370);
							joeTextTexture.loadMedia("51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75");
							joeTextTexture.render(10, 400);
							joeTextTexture.loadMedia("76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100");
							joeTextTexture.render(10, 430);
							break;	
						case 6:
							//Story
							joeTextTexture.loadMedia("You wake up to Toothless licking your face. Well, this seems familiar. The");
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("roosters are crowing and Berk is waking up. You see the special birthday");
							joeTextTexture.render(0, 20);
							joeTextTexture.loadMedia("cake again. You definitely remember eating the cake yesterday and all of"); 
							joeTextTexture.render(0, 40);
							joeTextTexture.loadMedia("the activities before...What does this mean? Well, what to do now?");
							joeTextTexture.render(0, 60);

							//Choices
							joeTextTexture.loadMedia("Rest a bit more from your week long journey of mapping unexplored");
							joeTextTexture.render(50, 340);
							joeTextTexture.loadMedia("lands and return to that awesome dream.");
							joeTextTexture.render(80, 360);
							joeTextTexture.loadMedia("Start your day early with coffee made from the new coffee beans");
							joeTextTexture.render(50, 380);
							joeTextTexture.loadMedia("you brought back from journey and relax with Toothless.");
							joeTextTexture.render(80, 400);
							joeTextTexture.loadMedia("Go find Astrid (your significant other), and hurry over to the");
							joeTextTexture.render(50, 420);
							joeTextTexture.loadMedia("best cliff to watch the sunrise.");
							joeTextTexture.render(80, 440);
							break;	
						case 7:
							//Story
							joeTextTexture.loadMedia("It's such a beautiful day, but you can't spend your whole day in the air");
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("...or you can.");
							joeTextTexture.render(0, 20);

							//Choices
							joeTextTexture.loadColors(0, 0, 0);
							joeTextTexture.loadMedia("Stay in the air.");
							joeTextTexture.render(50, 340);
							joeTextTexture.loadMedia("Go back to town and visit the tavern.");
							joeTextTexture.render(50, 380);
							joeTextTexture.loadMedia("Jump from Toothless to test his quickness because you know");
							joeTextTexture.render(50, 420);
							joeTextTexture.loadMedia("he'll catch you.");
							joeTextTexture.render(80, 440);
							joeTextTexture.loadColors(255, 255, 255);
							break;	
						case 8:
							//Story
							joeTextTexture.loadMedia("You are given Fishlegs' helmet as a prize. You always wonder how such a");
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("small helmet could fit on such a big head. He asks if you'd like a drink");
							joeTextTexture.render(0, 20);
							joeTextTexture.loadMedia("at the tavern.");
							joeTextTexture.render(0, 40);
							//Choices
							joeTextTexture.loadMedia("Why not? Relaxing day. A few drinks won't hurt.");
							joeTextTexture.render(50, 340);
							joeTextTexture.loadMedia("A beautiful fish-smelling harbor awaits.");
							joeTextTexture.render(50, 380);
							break;	
						case 9:			
							//Story
							joeTextTexture.loadColors(0, 0, 0);
							joeTextTexture.loadMedia("As you're walking away, there's a helmet in your hands and you see a young");
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("kid acting like a future viking in training.");
							joeTextTexture.render(0, 20);
							
							//Choices
							joeTextTexture.loadMedia("Give her the helmet. Birthdays don't have to be selfish days.");
							joeTextTexture.render(50, 340);
							joeTextTexture.loadMedia("Put on the helmet for style. I mean, it's not any special helmet.");
							joeTextTexture.render(50, 380);
							joeTextTexture.loadColors(255, 255, 255);
							break;
						case 10:
							joeTextTexture.loadMedia("Toothless picked you up and is randomly taking you somewhere.");
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("Maybe a new world? Click anywhere to see.");
							joeTextTexture.render(0, 20);
							break;
						case 12:
							joeTextTexture.loadMedia("GET THE DRAGON CUP IF YOU WANT TO WIN. USE ARROW KEYS TO MOVE.");
							joeTextTexture.render(0, 0);
							joeTextTexture.loadMedia("DO NOT LET FISHLEGS GET YOU! CLICK ANYWHERE TO PLAY.");
							joeTextTexture.render(0, 40);
							break;		
					}//end switch
					count = 0; //cannot enter the loop with count anymore
					SDL_RenderPresent(gRenderer); //update the renderer
				}//mouse down event	
				if(mgPlay){ //play the mini game
					if(!timer.isStarted()){ //start the timer, user only has 10 seconds
						timer.start();
					}
					else if(hiccup.move(fishlegs.getColliders())){ //check if user is collides
						scenario = 6;
						joeTexture.loadMedia("scene1JY.png");
						hiccup.reset();
						fishlegs.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
						fishlegs2.reset(SCREEN_WIDTH/4, SCREEN_HEIGHT/4);
						joeTexture.setAlpha(255);
						hiccup.setAlpha(0);
						mgPlay = false;
						timer.stop();
						count = 1;
					} 
					else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){//if the user presses keys then handle events	
						hiccup.handleEvent(e);
					}				
				}//if minigame is being played
			}//while there is an event
			//check to see if the user and enemy dots collide
			if(mgPlay && (fishlegs.randMove(hiccup.getColliders(), hiccup.getX(), hiccup.getY()) || fishlegs2.randMove(hiccup.getColliders(), hiccup.getX(), hiccup.getY()))){
					scenario = 6;
					joeTexture.loadMedia("scene1JY.png");
					hiccup.reset();
					fishlegs.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2); //reset positions so that they dont start at last hit place
					fishlegs2.reset(SCREEN_WIDTH/4, SCREEN_HEIGHT/4);
					joeTexture.setAlpha(255);
					hiccup.setAlpha(0);
					mgPlay = false;
					timer.stop();
					count = 1;
			}//makes sure that the fishlegs continues to move even though player dot doesn't move during mini game	
			if(mgPlay){
				if(timer.getTicks() > 10000 || goblet.checkCollision(goblet.getColliders(), hiccup.getColliders())){
					scenario = 8;
					joeTexture.loadMedia("scene8JY.png");
					hiccup.reset();
					joeTexture.setAlpha(255);
					hiccup.setAlpha(0);
					fishlegs.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
					fishlegs2.reset(SCREEN_WIDTH/4, SCREEN_HEIGHT/4);
					mgPlay = false;
					timer.stop();
					count = 1;
				}
				//Clear Screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear(gRenderer);
				//render the mini game textures
				goblet.render();
				hiccup.render();
				fishlegs.render();
				fishlegs2.render();	
				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}//while quit is not true
	}
	//free the memory
	joeTexture.free();
	choice.free();
	Mix_FreeMusic( gMusic );
	joeTextTexture.free();
	gMusic = NULL;
	return 0;
}
#endif
