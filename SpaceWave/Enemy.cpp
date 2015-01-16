#include "Enemy.h"
#include "SpriteHandler.h"
#include <DarkGDK.h>
using namespace Game;

void Enemy::Initilize(int id, int imageid, string imagepath, Vector2 pos, int WaveID)
{
	this->WaveID = WaveID;
	ID = id;
	ImageID = imageid;
	Alive = true;
	Position = pos;
	FireRate = dbRnd(20);
	while(FireRate < 10)
	{
		FireRate = dbRnd(20);
	}
	Health = 10;
	Speed = 3;
	Points = 10;
	LastShootTime = dbTimer();
	LastHurtTime = dbTimer();
	IsHurting = false;
	IsExploding = false;
	IsActive = false;
	CanShoot = false;

	dbSetImageColorKey(255, 0, 255);
	dbCreateAnimatedSprite(id, const_cast<char*>(imagepath.c_str()), 3, 2, ImageID);
	dbMirrorSprite(ID);
}

void Enemy::Initilize(int id, int imageid, string imagepath, Vector2 pos, int RateOfFire, int Health, int Speedy, int Points)
{
	ID = id;
	ImageID = imageid;
	Alive = true;
	Position = pos;
	FireRate = RateOfFire;
	Health = Health;
	Speed = Speedy;
	Points = Points;
	LastShootTime = dbTimer();
	LastHurtTime = dbTimer();
	IsHurting = false;
	IsExploding = false;
	IsActive = false;
	CanShoot = false;

	dbSetImageColorKey(255, 0, 255);
	dbCreateAnimatedSprite(id, const_cast<char*>(imagepath.c_str()), 3, 2, ImageID);
	dbMirrorSprite(ID);
}

void Enemy::Tick(SpriteHandler& Manager)
{
	if(IsActive)
	{
		if(Alive)
		{
 			Position -= Vector2(Speed, 0);

			if(Position.GetX() < 800 || Position.GetX() > 0)
				CanShoot = true;
			else
				CanShoot = false;

			if(Position.GetX() < -200)
			{
				Alive = false;
				ShutDown();
			}

			if(Health <= 0)
			{
				if(Alive != false)
				{
					Alive = false;
					IsActive = false;
					Shutdown();
					Manager.GetPlayer()->AddScore(Points);
					Manager.AddExplosion(Position);
					dbPlaySound(2);
					return;
				}
			}

			//Shoot Bullets
			if(FireRate != 0 && IsActive)
			{
				if((dbTimer() - FireRate*100) >= LastShootTime)
				{
					Manager.AddBullet(3, Position, 4, false);
					LastShootTime = dbTimer();
				}
			}

			if(dbSpriteCollision(ID, 1))
			{
				Manager.GetPlayer()->Hurt(5);
			}
		}
	}
	
}

void Enemy::Draw()
{
	dbShowSprite(ID);
	if(IsActive)
	{
		if(Alive)
		{
  			dbSprite(ID, Position.GetX(), Position.GetY(), ImageID);

			if(IsHurting)
			{
				dbPlaySprite(ID, 4, 6, 100);
				if((dbTimer() - 1200) >= LastHurtTime)
					IsHurting = false;
			}
			else
 				dbPlaySprite(ID, 1, 3, 100);
		}
	}
}

void Enemy::Hurt(int damage)
{
	if((dbTimer() - 10) >= LastHurtTime)
	{
		Health -= damage;
		LastHurtTime = dbTimer();
		IsHurting = true;
	}
}

void Enemy::Shutdown()
{
	dbHideSprite(ID);
	dbDeleteSprite(ID);
}
