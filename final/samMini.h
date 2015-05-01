/*Sam Cho, Whitney Choo, So Yon(Alli) Kwon, Joseph Yoon
*CSE 20212, Spring 2015
*Final Project
*How to Kill Harry Pokemon
*/
#include "LTexture.h"
#include <cmath>

using namespace std;

//The characters that will move around on the screen during the minigame
class samMini
{
public:
    //The dimensions of the character
    static const int SAMMINI_WIDTH = 50;
    static const int SAMMINI_HEIGHT = 96;
    
    //Maximum axis velocity of the character
    static const int SAMMINI_VEL = 7;
    
    //Initializes the variables
    samMini( int x, int y );
    int move( std::vector<SDL_Rect>& otherColliders );
    int randMove(std::vector<SDL_Rect>& otherColliders, int x, int y );
    void reset(int x = 0, int y = 0);
    
    //Takes key presses and adjusts the character's velocity
    void handleEvent( SDL_Event& e );
    int getX();
    int getY();
    //Shows the character on the screen
    void render();
    //The images that the character will be
    void loadMedia(std::string pic);
    void loadMedia2(std::string pic);
    //Gets the collision boxes
    std::vector<SDL_Rect>& getColliders();
    bool checkCollision( std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b );
    //Needed since the LTexture is protected
    void setAlpha(int a);
    
    
protected:
    //The X and Y offsets of the dot
    int mPosX, mPosY/*, nPosX, nPosY*/;
    
    //The velocity of the dot
    int mVelX, mVelY;
    double randVelX, randVelY;
    //Dot's collision boxes
    std::vector<SDL_Rect> mColliders;
    
    //Moves the collision boxes relative to the dot's offset
    void shiftColliders();
    LTexture samMiniTexture;
};

//Needed since LTexture is protected
void samMini::setAlpha(int a){
    samMiniTexture.setAlpha(a);
}

int samMini::getX(){
    return mPosX;
}

int samMini::getY(){
    return mPosY;
}

int samMini::randMove(std::vector<SDL_Rect>& otherColliders, int x, int y ){
    //Move the dot left or right
    int num = 0;
    
    //Changes xpos continuously
    mPosX += randVelX;
    shiftColliders();
    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + SAMMINI_WIDTH > SCREEN_WIDTH ) || checkCollision( mColliders, otherColliders ) )
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
    if( ( mPosY < 0 ) || ( mPosY + SAMMINI_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mColliders, otherColliders ) )
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

//resets coordinates when screen clears
void samMini::reset(int x, int y){
    mPosX = x;
    mPosY = y;
    mVelX = 0;
    mVelY = 0;
    randVelX = -1;
    randVelY = 1;
}

//Loads actual image to the character
void samMini::loadMedia(std::string pic){
    samMiniTexture.loadMedia(pic);
}

samMini::samMini( int x, int y )
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
    mColliders[ 0 ].w = 6;
    mColliders[ 0 ].h = 1;
    
    mColliders[ 1 ].w = 10;
    mColliders[ 1 ].h = 1;
    
    mColliders[ 2 ].w = 14;
    mColliders[ 2 ].h = 1;
    
    mColliders[ 3 ].w = 16;
    mColliders[ 3 ].h = 2;
    
    mColliders[ 4 ].w = 18;
    mColliders[ 4 ].h = 2;
    
    mColliders[ 5 ].w = 20;
    mColliders[ 5 ].h = 6;
    
    mColliders[ 6 ].w = 18;
    mColliders[ 6 ].h = 2;
    
    mColliders[ 7 ].w = 16;
    mColliders[ 7 ].h = 2;
    
    mColliders[ 8 ].w = 14;
    mColliders[ 8 ].h = 1;
    
    mColliders[ 9 ].w = 10;
    mColliders[ 9 ].h = 1;
    
    mColliders[ 10 ].w = 6;
    mColliders[ 10 ].h = 1;
    
    //Initialize colliders relative to position
    shiftColliders();
}

void samMini::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= SAMMINI_VEL; break;
            case SDLK_DOWN: mVelY += SAMMINI_VEL; break;
            case SDLK_LEFT: mVelX -= SAMMINI_VEL; break;
            case SDLK_RIGHT: mVelX += SAMMINI_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += SAMMINI_VEL; break;
            case SDLK_DOWN: mVelY -= SAMMINI_VEL; break;
            case SDLK_LEFT: mVelX += SAMMINI_VEL; break;
            case SDLK_RIGHT: mVelX -= SAMMINI_VEL; break;
        }
    }
}

int samMini::move( std::vector<SDL_Rect>& otherColliders )
{
    int num;
    //Move the dot left or right
    mPosX += mVelX;
    shiftColliders();
    num = 0;
    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + SAMMINI_WIDTH > SCREEN_WIDTH ) || checkCollision( mColliders, otherColliders ) )
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
    if( ( mPosY < 0 ) || ( mPosY + SAMMINI_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mColliders, otherColliders ) )
    {
        if(checkCollision(mColliders, otherColliders))
            num = 1;
        //Move back
        mPosY -= mVelY;
        shiftColliders();
    }
    return num;
}

bool samMini::checkCollision( std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b )
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

void samMini::render()
{
    //Show the dot
    samMiniTexture.render( mPosX, mPosY );
   // samOren.render( mPosX, mPosY );
}

void samMini::shiftColliders()
{
    //The row offset
    int r = 0;
    
    //Go through the dot's collision boxes
    for( int set = 0; set < mColliders.size(); ++set )
    {
        //Center the collision box
        mColliders[ set ].x = mPosX + ( SAMMINI_WIDTH - mColliders[ set ].w ) / 2;
        
        //Set the collision box at its row offset
        mColliders[ set ].y = mPosY + r;
        
        //Move the row offset down the height of the collision box
        r += mColliders[ set ].h;
    }
}

std::vector<SDL_Rect>& samMini::getColliders()
{
    return mColliders;
}
