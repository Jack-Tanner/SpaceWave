#include "Level.h"
#include "GameState.h"
#include <DarkGDK.h>
#include "Vector2.h"

using namespace Game;
using namespace Math;

void Level::LoadLevel(string filepath, GameState& gameState)
{
	dbCLS(dbRGB(255, 255, 255));
	dbInk(dbRGB(0, 0, 0), dbRGB(255, 255, 255));
	dbCenterText(400, 100, "Loading...");
	dbSync();

	FilePath = filepath;
	dbLoadImage("Media/Backdrop.png", 1);
	dbSetImageColorKey(255, 0, 255);
	dbLoadImage("Media/Bullet.bmp", 3);
	dbLoadSound("Media/laser.wav", 1);
	dbLoadSound("Media/explosion.wav", 2);
	spriteHandler.AddExplosion(Vector2(800, 400));
	spriteHandler.AddPlayer("Media/Ship.bmp", Vector2(300, 300));

	Backgroundx = 0;
	Backgroundx1 = 800;

	std::ifstream file(FilePath, std::ios::in|std::ios::binary);
	if(file.is_open())
	{
		MapHeader MapInfo;
		file.read((char*)(&MapInfo), sizeof(MapHeader));
		MapData* Entity;
		while(!file.eof())
		{
			Entity = new MapData();
			file.read((char*)(Entity), sizeof(MapData));
			
			if(Entity->Type == ENEMY)
			{
				spriteHandler.AddEnemy("Media/Ship.bmp", Vector2((Entity->PosX + 800), Entity->PosY), Entity->ID);
			}
			if(Entity->Type == WAVE)
			{
				spriteHandler.AddWave(*Entity);
			}

			delete Entity;
		}
	}

	for(int x = 4000; x < (4000+spriteHandler.GetEnemyCount() + 2); x++)
	{
		dbSetImageColorKey(0, 0, 0);
		dbCreateAnimatedSprite(x, "Media/Explosion.bmp", 4, 5, 160);
	}

	dbCLS(dbRGB(255, 255, 255));
	dbCenterText(400, 50, "Instructions");
	dbSetTextSize(26);
	dbCenterText(400, 150, "Click To Shoot");
	dbCenterText(400, 200, "Press W,A,S,D To Move");
	dbCenterText(400, 250, "Press P To Pause");
	dbCenterText(400, 350, "Press Any Key To Continue!");
	dbSync();
	dbWaitKey();

	
	
	gameState.SetCurrentState(GameState::PLAYING);
}

void Level::TickLevel(GameState& gameState)
{
	Backgroundx -= 2;
	Backgroundx1 -= 2;
	if(Backgroundx <= -800)
		Backgroundx = 800;
	if(Backgroundx1 <= -800)
		Backgroundx1 = 800;

	spriteHandler.Tick();

	if(spriteHandler.GetPlayer()->GetHealth() <= 0)
	{
		gameState.SetScore(spriteHandler.GetPlayer()->GetScore());
		ShutdownLevel();
		dbWait(300);
		gameState.SetCurrentState(GameState::GAMEOVER);
	}
	if(spriteHandler.GetCurrentWave() > spriteHandler.GetMaxWaves())
	{
		gameState.SetScore(spriteHandler.GetPlayer()->GetScore());
		ShutdownLevel();
		dbWait(300);
		gameState.SetCurrentState(GameState::WIN);
	}
}

void Level::DrawLevel()
{
	dbCLS();
	dbPasteImage(1, Backgroundx, 0);
	dbPasteImage(1, Backgroundx1, 0);
	spriteHandler.Draw();
	dbSync();
}

void Level::ShutdownLevel()
{
	spriteHandler.Shutdown();
	
}
