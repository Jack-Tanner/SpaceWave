#pragma once
#include "Vector2.h"
#include <DarkGDK.h>
using namespace Math;

namespace Game
{
	class SpriteHandler;

	class Sprite
	{
	public:
		virtual void Initilize(int id, int ImageID, Vector2 Pos);
		virtual void Tick(SpriteHandler& Handler);
		virtual void Draw();
		virtual void ShutDown();

		void SetPos(Vector2 vec){Position = vec;}

		int GetID(){return ID;};

		int GetWidth(){return dbSpriteWidth(ID);}
		int GetHeight(){return dbSpriteHeight(ID);}

		bool IsAlive(){return Alive;}
		void SetAlive(bool alive){Alive = alive;}

		void SetWaveID(int id){WaveID = id;}
		int GetWaveID(){return WaveID;}

		Vector2 GetPosition(){return Position;}

		void Hide(){dbHideSprite(ID);}
	
	protected:
		int WaveID, ID, ImageID;
		Vector2 Position;
		bool Alive;

	};
}