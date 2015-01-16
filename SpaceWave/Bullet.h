#pragma once
#include "Sprite.h"
#include "Vector2.h"
using namespace Math;
namespace Game 
{
	class Bullet : public Sprite
	{
	public:
		void Initilize(int id, int ImgID, Vector2 Pos, int Direction, bool IsGood);
		void Tick(SpriteHandler& Handler);
	private:
		int Direction;
		Vector2 Speed;
		bool Good;
	};
}