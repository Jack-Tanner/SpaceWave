#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include <string>
using namespace std;
using namespace Math;

namespace Game
{
	class Player : public Sprite
	{
	public:
		void Initilize(int id, string ImagePath, Vector2 vec);
		void Tick(SpriteHandler& Handler);
		void Draw();

		void Hurt(int damage);
		void AddScore(int amount);

		int GetScore(){return Score;}
		int GetHealth(){return Health;}
		void Shoot(SpriteHandler& Handler);
	private:
		int Score, Health, Speed;
		int LastHurtTime, LastShootTime;
		bool IsHurting, IsExploding;
	};
}