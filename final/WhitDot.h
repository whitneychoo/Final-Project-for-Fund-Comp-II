/*Sam Cho, Whitney Choo, So Yon(Alli) Kwon, Joseph Yoon
*CSE 20212, Spring 2015
*Final Project
*How to Kill Harry Pokemon
*/
#include "LTexture.h"
#include <cmath>
LTexture fDotTexture;
using namespace std;
//The dot that will move around on the screen
class WhitDot 
{
    public:
        //The dimensions of the pokemon
        static const int DOT_WIDTH = 54;        
        static const int DOT_HEIGHT = 60;
        void setAlpha(int a);

        //Maximum axis velocity of the dot
        static const int DOT_VEL = 7;
        
        //Initializes the variables
        WhitDot();

        //Takes key presses and adjusts the dot's velocity
        void handleEvent( SDL_Event& e );

        //Moves the dot and checks collision
        bool move( SDL_Rect& wall1, SDL_Rect& wall2, SDL_Rect& wall3, SDL_Rect& wall4, SDL_Rect& wall5);

        void loadMedia(std::string pic);

        //Shows the dot on the screen
        void render();

        bool checkCollision( SDL_Rect a, SDL_Rect b );

    protected:
        //The X and Y offsets of the dot
        int mPosX, mPosY;

        //The velocity of the dot
        int mVelX, mVelY;   
            
        SDL_Rect mCollider;
};
void WhitDot::setAlpha(int a){
    fDotTexture.setAlpha(a);
}

void WhitDot::loadMedia(std::string pic){
    fDotTexture.loadMedia(pic);
}

WhitDot::WhitDot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 240;

    //Set collision box dimension
    mCollider.w = DOT_WIDTH;
    mCollider.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}
void WhitDot::handleEvent( SDL_Event& e )
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
bool WhitDot::move( SDL_Rect& wall1, SDL_Rect& wall2, SDL_Rect& wall3, SDL_Rect& wall4, SDL_Rect& wall5 )
{
    // function checks movement of pokemon against the 5 obstacles
    //Move the dot left or right
    mPosX += mVelX;
    mCollider.x = mPosX;

    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || checkCollision( mCollider, wall1 ) || checkCollision( mCollider, wall2) || checkCollision( mCollider, wall3) || checkCollision( mCollider, wall4) || checkCollision( mCollider, wall5))
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    if(( mPosX + DOT_WIDTH >= SCREEN_WIDTH )){
    return true;
    }
    //Move the dot up or down
    mPosY += mVelY;
    mCollider.y = mPosY;

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider, wall1 ) || checkCollision( mCollider, wall3) || checkCollision( mCollider, wall4) || checkCollision( mCollider, wall5))
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }

    return false;
}

bool WhitDot::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
void WhitDot::render()
{
    //Show the dot
    fDotTexture.render( mPosX, mPosY );
}

