#pragma once
#include "Vector2.h"
#include "Sprite.h"
using namespace Math;

namespace Game
{
	class Explosion : public Sprite
	{
	public:
		void Initilize(int id, Vector2 Pos);
		void Tick();
		void Draw();
		void ShutDown();
	private:

	};
}
