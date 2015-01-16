#pragma once
#include "SpriteHandler.h"
#include <string>
using namespace std;

namespace Game
{
	class GameState;

	class Level
	{
	public:
		void LoadLevel(string filepath, GameState& gameState);
		void TickLevel(GameState& gameState);
		void DrawLevel();

		void ShutdownLevel();
	private:
		string FilePath;

		int Backgroundx, Backgroundx1;
		SpriteHandler spriteHandler;
	};
}