#pragma once
#include <dinput.h>
#include <DarkGDK.h>
#include <string>
#include <fstream>

#include "gvector.h"
//#include "GameState.h"

using namespace std;
using namespace vctr;

namespace Game
{
	class GameHandler
	{
	private:
		string Title;
		GameVector ScreenSize;
		GameVector vec;

//		GameState gameState;
	public:
		bool Init(string title, GameVector screen_size);
		void MainLoop();
		void Shutdown();

	};
}