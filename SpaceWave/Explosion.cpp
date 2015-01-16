#include "Explosion.h"
#include <DarkGDK.h>
using namespace Game;

void Explosion::Initilize(int id, Vector2 Pos)
{
	Position = Pos;
	ID = id;
	Alive = true;
	dbSetImageColorKey(0, 0, 0);
	dbScaleSprite(ID, 25);
}

void Explosion::Tick()
{
	if(Alive)
	{
		if(dbSpriteFrame(ID) == 20)
		{
			Alive = false;
			ShutDown();
		}
	}
}

void Explosion::Draw()
{
	if(Alive)
	{
		dbSprite(ID, Position.GetX(), Position.GetY(), 160);
		dbPlaySprite(ID, 1, 20, 80);
	}
}

void Explosion::ShutDown()
{
	Position = Vector2(-8000, -8000);
	dbHideSprite(ID);
	dbDeleteSprite(ID);
}