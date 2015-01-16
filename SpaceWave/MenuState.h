#pragma once
#include "BaseState.h"
#include <string>
using namespace std;

namespace Game
{
	class MenuState: public BaseState
	{
	public:
		bool Initilize();
		void Tick(GameState& gameState);
		void TickLoadMap(GameState& gameState);
		void TickHighscores();
		void Draw();
		void Shutdown();
		void DrawHighscores();
	private:
		int Selection;
		string MapSelection;

		int Backgroundx, Backgroundx1;

		enum mStates { NONE, HIGHSCORES, LOADMAP };
		mStates State;
	};
}