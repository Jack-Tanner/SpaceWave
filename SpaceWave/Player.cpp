#include "Player.h"
#include "Keyboard.h"
#include "SpriteHandler.h"
#include <DarkGDK.h>
#include <sstream>
using namespace Game;

void Player::Initilize(int id, string ImagePath, Vector2 vec)
{
	Position = vec;
	ImageID = 2;
	ID = id;
	Health = 100;
	Score = 0;
	Speed = 5;
	LastHurtTime = dbTimer();
	LastShootTime = dbTimer();
	dbSetImageColorKey(255, 0, 255);
	dbCreateAnimatedSprite(ID, const_cast<char*>(ImagePath.c_str()), 3, 2, ImageID);
	IsExploding = false;
	Alive = true;

}

void Player::Tick(SpriteHandler& Handler)
{
	if(!IsExploding)
	{
		if(!dbSpriteExist(ID))
			dbSprite(ID, Position.GetX(), Position.GetY(), ImageID);

		if(Health <= 0)
		{
			Health = 0;
			IsExploding = true;
			dbDeleteSprite(ID);
			dbSetImageColorKey(0, 0, 0);
			dbCreateAnimatedSprite(ID, "Explosion.bmp", 4, 5, ImageID);
			dbScaleSprite(ID, 25);
			dbPlaySound(2);
		}
	
		if(Keyboard::GetInstance()->IsKeyDown(DIK_W))
			Position -= Vector2(0, Speed);
		if(Keyboard::GetInstance()->IsKeyDown(DIK_S))
			Position += Vector2(0, Speed);
		if(Keyboard::GetInstance()->IsKeyDown(DIK_A))
			Position -= Vector2(Speed, 0);
		if(Keyboard::GetInstance()->IsKeyDown(DIK_D))
			Position += Vector2(Speed, 0);

		//Collision
		if(Position.GetX() <= 0)
			Position = Vector2(0, Position.GetY());
		else if((Position.GetX() + dbSpriteWidth(ID)) >= 800)
			Position = Vector2(800 - dbSpriteWidth(ID), Position.GetY());

		if(Position.GetY() <= 0)
			Position = Vector2(Position.GetX(), 0);
		else if((Position.GetY() + dbSpriteHeight(ID)) >= 600)
			Position = Vector2(Position.GetX(), (600 - dbSpriteHeight(ID)));

		if(dbMouseClick() == 1)
			Shoot(Handler);

	}

}

void Player::Draw()
{
	if(!IsExploding)
	{
		dbSetSpritePriority(ID, 3);
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
	else
	{

		if(Alive)
		{
			dbSprite(ID, Position.GetX(), Position.GetX(), ImageID);
			dbPlaySprite(ID, 1, 20, 100);
			if(dbSpriteFrame(ID) == 20)
				Alive = false;
		}
		else
		{
			//Game.ShowGameOver();
		}		
	}

	dbInk(RGB(0, 204, 0), 0);
	
	//Display Health & Score
	dbSetTextSize(20);
	dbText(10, 560, "Health");
	string str;
	stringstream ss;
	ss << "Score: " << Score;
	str = ss.str();
	dbText(600, 560, const_cast<char*>(str.c_str()));

	//Render Health Bar
	dbBox(10, 580, (20+Health), 590);
}

void Player::Hurt(int damage)
{
	if((dbTimer() - 500) >= LastHurtTime)
	{
		Health -= damage;
		LastHurtTime = dbTimer();
		IsHurting = true;
	}
}

void Player::AddScore(int amount)
{
	Score += amount;
}

void Player::Shoot(SpriteHandler& Handler)
{
	if((dbTimer() - 250) >= LastShootTime)
	{
		LastShootTime = dbTimer();
		Handler.AddBullet(3, Vector2(Position.GetX() + dbSpriteWidth(ID) - 10, Position.GetY()), 2, true);
		dbPlaySound(1);
	}
}