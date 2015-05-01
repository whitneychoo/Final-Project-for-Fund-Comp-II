/*Sam Cho, Whitney Choo, So Yon(Alli) Kwon, Joseph Yoon
*CSE 20212, Spring 2015
*Final Project
*How to Kill Harry Pokemon
*/
#ifndef TEXTTEXTURE_H
#define TEXTTEXTURE_H

#include "LTexture.h"


class TextTexture : public LTexture {
	public:
		//allows to load from file and edit font size
		void loadFile(std::string file, int font = 19);
		//change colors of font
		void loadColors(int red = 255, int green = 255, int blue = 255);
		//change what text is displayed on the screen
		bool loadMedia(std::string text);
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

	private:
		TTF_Font *gFont = NULL;
		string filename;
		int r, g, b;
		int fontSize;
};

//choose type of ttf and font size
void TextTexture::loadFile(std::string file, int font){
	filename = file;
	fontSize = font;
}

//choose what color the font is
void TextTexture::loadColors(int red, int green, int blue){
	r = red;
	g = green;
	b = blue;
}
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
//load the text you want to display to the screen
bool TextTexture::loadMedia(std::string text)
{
	bool success = true;
	gFont = TTF_OpenFont(filename.c_str(), fontSize);
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
	
        //Render text
        SDL_Color textColor = {r, g, b};
        if(!loadFromRenderedText(text, textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
	
    }
	return success;
}
#endif
