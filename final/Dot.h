/*Sam Cho, Whitney Choo, So Yon(Alli) Kwon, Joseph Yoon
*CSE 20212, Spring 2015
*Final Project
*How to Kill Harry Pokemon
*/
#include "LTexture.h"
#include <cmath>
using namespace std;
//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 50;
		static const int DOT_HEIGHT = 50;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 7;
		void setAlpha(int a);
		//Initializes the variables
		Dot( int x, int y );
		//move function to move with keyboard
		int move( std::vector<SDL_Rect>& otherColliders );
		//move function to bounce off walls with no input
		int randMove(std::vector<SDL_Rect>& otherColliders, int x, int y );	
		void reset(int x = 0, int y = 0);	
		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );
		int getX();
		int getY();
		//Shows the dot on the screen
		void render();
		void loadMedia(std::string pic);	
		//Gets the collision boxes
		std::vector<SDL_Rect>& getColliders();
		bool checkCollision( std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b );
    protected:
		//The X and Y offsets of the dot
		int mPosX, mPosY;
		//The velocity of the dot
		int mVelX, mVelY;	
		double randVelX, randVelY;	
		//Dot's collision boxes
		std::vector<SDL_Rect> mColliders;
		//Moves the collision boxes relative to the dot's offset
		void shiftColliders();
		//needs to be a variable so that multiple dots get rendered
		LTexture gDotTexture;

};

void Dot::setAlpha(int a){
	gDotTexture.setAlpha(a);
}

int Dot::getX(){
	return mPosX;
}

int Dot::getY(){
	return mPosY;
}

int Dot::randMove(std::vector<SDL_Rect>& otherColliders, int x, int y ){ 
//Move the dot left or right
	int num = 0;
    mPosX += randVelX;
    shiftColliders();
    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) || checkCollision( mColliders, otherColliders ) )
    {
	if(checkCollision(mColliders, otherColliders))
		num = 1;
        //Move back
        mPosX -= randVelX;
	randVelX = -1*randVelX;
		shiftColliders();
    }

    //Move the dot up or down
    mPosY += randVelY;
	shiftColliders();

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mColliders, otherColliders ) )
    {
	if(checkCollision(mColliders, otherColliders))
		num = 1;
        	//Move back
        	mPosY -= randVelY;
		randVelY = -1*randVelY;
		shiftColliders();
    }
	return num;
}
//reset to make sure that images can start at new places
void Dot::reset(int x, int y){
	mPosX = x;
	mPosY = y;
	mVelX = 0;
	mVelY = 0;
	randVelX = -1;
	randVelY = 1; 
}
//load media function to be able to make many different dots
void Dot::loadMedia(std::string pic){
	gDotTexture.loadMedia(pic);
}

Dot::Dot( int x, int y )
{
    //Initialize the offsets
    mPosX = x;
    mPosY = y;

    //Create the necessary SDL_Rects
    mColliders.resize( 11 );

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
	randVelX = -1;
	randVelY = 1;

    //Initialize the collision boxes' width and height
    mColliders[ 0 ].w = 20;
    mColliders[ 0 ].h = 2;

    mColliders[ 1 ].w = 28;
    mColliders[ 1 ].h = 2;

    mColliders[ 2 ].w = 34;
    mColliders[ 2 ].h = 3;

    mColliders[ 3 ].w = 40;
    mColliders[ 3 ].h = 4;

    mColliders[ 4 ].w = 46;
    mColliders[ 4 ].h = 4;

    mColliders[ 5 ].w = 50;
    mColliders[ 5 ].h = 20;

    mColliders[ 6 ].w = 46;
    mColliders[ 6 ].h = 4;

    mColliders[ 7 ].w = 40;
    mColliders[ 7 ].h = 4;

    mColliders[ 8 ].w = 34;
    mColliders[ 8 ].h = 3;

    mColliders[ 9 ].w = 28;
    mColliders[ 9 ].h = 2;

    mColliders[ 10 ].w = 20;
    mColliders[ 10 ].h = 2;

	//Initialize colliders relative to position
	shiftColliders();
}

void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
	//Adjust the velocity
        switch( e.key.keysym.sym )
        {		
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

int Dot::move( std::vector<SDL_Rect>& otherColliders )
{
	int num;
    //Move the dot left or right
    mPosX += mVelX;
    shiftColliders();
num = 0;
    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) || checkCollision( mColliders, otherColliders ) )
    {
	if(checkCollision(mColliders, otherColliders))
		num = 1;
        //Move back
        mPosX -= mVelX;
		shiftColliders();
    }

    //Move the dot up or down
    mPosY += mVelY;
	shiftColliders();

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mColliders, otherColliders ) )
    {
	if(checkCollision(mColliders, otherColliders))
		num = 1;
        //Move back
        mPosY -= mVelY;
		shiftColliders();
    }
	return num;
}

bool Dot::checkCollision( std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Go through the A boxes
    for( int Abox = 0; Abox < a.size(); Abox++ )
    {
        //Calculate the sides of rect A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;

        //Go through the B boxes
        for( int Bbox = 0; Bbox < b.size(); Bbox++ )
        {
            //Calculate the sides of rect B
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;

            //If no sides from A are outside of B
            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                //A collision is detected
                return true;
            }
        }
    }

    //If neither set of collision boxes touched
    return false;
}

void Dot::render()
{
    //Show the dot
	gDotTexture.render( mPosX, mPosY );
}

void Dot::shiftColliders()
{
    //The row offset
    int r = 0;

    //Go through the dot's collision boxes
    for( int set = 0; set < mColliders.size(); ++set )
    {
        //Center the collision box
        mColliders[ set ].x = mPosX + ( DOT_WIDTH - mColliders[ set ].w ) / 2;

        //Set the collision box at its row offset
        mColliders[ set ].y = mPosY + r;

        //Move the row offset down the height of the collision box
        r += mColliders[ set ].h;
    }
}

std::vector<SDL_Rect>& Dot::getColliders()
{
	return mColliders;
}


