#include "Sprite.h"
#include "SpriteHandler.h"
using namespace Game;

void Sprite::Initilize(int id, int iID, Vector2 Pos)
{
	ID = id;
	ImageID = iID;
	Position = Pos;
	Alive = true;
	WaveID = 0;
}

void Sprite::Tick(SpriteHandler& Handler)
{
	if(!dbSpriteExist(ID))
		dbSprite(ID, Position.GetX(), Position.GetY(), ImageID);

	if(Alive)
		dbShowSprite(ID);
	else if(!Alive)
		dbHideSprite(ID);
}

void Sprite::Draw()
{
	if(Alive)
	{
		dbShowSprite(ID);
  		dbSprite(ID, Position.GetX(), Position.GetY(), ImageID);
	}
}

void Sprite::ShutDown()
{
	dbDeleteSprite(ID);
}