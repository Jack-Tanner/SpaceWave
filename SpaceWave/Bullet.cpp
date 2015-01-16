#include "Bullet.h"
#include "SpriteHandler.h"
using namespace Game;

void Bullet::Initilize(int id, int ImgID, Vector2 Pos, int Direction, bool IsGood)
{
	ID = id;
	ImageID = ImgID;
	Position = Pos;
	Alive = true;
	this->Direction = Direction;
	Speed = Vector2(8, 0);
	Good = IsGood;
}

void Bullet::Tick(SpriteHandler& Handler)
{
	if(Alive)
	{
		if(Position.GetX() > 820)
			Alive = false;
		else if(Position.GetX() < -20)
			Alive = false;

		if(Position.GetY() > 620)
			Alive = false;
		else if(Position.GetY() < -20)
			Alive = false;

		if(Direction == 2)
			Position += Speed;
		else if(Direction == 4)
			Position -= Speed;

		if(!Good)
		{
			if(dbSpriteCollision(ID, 1))
			{
				Handler.GetPlayer()->Hurt(10);
				Alive = false;
				this->ShutDown();
			}
		}
		else
		{
			if(Handler.CheckBulletHit(ID, 10))
			{
				this->ShutDown();
				Alive = false;
			}
			
		}
	}
}
