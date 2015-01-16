#pragma once
#include "BaseState.h"
#include "SplashState.h"
#include "MenuState.h"
#include "Level.h"
#include "Editor.h"
#include <string>

using namespace std;

namespace Game
{
	struct HighScoreData
	{
		string name;
		int score;
	};

	class GameState
	{
	public:
		enum States {SPLASH, LOADING, PAUSED, MENU, PLAYING, EXIT, GAMEOVER, EDITOR, WIN};

		States GetCurrentState(){return CurrentState;}
		void SetCurrentState(States state);
		void Initilize();
		void Tick();
		void Draw();
		void Shutdown();
		void GameOver();
		void Win();
		void LoadGame();

		void SetScore(int score){Score = score;}
		void SetMapPath(string path){MapName = path;}

	private:
		States CurrentState;
		SplashState Splash;
		MenuState Menu;
		Level level;
		Editor1 edit;

		int Score;
		string MapName;
	};
}