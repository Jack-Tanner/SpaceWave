#include "Editor.h"
#include "Vector2.h"
#include <DarkGDK.h>

using namespace Game;
using namespace Math;

Editor1::Editor1()
{
	ShowGrid = false;
	NextKeyPressTime = dbTimer();
	NextMousePressTime = dbTimer();
	GRIDX = 40;
	GRIDY = 30;
	EnemyID = 1;
	CurrentWave = 0;
	NumEnemies = 2;
	CanUndo = false;
	HasLoaded = false;
}

void Editor1::LoadFile()
{
	dbClearEntryBuffer();
	while(dbKeyState(28) != 1)
	{
		dbCLS(dbRGB(255, 255, 255));
		MapName += dbEntry();

		dbClearEntryBuffer();
		dbInk(dbRGB(0, 0, 0), dbRGB(255, 255, 255));
		dbSetTextSize(26);
		dbCenterText(300, 100, "Enter A Name For The Map: ");
		dbCenterText(200, 300, (char*)MapName.c_str());
		if(dbKeyState(14) == 1)
		{
			if(MapName.size() != 0)
			{
				MapName.erase(MapName.end()-1);
			}
		}
		dbSync();	
	}
	MapName += ".map";
	file.open(MapName, std::ios::binary);

	if(!file.is_open())
	{
		dbWait(200);
		dbClearEntryBuffer();
		dbCLS(dbRGB(255, 255, 255));
		dbCenterText(400, 300, "File Name Incorrect!");
		dbCenterText(400, 330, "Use only Letters and Numbers!");
		dbSync();
		dbWaitKey();
		HasLoaded = false;
		MapName.clear();
	}
	else
	{
		HasLoaded = true;
	}

	std::ofstream mapfile;
	mapfile.open("maps.txt", std::ios::app);
	mapfile << MapName << std::endl;
	
}

void Editor1::Update()
{
	if(!HasLoaded)
	{
		LoadFile();
	}

	if(WaveList.size() == 0)
	{
		MapData FirstWave;
		FirstWave.Type = WAVE;
		FirstWave.CurrentWaveID = 0;
		FirstWave.TimeUntilNextWave = 5000;

		for(int i = 0; i <= 255; i++)
		{
			FirstWave.WaveIDS[i] = 0;
		}

		WaveList.push_back(FirstWave);
	}

	if(dbTimer() >= NextMousePressTime)
	{
		if(dbMouseClick() == 1)
		{
			Enemy enemy;
			enemy.Initilize(NumEnemies, 10, "Media/Ship.bmp", Vector2(dbMouseX(), dbMouseY()), EnemyID);
			enemy.SetPos(Vector2((dbMouseX() - (enemy.GetWidth() / 2)), ((dbMouseY() - (enemy.GetHeight() / 2)))));
			enemy.SetActive(true);

			//Add to current wave
			WaveList[CurrentWave].WaveIDS[WaveList[CurrentWave].CurrentWaveID] = EnemyID;
			WaveList[CurrentWave].CurrentWaveID++;

			EnemyList.push_back(enemy);
			EnemyID++;
			NumEnemies += 2;

			CanUndo = true;

			NextMousePressTime = dbTimer() + 200;
		}
	}

	if(dbTimer() >= NextKeyPressTime)
	{
		if(dbRightKey() == 1)
		{
			CurrentWave++;
			
			if(CurrentWave >= (WaveList.size()))
			{
				MapData NewWave;
				NewWave.Type = WAVE;
				NewWave.CurrentWaveID = 0;
				NewWave.TimeUntilNextWave = 5000;

				for(int i = 0; i <= 255; i++)
				{
					NewWave.WaveIDS[i] = 0;
				}

				WaveList.push_back(NewWave);
			}

			NextKeyPressTime = dbTimer() + 200;
		}
		
		else if(dbLeftKey() == 1)
		{
			if(CurrentWave != 0)
				CurrentWave--;
			NextKeyPressTime = dbTimer() + 200;
		}

		else if(dbKeyState(34) == 1)
		{
			if(ShowGrid)
				ShowGrid = false;
			else
				ShowGrid = true;
			NextKeyPressTime = dbTimer() + 200;
		}

		else if(dbKeyState(44) == 1)
		{
			std::vector<Enemy>::iterator ss;
			ss = EnemyList.end() - 1;
			if(CanUndo)
			{
				ss->ShutDown();
				EnemyList.erase(ss);
				NumEnemies -= 2;

				if(NumEnemies == 2)
					CanUndo = false;
			}
			
			NextKeyPressTime = dbTimer() + 200;
		}

		else if(dbKeyState(26) == 1)
		{
			if(GRIDX <= 8 || GRIDY <= 8)
			{
				GRIDY = 8;
				GRIDX = 8;
			}

			GRIDY -= 2;
			GRIDX -= 2;
			NextKeyPressTime = dbTimer() + 200;
		}

		else if(dbKeyState(27) == 1)
		{
			GRIDY += 2;
			GRIDX += 2;
			NextKeyPressTime = dbTimer() + 200;
		}

		else if(dbKeyState(31) == 1)
		{
			SaveMap(const_cast<char*>(MapName.c_str()));
			NextKeyPressTime = dbTimer() + 200;
		}
	}
}


