#ifndef TEXTTEXTURE_H
#define TEXTTEXTURE_H

#include "LTexture.h"


class TextTexture : public LTexture {
	public:
		bool loadMedia(std::string text, int red = 255, int green = 255, int blue = 255);
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

	private:
		TTF_Font *gFont = NULL;
};

#ifdef _SDL_TTF_H
bool TextTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

bool TextTexture::loadMedia(std::string text, int red, int blue, int green)
{
	bool success = true;
	gFont = TTF_OpenFont( "ironbrine.ttf", 19);
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
	
        //Render text
        SDL_Color textColor = {red, green, blue};
        if(!loadFromRenderedText(text, textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
	
    }
	return success;
}
#endif
