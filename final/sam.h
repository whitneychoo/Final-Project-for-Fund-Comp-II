/*Sam Cho, Whitney Choo, So Yon(Alli) Kwon, Joseph Yoon
*CSE 20212, Spring 2015
*Final Project
*How to Kill Harry Pokemon
*/
#include "base.h"
#include "samMini.h"
#include "LTimer.h"
#ifndef SAM_H
#define SAM_H
using namespace std;

//Current displayed texture
//Create objects from samMini texture that will be in the minigame
samMini samDot(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
samMini samOtherDot(0,0);
samMini samGogoDot(500, 300);
samMini samJohnnyDot(200, 200);

LTimer samTimer;
LTexture samTexture;
LTexture samChoice;
//Rendered texture
TextTexture samTextTexture;

class sam : public base {
public:
    //pretty selfexplanatory functions
    int playGame();
    bool loadMusic();
};

bool sam::loadMusic(){
	bool success = true;
	//Load music
	gMusic = Mix_LoadMUS( "killbill.mp3" );
	if( gMusic == NULL )
	{
		//errorchecks
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	} 
	return success;	
}

int sam::playGame()
{
    int count = 1;
    int scenario = 1;
    bool mgPlay = false;
    
    //Load media
    //Errorchecks
    if(!samTexture.loadMedia("scene1SC.png"))
        printf( "Failed to load media!\n" );
    else{
        //Apply the image
        SDL_RenderClear( gRenderer );
        //Render texture to screen
        samTexture.render(0, 0);
		loadMusic();
		Mix_PlayMusic(gMusic, -1);
		samTextTexture.loadFile("Raleway-Bold.ttf");
        //Update screen
        SDL_RenderPresent( gRenderer );
        bool quit = false;
        SDL_Event e;
        while(!quit){
            while(SDL_PollEvent(&e) !=0 || count){
                if(e.type == SDL_QUIT)
                    quit = true;
                else if((e.type == SDL_MOUSEBUTTONDOWN && !mgPlay) || count){
                    //Clear Screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear(gRenderer);
                    
                    int x, y;
                    if(!count){
                        SDL_GetMouseState(&x, &y);
                        //switch case goes through all of the locations of the blue squares next to the options
                        switch(scenario){
                            case 1:
                                if(x <= 90 && x >= 60 && y >= 340 && y <= 370)
                                    scenario = 2;
                                else if(x <= 90 && x >= 60 && y >= 380 && y <= 410)
                                    scenario = 4;
                                else if(x <= 90 && x >= 60 && y >= 420 && y <= 450)
                                    scenario = 3;
                                break;
                            case 2:
                                if(x <= 90 && x >= 60 && y >= 380 && y <= 410)
                                    scenario = 3;
                                else if(x <= 90 && x >= 60 && y >= 420 && y <= 450)
                                    scenario = 4;
                                break;
                            case 3:
                                if(x <= 90 && x >= 60 && y >= 420 && y <= 450)
                                    scenario = 10;
                                break;
                            case 4:
                                if(x <= 90 && x >= 60 && y >= 380 && y <= 410)
                                    scenario = 5;
                                else if(x <= 90 && x >= 60 && y >= 420 && y <= 450)
                                    scenario = 6;
                                break;
                            case 5:
                                if(x <= 90 && x >= 60 && y >= 380 && y <= 410)
                                    scenario = 3;
                                else if(x <= 90 && x >= 60 && y >= 420 && y <= 450)
                                    scenario = 4;
                                break;
                            case 6:
                                if(x <= 90 && x >= 60 && y >= 420 && y <= 450)
                                    scenario = 10;
                                break;
                            case 7://minigame case
                                break;
                            case 8:
                                if(x <= 90 && x >= 60 && y >= 420 && y <= 450)
                                    scenario = 9;
                                break;
                            case 10:
                                if(x <= 90 && x >= 60 && y >= 420 && y <= 450)
                                    scenario = 7;
                                break;
                        }//end switch
                    }
                    //Scene Choice loads all scene images. case 7 is the minigame and so loads the minigame characters. case 9 is the end of the level
                    switch(scenario){
                        case 1:
                            samTexture.loadMedia("scene1SC.png");
                            break;
                        case 2:
                            samTexture.loadMedia("scene2SC.png");
                            break;
                        case 3:
                            samTexture.loadMedia("scene3SC.png");
                            break;
                        case 4:
                            samTexture.loadMedia("scene4SC.png");
                            break;
                        case 5:
                            samTexture.loadMedia("scene5SC.png");
                            break;
                        case 6:
                            samTexture.loadMedia("scene6SC.png");
                            break;
                        case 7:
                            mgPlay = true;
                            samTexture.setAlpha(0);
                            samDot.loadMedia("minigame.png");
                            samOtherDot.loadMedia("oren.png");
                            samGogoDot.loadMedia("gogo.png");
                            samJohnnyDot.loadMedia("johnny.png");

                            break;
                        case 8:
                            samTexture.loadMedia("scene8SC.png");
                            break;
                        case 9:
                            quit = true;
                            break;
                        case 10:
                            samTexture.loadMedia("doors.png");
                            break;
                    }
                    //Scene Draw
                    //stretch backgrounds
                    samTexture.setWidth(SCREEN_WIDTH);
                    samTexture.setHeight(SCREEN_HEIGHT);
                    //Draw textures
                    //these if statements draw the blue squares you can click on in each scenario
                    samTexture.render(0,0);
                    if(scenario == 1){
                        samChoice.loadMedia("bluesquare.png");
                        samChoice.render(60, 340);
                        samChoice.render(60, 380);
                        samChoice.render(60, 420);
                    }
                    if(scenario == 2 || scenario == 4 || scenario == 5){
                        samChoice.loadMedia("bluesquare.png");
                        samChoice.render(60, 380);
                        samChoice.render(60, 420);
                    }
                    if(scenario == 3 || scenario == 6 || scenario == 8 || scenario == 10){
                        samChoice.loadMedia("bluesquare.png");
                        samChoice.render(60, 420);
                    }

                    //Scene Text Draw
                    switch(scenario){
                        case 1:
                            //Choices
                            samTextTexture.loadMedia("Go get delicious sushi!");
                            samTextTexture.render(100, 340);
                            samTextTexture.loadMedia("Talk to the creepy man!");
                            samTextTexture.render(100, 380);
                            samTextTexture.loadMedia("Go rent a motorcycle!");
                            samTextTexture.render(100, 420);
                            break;
                        case 2:
                            //Choices
                            samTextTexture.loadMedia("Go rent a motorcycle!");
                            samTextTexture.render(100, 380);
                            samTextTexture.loadMedia("Talk to the creepy man!");
                            samTextTexture.render(100, 420);
                            break;
                        case 3:
                            //Choices
                            samTextTexture.loadMedia("Go find Oren Ishii!");
                            samTextTexture.render(100, 420);
                            break;
                        case 4:
                            //Choices
                            samTextTexture.loadMedia("Definitely a friend!");
                            samTextTexture.render(100, 380);
                            samTextTexture.loadMedia("Definitely a foe!");
                            samTextTexture.render(100, 420);
                            break;
                        case 5:
                            //Choices
                            samTextTexture.loadMedia("Go rent a motorcycle!");
                            samTextTexture.render(100, 380);
                            samTextTexture.loadMedia("Talk to the creepy man!");
                            samTextTexture.render(100, 420);
                            break;
                            break;
                        case 6:
                            //Choices
                            samTextTexture.loadMedia("Go find Oren Ishii!");
                            samTextTexture.render(100, 420);
                            break;
                        case 7:
                            samTextTexture.loadMedia("YOU HAVE 10 SECONDS TO SURVIVE. USE ARROW KEYS TO MOVE.");
                            samTextTexture.render(0, 0);
                            break;
                        case 8:
                            //Choices
                            samTextTexture.loadMedia("Move onto the next level!");
                            samTextTexture.render(100, 420);
                            break;
                        case 9:
                            break;
                        case 10:
                            samTextTexture.loadMedia("I am ready!");
                            samTextTexture.render(100,420);
                            break;
                    }
                    count = 0;
                    SDL_RenderPresent(gRenderer);
                }//mouse down event	
                if(mgPlay){
                    //if(!samTimer.isStarted()){
                        samTimer.start();
                    //}
                    //if you lose you go back to scene 1 and start over
                    if(samDot.move(samOtherDot.getColliders())){
                        scenario = 1;
                        samTexture.loadMedia("scene1SC.png");
                        samDot.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                        samOtherDot.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                        samGogoDot.reset(500, 300);
                        samJohnnyDot.reset(200,200);
                        samTexture.setAlpha(255);
                        samDot.setAlpha(0);
                        mgPlay = false;
                        samTimer.stop();
                        count = 1;
                    } 
                    else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){	
                        samDot.handleEvent(e);
                    }				
                }//if minigame is being played*/
            }//while there is an event
            
            //if there is a collision between beatrix kiddo and any of oren's people the game is over and scenario 1 is presented again
            if(mgPlay && (samOtherDot.randMove(samDot.getColliders(), samDot.getX(), samDot.getY()) || samGogoDot.randMove(samDot.getColliders(), samDot.getX(), samDot.getY()) || samJohnnyDot.randMove(samDot.getColliders(), samDot.getX(), samDot.getY()))){
                
                scenario = 1;
                samTexture.loadMedia("scene1SC.png");
                samDot.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                samOtherDot.reset(0,0);
                samGogoDot.reset(500,300);
                samJohnnyDot.reset(200,200);
                samTexture.setAlpha(255);
                samDot.setAlpha(0);
                mgPlay = false;
                samTimer.stop();
                count = 1;
            }//makes sure that otherdot continues to move even though player dot doesn't move during mini game	
            if(mgPlay){
                if(samTimer.getTicks() > 7000){
                    scenario = 8;
                    samTexture.loadMedia("scene1SC.png");
                    samDot.reset(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                    samTexture.setAlpha(255);
                    samDot.setAlpha(0);
                    samOtherDot.reset(0, 0);
                    samGogoDot.reset(500,300);
                    samJohnnyDot.reset(200,200);
                    mgPlay = false;
                    samTimer.stop();
                    count = 1;
                }
                //Clear Screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear(gRenderer);
                samDot.render();
                samOtherDot.render();
                samGogoDot.render();
                samJohnnyDot.render();
                
                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }//while quit is not true
    }
    samTexture.free();
    samChoice.free();
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
	return 0;
}

#endif


