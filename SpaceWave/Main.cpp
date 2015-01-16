/************************************************
 * Author: Ken Hayes
 * Date: 2013.4.28
 ************************************************/

// whenever using Dark GDK you must ensure you include the header file
#include "DarkGDK.h"
#include <string>

#include "gvector.h"
#include "Game.h"

using namespace Game;
using namespace vctr;

// the main entry point for the application is this function
void DarkGDK ( void )
{
	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );

	// our main loop
	while ( LoopGDK ( ) )
	{
		// update the screen
		dbSync ( );
	}

	// return back to windows
	return;
}