#pragma once

namespace Game
{
	class GameState;

	class BaseState
	{
	public:
		virtual bool Initilize() = 0;
		virtual void Tick(GameState& gameState) = 0;
		virtual void Draw() = 0;
		virtual void Shutdown() = 0;
	};
}