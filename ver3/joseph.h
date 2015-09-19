#include "base.h"
#include "Dot.h"
#include "LTimer.h"
#include "TextTexture.h"
#ifndef JOSEPH_H
#define JOSEPH_H
using namespace std;

//Current displayed texture
Dot dot(0, 0);
Dot otherDot(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
LTimer timer;
LTexture gTexture;
//Rendered texture
TextTexture gTextTexture;
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
	int count = 1;
	int scenario = 1;
	bool mgPlay = false;
	//Load media

	if(!gTexture.loadMedia("scene1JY.png") && !loadMusic())
		printf( "Failed to load media!\n" );
	else{
		//Apply the image
		SDL_RenderClear( gRenderer );
		//Render texture to screen
		//gTexture.render(0, 0);
		//Update screen
		SDL_RenderPresent( gRenderer );
		bool quit = false;
		cout << "should play music" << endl;
		loadMusic();
		Mix_PlayMusic(gMusic, -1);
		SDL_Event e;
		while(!quit){
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
					}
					//Scene Choice
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
							gTextTexture.loadMedia("You wake up to Toothless (your dragon) licking your face. The roosters are"); 
							gTextTexture.render(0, 0);
							gTextTexture.loadMedia("crowing and the Isle of Berk is waking up. It's finally the day of your ");
							gTextTexture.render(0, 20);
							gTextTexture.loadMedia("birthday and a well-deserved rest day from all the exploration trips your"); 
							gTextTexture.render(0, 40);
							gTextTexture.loadMedia("father has been sending you on. You eat the special birthday breakfast on your");
							gTextTexture.render(0, 60);
							gTextTexture.loadMedia("bedside table and decide what to do now... ");
							gTextTexture.render(0, 80);
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
							break;
						case 11:
							gTexture.setAlpha(0);
							dot.loadMedia("dot.bmp");
							mgPlay = true;
							break;		
					}
					//Scene Draw
					//stretch backgrounds
					gTexture.setWidth(SCREEN_WIDTH);
					gTexture.setHeight(SCREEN_HEIGHT);
					//Draw textures
					gTexture.render(0,0);
					
					//Scene Text Draw
					switch(scenario){
						case 1:
							//Story
							gTextTexture.loadMedia("You wake up to Toothless (your dragon) licking your face. The roosters are"); 
							gTextTexture.render(0, 0);
							gTextTexture.loadMedia("crowing and the Isle of Berk is waking up. It's finally the day of your ");
							gTextTexture.render(0, 20);
							gTextTexture.loadMedia("birthday and a well-deserved rest day from all the exploration trips your"); 
							gTextTexture.render(0, 40);
							gTextTexture.loadMedia("dad has been sending you on. You eat the special birthday breakfast on your");
							gTextTexture.render(0, 60);
							gTextTexture.loadMedia("bedside table and decide what to do now... ");
							gTextTexture.render(0, 80);
							
							//Choices
							gTextTexture.loadMedia("Rest a bit more from your week long journey of mapping unexplored lands and");
							gTextTexture.render(10, 340);
							gTextTexture.loadMedia("return to that awesome dream.");
							gTextTexture.render(20, 360);
							gTextTexture.loadMedia("Start your day early with coffee made from the new coffee beans your brought");
							gTextTexture.render(10, 380);
							gTextTexture.loadMedia("back from journey and relax in your childhood living room playing with ");
							gTextTexture.render(20, 400);
							gTextTexture.loadMedia("Toothless.");
							gTextTexture.render(20, 420);
							gTextTexture.loadMedia("Go find Astrid (your significant other), and hurry over to the best cliff to");
							gTextTexture.render(10, 440);
							gTextTexture.loadMedia("watch the sunrise.");
							gTextTexture.render(20, 460);
							break;		
						case 2:
							//Story
							gTextTexture.loadMedia("Everyone is bustling around Berk. What do you want to do?"); 
							gTextTexture.render(0, 0);
							
							//Choices
							gTextTexture.loadMedia("Go to the local tavern to see who's around.");
							gTextTexture.render(10, 340);
							gTextTexture.loadMedia("Hide under your blanket because the sun is too bright and fall back asleep.");
							gTextTexture.render(10, 360);
							gTextTexture.loadMedia("Go for a quick flight with Toothless.");
							gTextTexture.render(10, 380);
							break;	
						case 3:
							//Story
							gTextTexture.loadMedia("You feel energized and race Toothless to the harbor because you want to see");
							gTextTexture.render(0, 0);
							gTextTexture.loadMedia("how all the fisherman are doing. On the way there, you see your good friend");
							gTextTexture.render(0, 20);
							gTextTexture.loadMedia("Fishlegs. He calls out to you as you're getting closer and asks if you want"); 
							gTextTexture.render(0, 40);
							gTextTexture.loadMedia("to play a quick game of Dragon Cup.");
							gTextTexture.render(0, 60);
							
							//Choices
							gTextTexture.loadMedia("Continue to run by him because now Toothless has gained a lead on you!");
							gTextTexture.render(10, 340);
							gTextTexture.loadMedia("Stop and play a quick game of Dragon Cup.");
							gTextTexture.render(10, 360);
							gTextTexture.loadMedia("Steal Fishlegs' helmet and continue to run.");
							gTextTexture.render(10, 380);
							break;	
						case 4:			
							//Story
							gTextTexture.loadMedia("You're at the cliff with Astrid. The sunrise is awesome. Best decision to");
							gTextTexture.render(0, 0);
							gTextTexture.loadMedia("start your day off with spending time with her. What move to make next..?");
							gTextTexture.render(0, 20);

							//Choices
							gTextTexture.loadMedia("Take a quick nap with Astrid.");
							gTextTexture.render(10, 340);
							gTextTexture.loadMedia("Ask Astrid to marry you.");
							gTextTexture.render(10, 360);
							gTextTexture.loadMedia("Challenge Astrid to a race around Berk with their dragons.");
							gTextTexture.render(10, 380);
							break;		
						case 5:
							//Story
							gTextTexture.loadMedia("For some reason, there's not that many people at the tavern. Well, there's");
							gTextTexture.render(0, 0);
							gTextTexture.loadMedia("a person you haven't seen before. Being the son of the chieftain and all,");
							gTextTexture.render(0, 20);
							gTextTexture.loadMedia("you go and introduce yourself. 'I'm Hiccup. What's your name?' The person"); 
							gTextTexture.render(0, 40);
							gTextTexture.loadMedia("looks at you and asks you to choose a number between 1 and 100.");
							gTextTexture.render(0, 60);

							//Choices
							gTextTexture.loadMedia("1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25");
							gTextTexture.render(10, 340);
							gTextTexture.loadMedia("26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50");
							gTextTexture.render(10, 360);
							gTextTexture.loadMedia("51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75");
							gTextTexture.render(10, 380);
							gTextTexture.loadMedia("76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100");
							gTextTexture.render(10, 400);
							break;	
						case 6:
							//Story
							gTextTexture.loadMedia("You wake up to Toothless licking your face. Well, this seems familiar. The");
							gTextTexture.render(0, 0);
							gTextTexture.loadMedia("roosters are crowing and the Isle of Berk is waking up. You see the special");
							gTextTexture.render(0, 20);
							gTextTexture.loadMedia("birthday cake again. You definitely remember eating the cake yesterday and"); 
							gTextTexture.render(0, 40);
							gTextTexture.loadMedia("all of the activities before... What does this mean? Well, what to do now.?");
							gTextTexture.render(0, 60);

							//Choices
							gTextTexture.loadMedia("Rest a bit more from your week long journey of mapping unexplored lands and");
							gTextTexture.render(10, 340);
							gTextTexture.loadMedia("return to that awesome dream.");
							gTextTexture.render(20, 360);
							gTextTexture.loadMedia("Start your day early with coffee made from the new coffee beans your brought");
							gTextTexture.render(10, 380);
							gTextTexture.loadMedia("back from journey and relax in your childhood living room playing with ");
							gTextTexture.render(20, 400);
							gTextTexture.loadMedia("Toothless.");
							gTextTexture.render(20, 420);
							gTextTexture.loadMedia("Go find Astrid (your significant other), and hurry over to the best cliff to");
							gTextTexture.render(10, 440);
							gTextTexture.loadMedia("watch the sunrise.");
							gTextTexture.render(20, 460);
							break;	
						case 7:
							//Story
							gTextTexture.loadMedia("It's such a beautiful day, but you can't spend your whole day in the air.");
							gTextTexture.render(0, 0);
							gTextTexture.loadMedia("Or you can.");
							gTextTexture.render(0, 20);

							//Choices
							gTextTexture.loadMedia("Stay in the air.");
							gTextTexture.render(10, 340);
							gTextTexture.loadMedia("Go back to town and visit the tavern.");
							gTextTexture.render(10, 360);
							gTextTexture.loadMedia("Jump from Toothless to test his quickness because you know he'll catch you.");
							gTextTexture.render(10, 380);
							break;	
						case 8:
							//Story
							gTextTexture.loadMedia("You are given Fishlegs' helmet as a prize. You always wonder how such a");
							gTextTexture.render(0, 0);
							gTextTexture.loadMedia("small helmet could fit on such a big head. He asks if you'd like a drink");
							gTextTexture.render(0, 20);
							gTextTexture.loadMedia("at the tavern.");
							gTextTexture.render(0, 40);
							//Choices
							gTextTexture.loadMedia("Why not? Relaxing day. A few drinks won't hurt.");
							gTextTexture.render(10, 340);
							gTextTexture.loadMedia("A beautiful fish-smelling harbor awaits.");
							gTextTexture.render(10, 360);
							break;	
						case 9:			
							//Story
							gTextTexture.loadMedia("As you're walking away, there's a helmet in your hands and you see a young");
							gTextTexture.render(0, 0);
							gTextTexture.loadMedia("kid acting like a future viking in training.");
							gTextTexture.render(0, 20);
							
							//Choices
							gTextTexture.loadMedia("Give her the helmet. Birthdays don't have to be selfish days.");
							gTextTexture.render(10, 340);
							gTextTexture.loadMedia("Put on the helmet for style. I mean, it's not any special helmet.");
							gTextTexture.render(10, 360);
							break;
						case 10:
							cout << "You have passed this level" << endl;
							break;
						case 11:
							gTextTexture.loadMedia("YOU HAVE 10 SECONDS TO SURVIVE. USE ARROW KEYS TO MOVE.");
							gTextTexture.render(0, 0);
							break;		
					}
					count = 0;
					SDL_RenderPresent(gRenderer);
				}//mouse down event	
				if(mgPlay){
					if(!timer.isStarted()){
						timer.start();
					}
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
					else if(dot.move(otherDot.getColliders())){
						scenario = 6;
						gTexture.loadMedia("scene1JY.png");
						dot.reset();
						otherDot.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
						gTexture.setAlpha(255);
						gDotTexture.setAlpha(0);
						mgPlay = false;
						timer.stop();
						count = 1;
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
					count = 1;
			}//makes sure that otherdot continues to move even though player dot doesn't move during mini game	
			if(mgPlay){
				//Clear Screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear(gRenderer);
				dot.render();
				otherDot.render();	

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}//while quit is not true
	}
	gTexture.free();
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
}

//The dot that will move around on the screen
#endif


