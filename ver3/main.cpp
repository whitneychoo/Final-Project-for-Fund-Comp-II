#include "joseph.h"
#include "Whitney.h"
#include <iostream>
using namespace std;

int main( int argc, char* args[] ){

	Joseph hi;
	Whitney hoe;
	//Start up SDL and create window
	if( !hi.init())
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{	
	hi.playGame();
	cout << "Whitney is playing" << endl;
        hoe.playGame();
	cout << "Whitney is done" << endl;
	}
	hi.close();
	hoe.close();
}
