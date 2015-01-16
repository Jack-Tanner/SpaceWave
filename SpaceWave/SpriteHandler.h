#pragma once
#include "Sprite.h"
#include "Player.h"
#include "Vector2.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "MapData.h"
#include <vector>
#include <string>
using namespace std;
using namespace Math;

namespace Game
{
	class SpriteHandler
	{
	public:
		SpriteHandler()
		{
			BulletID = 5;
			EnemyID = 2000;
			ExplosionID = 4000;
			CurrentWave = 0;
		}
		void AddPlayer(string ImagePath, Vector2 vec);
		Player* GetPlayer(){return &Player1;}

		void AddBullet(int ImageID, Vector2 Pos, int Direction, bool IsGood);
		void AddEnemy(string ImagePath, Vector2 Pos, int WaveID);
		void AddExplosion(Vector2 Pos);
		void AddWave(MapData wave);
		
		void Tick();
		void Draw();

		bool CheckBulletHit(int ID, int Damage);

		int GetCurrentWave(){return CurrentWave;}
		int GetMaxWaves(){return WaveList.size();}
		int GetEnemyCount(){return EnemyList.size();}
		void Shutdown();
	private:
		Player Player1;
		vector<Bullet> BulletList;
		vector<Enemy> EnemyList;
		vector<Explosion> ExplosionList;
		vector<MapData> WaveList;
		int BulletID, EnemyID, ExplosionID;
		int NextWaveTime, CurrentWave;
	};
}