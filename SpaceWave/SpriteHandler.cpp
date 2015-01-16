#include "SpriteHandler.h"
#include <sstream>
using namespace Game;

void SpriteHandler::AddPlayer(string ImagePath, Vector2 vec)
{
	Player1.Initilize(1, ImagePath, vec);
}

void SpriteHandler::AddBullet(int ImageID, Vector2 Pos, int Direction, bool IsGood)
{
	Bullet temp;
	temp.Initilize(BulletID, 3, Pos, Direction, IsGood);
	BulletList.push_back(temp);
	BulletID++;

	if(BulletID >= 1000)
	{
		BulletID = 5;
	}
}

void SpriteHandler::AddEnemy(string ImagePath, Vector2 Pos, int WaveID)
{
	Enemy temp;
	temp.Initilize(EnemyID, 4, ImagePath, Pos, WaveID);
	EnemyList.push_back(temp);
	EnemyID++;

	if(EnemyID >= 3500)
	{
		EnemyID = 1000;
	}

}

void SpriteHandler::AddExplosion(Vector2 Pos)
{
	Explosion temp;
	temp.Initilize(ExplosionID, Pos);
	ExplosionList.push_back(temp);
	ExplosionID++;

	if(ExplosionID >= 4500)
	{
		EnemyID = 4000;
	}
}

void SpriteHandler::AddWave(MapData Wave)
{
	if(WaveList.size() <= 0)
	{
		NextWaveTime = (dbTimer() + Wave.TimeUntilNextWave);
	}
	WaveList.push_back(Wave);
}

void SpriteHandler::Tick()
{
	Player1.Tick(*this);

	//Get Current Wave And Activate Sprites If Needed.
	std::vector<Enemy>::iterator wt;
	for(wt = EnemyList.begin(); wt != EnemyList.end(); wt++)
	{
		for(int vb = 0; vb != 255; vb++)
		{
			if(wt->GetWaveID() == WaveList[CurrentWave].WaveIDS[vb])
			{
				wt->SetActive(true);
			}
		}
	}
	
	int CurrentTime = dbTimer();
	if(NextWaveTime != 0)
	{
		if(CurrentTime >= NextWaveTime)
		{
			CurrentWave++;
			NextWaveTime = (dbTimer() + 3000);
		}
	}

	//Explosion
	if(ExplosionList.size() -1 > 0)
	{
		std::vector<Explosion>::iterator ext;
		for(ext = ExplosionList.begin(); ext != ExplosionList.end(); ext++)
		{
			ext->Tick();
		}
	}

	//Bullets
	if(BulletList.size() > 0)
	{
		std::vector<Bullet>::iterator it;
		for(it = BulletList.begin(); it != BulletList.end(); it++)
		{
			it->Tick(*this);
		}
	}

	//Enemy
	if(EnemyList.size() > 0)
	{
		std::vector<Enemy>::iterator et;
		for(et = EnemyList.begin(); et != EnemyList.end(); et++)
		{
			et->Tick(*this);
		}
	}

}

void SpriteHandler::Draw()
{
	Player1.Draw();

	//Bullets
	if(BulletList.size() != 0)
	{
		std::vector<Bullet>::iterator it;
		for(it = BulletList.begin(); it != BulletList.end(); it++)
		{
			it->Draw();
		}
	}

	//Enemy
	if(EnemyList.size() > 0)
	{
		std::vector<Enemy>::iterator et;
		for(et = EnemyList.begin(); et != EnemyList.end(); et++)
		{
			et->Draw();
		}
	}

	//Explosion
	if(ExplosionList.size() -1 > 0)
	{
		std::vector<Explosion>::iterator ext;
		for(ext = ExplosionList.begin(); ext != ExplosionList.end(); ext++)
		{
			ext->Draw();
		}
	}

	string text;
	stringstream ss;
	ss << "Wave: " << CurrentWave << "/" << WaveList.size();
	text = ss.str();

	dbText(300, 560, const_cast<char*>(text.c_str()));
	ss.clear();
	text.clear();
}

bool SpriteHandler::CheckBulletHit(int ID, int Damage)
{
	std::vector<Enemy>::iterator it;
	for(it = EnemyList.begin(); it != EnemyList.end(); it++)
	{
		if(dbSpriteCollision(ID, it->GetID()))
		{
			if(it->IsAlive())
			{
				if(!it->Exploding())
				{
					it->Hurt(Damage);
					return true;
				}
			}
		}	
	}
	return false;
}

void SpriteHandler::Shutdown()
{
	Player1.ShutDown();

	if(BulletList.size() != 0)
	{
		std::vector<Bullet>::iterator it;
		for(it = BulletList.begin(); it != BulletList.end(); it++)
		{
			it->ShutDown();
		}
	}

	//Enemy
	if(EnemyList.size() > 0)
	{
		std::vector<Enemy>::iterator et;
		for(et = EnemyList.begin(); et != EnemyList.end(); et++)
		{
			et->ShutDown();
		}
	}

	//Explosion
	if(ExplosionList.size() -1 > 0)
	{
		std::vector<Explosion>::iterator ext;
		for(ext = ExplosionList.begin(); ext != ExplosionList.end(); ext++)
		{
			ext->ShutDown();
		}
	}

	BulletList.clear();
	EnemyList.clear();
	ExplosionList.clear();
	WaveList.clear();
	BulletID = 5;
	EnemyID = 2000;
	ExplosionID = 4000;
	CurrentWave = 0;
}
