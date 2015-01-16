#ifndef Editor_H
#define Editor_H

#include "Enemy.h"
#include "MapData.h"

#include <vector>
#include <string>
#include <fstream>

namespace Game
{
	class Editor1
	{
	public:
		Editor1();

		void Update();
		void Render();
		void LoadFile();

		void SaveMap(char* filepath);

	private:

		bool ShowGrid;
		int NextKeyPressTime;
		int NextMousePressTime;

		int GRIDX, GRIDY;

		int EnemyID;
		int CurrentWave;

		int NumEnemies;
		bool CanUndo;

		bool HasLoaded;
		std::string MapName;

		std::vector<Enemy> EnemyList;
		std::vector<MapData>WaveList;
		std::ofstream file;
	};
}
#endif