void Editor1::Render()
{
	dbCLS(dbRGB(0, 0, 0));
	if(HasLoaded)
	{
		char text[32];
		dbInk(RGB(0, 204, 0), 0);
		dbSetTextSize(22);
		sprintf(text, "Wave: %d / %d", CurrentWave+1, WaveList.size());
		dbText(0, 570, text);
		//Draw Grid
		if(ShowGrid)
		{
			dbInk(dbRGB(150, 150, 150), dbRGB(0, 0, 0));
			for(int i = 0; i < dbScreenWidth(); i += GRIDX)
			{
				dbLine(i, 0, i, dbScreenHeight());
			}
			for(int i = 0; i < dbScreenHeight(); i += GRIDY)
			{
				dbLine(0, i, dbScreenWidth(), i);
			}
		}

		std::vector<Enemy>::iterator it;
		for(it = EnemyList.begin(); it != EnemyList.end(); it++)
		{
			(*it).Hide();
			//Check If In Current Wave
			for(int i = 0; i <= 255; i++)
			{
				if((*it).GetWaveID() == WaveList[CurrentWave].WaveIDS[i])
				{
					(*it).Draw();
					break;
				}
			}
		}
	}
	dbSync();
}

void Editor1::SaveMap(char* filepath)
{
	if(!file.is_open())
	{
		file.open(MapName, std::ios::binary);
	}
	else
	{
		MapHeader Header;
		Header.BackgroundImage = "Media/Backdrop.png";
		Header.PlayerImage = "Media/ship.bmp";
		file.write((char*)(&Header), sizeof(MapHeader));

		std::vector<Enemy>::iterator it;
		for(it = EnemyList.begin(); it != EnemyList.end(); it++)
		{
			MapData Data;
			Data.ImagePath = "Media/Ship.bmp";
			Data.PosX = (*it).GetPosition().GetX();
			Data.PosY = (*it).GetPosition().GetY();
			Data.ID = (*it).GetWaveID();
			Data.Type = ENEMY;
			file.write((char*)(&Data), sizeof(MapData));
	
		}

		std::vector<MapData>::iterator et;
		for(et = WaveList.begin(); et != WaveList.end(); et++)
		{
			MapData data;
			data.Type = WAVE;
			data.CurrentWaveID = et->CurrentWaveID;
			for(int xy = 0; xy < 255; xy++)
			{
				data.WaveIDS[xy] = et->WaveIDS[xy];
			}
			data.TimeUntilNextWave = et->TimeUntilNextWave;
			file.write((char*)(&data), sizeof(MapData));
		}
	
		file.close();
	}
}