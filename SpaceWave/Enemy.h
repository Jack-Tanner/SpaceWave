#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include <string>
using namespace std;
using namespace Math;

namespace Game
{
	class Enemy : public Sprite
	{
	public:

		void Initilize(int id, int imageid, string imagepath, Vector2 pos, int WaveID);
		void Initilize(int id,int imageid, string imagepath, Vector2 pos, int RateOfFire, int Health, int Speedy, int Points);

		void Hurt(int damage);

		void Draw();
		void Tick(SpriteHandler& Handler);
		void Shutdown();

		bool Exploding(){return IsExploding;};
		bool Active(){return IsActive;};
		void SetActive(bool Active){IsActive = Active;};
		int GetWaveID(){return WaveID;}
	private:
		int Speed;
		int WaveID;
		int FireRate, Health, Points;
		int LastShootTime, LastHurtTime;
		bool IsHurting, IsActive, CanShoot, IsExploding;
		};
}