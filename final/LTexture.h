#ifndef LTEXTURE_H
#define LTEXTURE_H


#include <iostream>
using namespace std;

SDL_Renderer* gRenderer = NULL;
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//TTF_Font *gFont = NULL;


//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		//Deallocates texture
		void free();

		bool loadMedia(std::string pic);
		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();
		
		void setWidth(int width);
		void setHeight(int height);

bool loadMiniGame (std::string, std::string, std::string);
	protected:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//used for mini games
LTexture gDotTexture;
LTexture gDotTexture1;
LTexture gDotTexture2;
//used to load mini game files and use textures
bool
  LTexture::loadMiniGame (std::string minigame, std::string minigame1,
		      std::string minigame2)
{
  //Loading success flag
  bool success = true;

  //Load dot texture
  if (!gDotTexture.loadFromFile (minigame.c_str ()))
    {
      printf ("Failed to load dot texture!\n");
      success = false;
    }

  if (!gDotTexture1.loadFromFile (minigame1.c_str ()))
    {
      printf ("Failed to load dot texture!\n");
      success = false;
    }

  if (!gDotTexture2.loadFromFile (minigame2.c_str ()))
    {
      printf ("Failed to load dot texture!\n");
      success = false;
    }


  return success;
}

void LTexture::setWidth(int width){
	mWidth = width;
}

void LTexture::setHeight(int height){
	mHeight = height;
}

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}


void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool LTexture::loadMedia(std::string pic)
{
	//Loading success flag
	bool success = true;
	//Load stretching surface

	if( !loadFromFile( pic))
	{
		printf( "Failed to load stretching image!\n" );
		success = false;
	}
	return success;
}

#endif
