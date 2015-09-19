#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

using namespace std;

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path, SDL_Renderer*);

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x, int y, SDL_Renderer* );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;

};

#endif
