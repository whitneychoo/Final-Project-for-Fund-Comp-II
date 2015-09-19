#include "ex.h"
#include "derive.h"
using namespace std;

int main( int argc, char* args[] ){

	whitney hi;
	whitney hoe;
	whitney hey;
	whitney ha;
	//Start up SDL and create window
	if( !hi.init())
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		
		hi.playGame();
        hoe.playGame();
	}

	hi.close();
}
