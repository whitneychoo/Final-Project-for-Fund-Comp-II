#include "base.h"
#include "SoDot.h"
#include "LTimer.h"
#include "TextTexture.h"
#include "LTexture.h"
#include <string>
#ifndef SO_H
#define SO_H
using namespace std;

LTimer sTimer;
LTexture mini;
LTexture button;
LTexture gTexture;
LTexture rec;
//Rendered texture
TextTexture gTextTexture;
SoDot dot (0, 0);

class So:public base
{
public:
  //play game
  int playGame ();
	bool loadMusic();
};

bool So::loadMusic(){
	bool success = true;
	//Load music
	gMusic = Mix_LoadMUS( "hp.mp3" );
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	} 
	return success;
}

int
So::playGame ()
{

  int count = 1;
  int scenario = 1;

  bool mgPlay = false;
  //Load media
  if (!gTexture.loadMedia ("S11.png"))
    printf ("Failed to load media!\n");
  else
    {

      SDL_Event e;
	//load Music
	loadMusic();
	Mix_PlayMusic(gMusic, -1);
      //Apply the image
      SDL_RenderClear (gRenderer);
      //Render texture to screen
      SDL_SetRenderDrawColor (gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	gTextTexture.loadFile("Bo.ttf", 25);
	gTextTexture.loadColors();
      //Update screen
      SDL_RenderPresent (gRenderer);
      bool quit = false;
      int c;
      string counter;
      while (!quit)
	{
	  while (SDL_PollEvent (&e) != 0 || count)
	    {
	      if (e.type == SDL_QUIT)
		quit = true;
	      //dot.handleEvent (e);
	      else if (e.type == SDL_MOUSEBUTTONDOWN && !mgPlay || count)
		{
		  //Clear Screen
		  SDL_SetRenderDrawColor (gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		  SDL_RenderClear (gRenderer);
		  int x, y;
		  if (!count)
		    {
		      SDL_GetMouseState (&x, &y);
		      switch (scenario)
			{ //check mouse position
			case 1:
			  if (x <= 40 && x >= 10 && y >= 340 && y <= 370)
			    scenario = 2;
			  else if (x <= 40 && x >= 10 && y >= 380 && y <= 410)
			    scenario = 13;	//starting scene
			  break;
			case 2:
			  if (x <= 40 && x >= 10 && y >= 340 && y <= 370)
			    scenario = 3;
			  else if (x <= 40 && x >= 10 && y >= 380 && y <= 410)
			    scenario = 11;
			  break;

			case 3:
			  if (x <= 40 && x >= 10 && y >= 340 && y <= 370)
			    scenario = 5;
			  else if (x <= 40 && x >= 10 && y >= 380 && y <= 410)
			    scenario = 4;	
			  break;
			case 4:
			  if (x <= 40 && x >= 10 && y >= 340 && y <= 370)
			    scenario = 5;
			  else if (x <= 40 && x >= 10 && y >= 380 && y <= 410)
			    scenario = 9;
			  else if (x <= 40 && x >= 10 && y >= 400 && y <= 450)
			    scenario = 13;
			  break;
			case 5:
			  if (x <= 40 && x >= 10 && y >= 340 && y <= 370)
			    scenario = 6;
			  else if (x <= 40 && x >= 10 && y >= 380 && y <= 410)
			    scenario = 9;
			  else if (x <= 40 && x >= 10 && y >= 420 && y <= 450)
			    scenario = 8;
			  break;
			case 6:
			  if (x <= 40 && x >= 10 && y >= 340 && y <= 370)
			    scenario = 8;
			  else if (x <= 40 && x >= 10 && y >= 380 && y <= 410)
			    scenario = 1;
			  else if (x <= 40 && x >= 10 && y >= 420 && y <= 450)
			    scenario = 7;
			  break;
			case 7:
			  if (x <= 40 && x >= 10 && y >= 340 && y <= 370)
			    scenario = 9;
			  else if (x <= 40 && x >= 10 && y >= 380 && y <= 410)
			    scenario = 9;
			  else if (x <= 40 && x >= 10 && y >= 420 && y <= 450)
			    scenario = 6;
			  break;
			case 8:
			  if (x <= 40 && x >= 10 && y >= 340 && y <= 370)
			    scenario = 12;
			  else if (x <= 40 && x >= 10 && y >= 380 && y <= 410)
			    scenario = 9;
			  break;
			case 9:
			  break;
			case 10:
			  scenario = 11;
			  break;
			case 11:
				quit = true;
			  break;
			case 12:
				scenario = 15;
			  break;
			case 13:	//start scene
			  break;
			case 14:
			  scenario = 10;
			  break;
			case 15:
				break;
			}//end switch
		    }//if count == 0
		  switch (scenario)
		    { //load media
		    case 1:
		      gTexture.loadMedia ("S11.png");
		      break;
		    case 2:
		      gTexture.loadMedia ("S21.jpg");
		      break;
		    case 3:
		      gTexture.loadMedia ("S31.jpg");
		      break;
		    case 4:
		      gTexture.loadMedia ("S42.jpg");
		      break;
		    case 5:
		      gTexture.loadMedia ("S53.jpg");
		      break;
		    case 6:
		      gTexture.loadMedia ("S62.jpg");
		      break;
		    case 7:
		      gTexture.loadMedia ("S72.jpg");
		      break;
		    case 8:
		      gTexture.loadMedia ("S85.jpg");
		      break;
		    case 9:
		      gTexture.loadMedia ("E23.jpg");
		      break;
		    case 10:
		      gTexture.loadMedia ("E21.jpg");
		      break;
		    case 11:
		      gTexture.loadMedia ("game.png");
		      break;
		    case 12:
			break;	      	
		    case 13:
		      gTexture.loadMedia ("SS1.jpg");
		      scenario = 12;
		      break;
		    case 14:
		      gTexture.loadMedia ("E21.jpg");
		      scenario = 10;
		      break;
			case 15:
			mini.loadMiniGame ("human.png", "harry.jpg", "dot.gif");
		      mgPlay = true;
		      break;

	
		    }

		  //stretch backgrounds
		  gTexture.setWidth (SCREEN_WIDTH);
		  gTexture.setHeight (SCREEN_HEIGHT);
		  //Draw textures
		  gTexture.render (0, 0);
		  if (scenario != 10 && scenario != 13 && scenario != 9
		      && scenario != 12 && scenario != 14 && scenario != 11)
		    {
		      button.loadMedia ("bolt");
		      button.render (10, 340);
		      button.render (10, 380);
		    }
		  if (scenario != 1 && scenario != 2 && scenario != 3
		      && scenario != 8 && scenario != 9 && scenario != 10
		      && scenario != 13 && scenario != 12 && scenario != 14 && scenario != 11)
		    button.render (10, 420);
		  switch (scenario)
		    {
		    case 1:

		      gTextTexture.loadMedia ("It is Dudley's birthday.");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia ("You go to a zoo and see a snake.");
		      gTextTexture.render (0, 20);
		      gTextTexture.loadMedia("You see a snake and feel a weird connection with it.");
		      gTextTexture.render (0, 40);
		      gTextTexture.loadMedia ("Do you talk to the snake?");
		      gTextTexture.render (0, 60);

		      //Choices
		      gTextTexture.loadMedia ("Yes, you don't mind being weird.");
		      gTextTexture.render (50, 340);
		      gTextTexture.loadMedia("You feel like he would speak back to you");
		      gTextTexture.render (80, 360);
		      gTextTexture.loadMedia("No, you don't want to be weird. You know snakes");
		      gTextTexture.render (50, 380);
		      gTextTexture.loadMedia ("fon't talk anyways.");
		      gTextTexture.render (80, 400);

		      break;
		    case 2:
		      gTextTexture.loadMedia ("Hagrid, a giant, appears.");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia("He tells you that your parents were great wizards. ");
		      gTextTexture.render (0, 20);
		      gTextTexture.loadMedia("He tells you that you have been accepted ");
		      gTextTexture.render (0, 40);
		      gTextTexture.loadMedia("to Hogwarts. Do you accept the invitation?");
		      gTextTexture.render (0, 60);

		      //Choices
		      gTextTexture.loadMedia("Yes, you are on board for the invitation.");
		      gTextTexture.render (50, 340);
		      gTextTexture.loadMedia("No. Wizards don't exist. You think this is a scam.");
		      gTextTexture.render (50, 380);
		      break;

		    case 3:

		      gTextTexture.loadMedia("You are on board the Hogwarts Express!");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia("It is amazing. Everyone seems to know your name.  ");
		      gTextTexture.render (0, 20);
		      gTextTexture.loadMedia("A red-haired boy comes into your compartment.");
		      gTextTexture.render (0, 40);
		      gTextTexture.loadMedia("He seems to want to talk to you. What do you do?");
		      gTextTexture.render (0, 60);

		      //Choices
		      gTextTexture.loadMedia("You talk to him. You guys are going to be friends.");
		      gTextTexture.render (50, 340);
		      gTextTexture.loadMedia("He has a smudge on his face. You don't like him.");
		      gTextTexture.render (50, 380);

		      break;
		    case 4:
		      //Story
		      gTextTexture.loadMedia("You are placed into the Slytherine House. ");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia("Malfoy is Crabbe are your best friends. What do you do?");
		      gTextTexture.render (0, 20);


		      //Choices
		      gTextTexture.loadMedia
			("You decide somethig is wrong.Malfoy is mean. you want out.");
		      gTextTexture.render (50, 340);
		      gTextTexture.loadMedia ("You miss home. ");
		      gTextTexture.render (50, 380);
		      gTextTexture.loadMedia
			("You love it. Evilness is your thing. ");
		      gTextTexture.render (50, 420);

		      break;
		    case 5:
		      //Story
		      gTextTexture.loadMedia("You are a Gryffindor. Hermonine, Ron, ");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia("Dumbledore are your best friends.");
		      gTextTexture.render (0, 20);
		      gTextTexture.loadMedia("You have learnt about the sorcerer’s stone.");
		      gTextTexture.render (0, 40);
		      gTextTexture.loadMedia("You think Snape is after it. What do you do?");
		      gTextTexture.render (0, 60);

		      //Choices
		      gTextTexture.loadMedia ("Tell Hagrid.Go meet with him.");
		      gTextTexture.render (50, 340);

		      gTextTexture.loadMedia("Don't do anything.He is a professor after all.");
		      gTextTexture.render (50, 380);

		      gTextTexture.loadMedia("Go chase Snape yourself.Your courage calls you.");
		      gTextTexture.render (50, 420);

		      break;
		    case 6:
		      gTextTexture.loadMedia("You are in Hagrid’s Hut with Ron and Hermonine. ");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia("You ask Hagrid if he knows anything about the stone. ");
		      gTextTexture.render (0, 20);
		      gTextTexture.loadMedia("He accidentally tells you about the three headed dogs. ");
		      gTextTexture.render (0, 40);
		      gTextTexture.loadMedia("After hearing this, what do you do?");
		      gTextTexture.render (0, 60);

		      //Choices
		      gTextTexture.loadMedia ("Go to the trapdoor.");
		      gTextTexture.render (50, 340);
		      gTextTexture.loadMedia("You are determined to guard the stone.");
		      gTextTexture.render (50, 360);
		      gTextTexture.loadMedia ("Three headed Dogs? ");
		      gTextTexture.render (50, 380);
		      gTextTexture.loadMedia ("No Way.");
		      gTextTexture.render (50, 400);
		      gTextTexture.loadMedia("Ask Ron and Hermonine to go without you.");
		      gTextTexture.render (50, 420);
		      gTextTexture.loadMedia("Betray them. You are too scared.");
		      gTextTexture.render (50, 440);
		      break;
		    case 7:
		      //Story
		      gTextTexture.loadMedia("You are at the trapdoor that leads to the stone. ");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia ("There is a three headed dog.");
		      gTextTexture.render (0, 20);
		      gTextTexture.loadMedia ("What do you do?");
		      gTextTexture.render (0, 40);
		      //Choices
		      gTextTexture.loadMedia
			("Scream and run for your life and never come back.");
		      gTextTexture.render (50, 340);
		      gTextTexture.loadMedia("Try to go through it despite the danger of being eaten.");
		      gTextTexture.render (50, 380);
		      gTextTexture.loadMedia("Retreat for now but come back later.");
		      gTextTexture.render (50, 420);
		      break;
		    case 8:
		      //Story
		      gTextTexture.loadMedia("You have chased after the stone. It was Voldemort ");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia("who was after the stone. You stand face with Voldemort. ");
		      gTextTexture.render (0, 20);

		      gTextTexture.loadMedia("The stone is in your pocket. He wants the stone.");
		      gTextTexture.render (0, 40);
		      gTextTexture.loadMedia ("Fight him and win.");
		      gTextTexture.render (0, 60);
		      //Choices
		      gTextTexture.loadMedia ("Yes. Choose to duel.");
		      gTextTexture.render (50, 340);
		      gTextTexture.loadMedia ("Run for your life.");
		      gTextTexture.render (50, 380);
		      break;
		    case 9:
		      gTextTexture.loadMedia(" Voldemort succeeded in resurrecting himself.");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia("You have fallen into the evilness of Voldemort. ");
		      gTextTexture.render (0, 20);
			gTextTexture.loadMedia("The wizarding world has fallen.");
		      gTextTexture.render (0, 40);
		      quit = true;
		      break;
		    case 10:
		      gTextTexture.loadMedia ("You have defeated Voldemort.");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia(" You are happy to go back home.");
		      gTextTexture.render (0, 20);

		      gTextTexture.loadMedia("The wizarding world is safe.. for now. The END.");
		      gTextTexture.render (0, 40);
		      break;
		    case 11:
			gTextTexture.loadMedia("Click anywhere to exit the game.");
			gTextTexture.render(0, 0);
		      break;
		    case 12:
		      gTextTexture.
			loadMedia
			("Hit Voldy 5 times in 10 sec. Press Spacebar.");
		      gTextTexture.render (0, 0);
		      break;
		    case 13:
		      gTextTexture.loadMedia ("You are Harry Potter.");
		      gTextTexture.render (0, 0);
		      gTextTexture.loadMedia ("You are miserable in your cupboard.");
		      gTextTexture.render (0, 20);
		      gTextTexture.loadMedia("Your uncle and aunt mistreat you. You are not loved");
		      gTextTexture.render (0, 40);
		      break;
		    }
		  count = 0;
		  SDL_RenderPresent (gRenderer);
		}		//mouse down event     
	      if (mgPlay)
		{ //play mini game
		  if (!sTimer.isStarted ())
		    {  //start timer
		      sTimer.start ();
		    }
		  else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP || e.type == SDLK_SPACE)
			{
		      dot.handleEvent (e);
		    }
		}//if minigame is being played
	    }//while there is an event
	  if (mgPlay)
	    {
	      if (sTimer.getTicks () > 8000)
		{ //play in 8 seconds
		  //if lost move to scene 9
		  scenario = 9;
		  gTexture.setAlpha (255);
		  gDotTexture.setAlpha (0);
		  mgPlay = false;
		  sTimer.stop ();
		  count = 1;
		}

	      //Clear Screen
	      SDL_SetRenderDrawColor (gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	      SDL_RenderClear (gRenderer);
		
 		//render textures
	      dot.renderd ();
		//move the textures
	      dot.moveB ();
	      dot.moveH ();
	      dot.moveV ();
	      if (dot.checkWin () == 5)
		{ //check if Voldy was hit 5 times
		  SDL_SetRenderDrawColor (gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		  SDL_RenderClear (gRenderer);
		 //if so move to scene 14
		  scenario = 14;
		  mgPlay = false;
		  count = 1;
		}
	      SDL_RenderPresent (gRenderer);
	    }//if playing mini game
	}//while quit is not true
    }
	//free music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

return 1;

}





#endif
