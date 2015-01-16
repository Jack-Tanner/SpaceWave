#pragma once
#include <string>

struct MapHeader
{
	char* BackgroundImage;
	char* PlayerImage;

	int NumWaves;
};

enum MapDataType
{
	NONE,
	ENEMY,
	ITEM,
	WAVE
};

struct MapData
{
	MapDataType Type;

	int PosX, PosY;
	int ID;

	char* ImagePath;

	int WaveIDS[256];
	int CurrentWaveID;
	int TimeUntilNextWave;
};