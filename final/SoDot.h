/*Sam Cho, Whitney Choo, So Yon(Alli) Kwon, Joseph Yoon
*CSE 20212, Spring 2015
*Final Project
*How to Kill Harry Pokemon
*/

#include "LTexture.h"
#include <cmath>

using namespace std;
//The dot that will move around on the 

class SoDot
{
    public:
  //Initializes the variables
  SoDot (int, int);

  //Takes key presses and adjusts the dot's velocity
   void handleEvent (SDL_Event & e);

  //Moves the dot
   void moveV ();

  void moveH ();
  void moveB ();
  //Shows the dot on the screen

  int getCount ();
  int checkWin ();
  void renderd();
void loadMedia(std::string);

 protected:
  //The X and Y offsets of the dot
  int mPosX, mPosY, mPosXV, mPosYV, mPosXH, mPosYH, mPosXB, mPosYB;
  int DOT_WIDTH_H;
  int DOT_HEIGHT_H;
  int DOT_WIDTH_V;
  int DOT_HEIGHT_V;

  int DOT_VELH, DOT_VELYV, DOT_VELXV, DOT_VELB;
  //The velocity of the dot
  int mVelXH, mVelYH;
  int win;
  int counter;
  int spacePressed;

};

//load media
void SoDot::loadMedia(std::string pic){
	gDotTexture.loadMedia(pic);
}

void
SoDot::handleEvent (SDL_Event & e)
{
   //If a key was pressed
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
      //Adjust the velocity
      switch (e.key.keysym.sym)
	{
	case SDLK_UP:
	  mVelYH -= DOT_VELH; //move texture up
	  break;
	case SDLK_DOWN:
	  mVelYH += DOT_VELH; //move down

	  break;
	}
    }
  //If a key was released
  if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
      //Adjust the velocity
      switch (e.key.keysym.sym)
	{
	case SDLK_UP:
	  mVelYH += DOT_VELH;
	  break;
	case SDLK_DOWN:
	  mVelYH -= DOT_VELH;
	  break;
       case SDLK_SPACE: //if space is pressed
	  spacePressed = 1;
	  break;
}

}
}

SoDot::SoDot (int x , int y)
{
  //Initialize the textures
  mPosX = x;
  mPosY = y;
  mPosXV = 100;
  mPosYV = 100;
  mPosXH = 550;
  mPosYH = 100;
  mPosXB = mPosXH - 30;
  mPosYB = mPosYH;

  
  spacePressed = 0;
  //Initialize the velocity
  mVelXH = 0;
  mVelYH = 0;
  DOT_WIDTH_V = 70;
  DOT_HEIGHT_V = 140;
  DOT_WIDTH_H = 60;
  DOT_HEIGHT_H = 60;
  DOT_VELH = 1;
  DOT_VELYV = 2;
  DOT_VELXV = 3;
  DOT_VELB = 6;
  win = 0;
  counter = 0;
}

void
SoDot::moveH ()
{
//move Harry
//bool quit = false;
  

  //Move the dot up or down
  mPosYH += mVelYH;

  //If the dot went too far up or down
  if ((mPosYH < 0) || (mPosYH + DOT_HEIGHT_H > SCREEN_HEIGHT))
    {
      //Move back
      mPosYH -= mVelYH; 
    }
  mPosXB = mPosXH;
  mPosYB = mPosYH;


}


void
SoDot::moveV ()
{				//move Voldemort
  //Move the dot left or right
  mPosYV += DOT_VELYV;


  //If the dot went too far up or down
  if ((mPosYV < 0) || (mPosYV + DOT_HEIGHT_V > SCREEN_HEIGHT))
    {
      //Move back
      DOT_VELYV = DOT_VELYV * -1; //change directions
    }


//mPosY += 20;
}

void
SoDot::moveB ()
{
//when space is pressed
  if (spacePressed == 1)
    {
      do
	{
	  mPosXB -= DOT_VELB; //move the ball
	  SDL_RenderClear (gRenderer);
	  renderd (); //render the ball
	  moveV(); //move Voldemort
	  SDL_RenderPresent (gRenderer);
	}
      while (mPosXB > 80); //move ball until the wall
         
      if ((mPosYB < mPosYV + 140) && (mPosYB > mPosYV - 10))
	{ //count if the ball hits Voldemort
	 counter ++;
	}

      mPosXB = mPosXH;
//turn off shoot
      spacePressed = 0;
    }
}


int SoDot::checkWin()
{
//return counter

return counter;
}

void
SoDot::renderd ()
{
  //Show the textures
  gDotTexture.render (mPosXV, mPosYV);
  gDotTexture1.render (mPosXH, mPosYH);
  gDotTexture2.render (mPosXB, mPosYB);
}




