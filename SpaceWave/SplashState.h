#pragma once
#include "BaseState.h"

namespace Game
{
	class SplashState: public BaseState
	{
	public:
		bool Initilize();
		void Tick(GameState& gameState);
		void Draw();
		void Shutdown();
	};
}