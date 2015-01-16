#include "GameState.h"
#include "Keyboard.h"
#include <fstream>
#include <sstream>
using namespace Game;

void GameState::Initilize()
{
	CurrentState = SPLASH;
	MapName = "p.map";
	
}

void GameState::SetCurrentState(States state)
{
	switch(CurrentState)
	{
	case SPLASH:
		{
			Splash.Shutdown();
			break;
		}
	case MENU:
		{
			Splash.Shutdown();
			break;
		}
	case PLAYING:
		{
			level.ShutdownLevel();
		}
	}

	CurrentState = state;

	switch(state)
	{
	case SPLASH:
		{
			Splash.Initilize();
			break;
		}
	case MENU:
		{
			Menu.Initilize();
			break;
		}
	case GAMEOVER:
		{
			GameOver();
			break;
		};
	case WIN:
		{
			Win();
			break;
		};
	case EDITOR:
		{
			edit.LoadFile();
			break;
		}
	}
}

void GameState::Tick()
{
	switch(CurrentState)
	{
	case SPLASH:
		{
			Splash.Tick(*this);
			break;
		}
	case MENU:
		{
			Menu.Tick(*this);
			break;
		}
	case LOADING:
		{
			level.LoadLevel(MapName, *this);
			break;
		}
	case PLAYING:
		{
			level.TickLevel(*this);
			break;
		}
	case EDITOR:
		{
			edit.Update();
			break;
		}
	}
}
void GameState::Draw()
{
	switch(CurrentState)
	{
	case SPLASH:
		{
			Splash.Draw();
			break;
		}
	case MENU:
		{
			Menu.Draw();
			break;
		}
	case PLAYING:
		{
			level.DrawLevel();
			break;
		};

		case EDITOR:
		{
			edit.Render();
			break;
		}
	}
}

void GameState::LoadGame()
{

	CurrentState = PLAYING;
}

void GameState::GameOver()
{
	dbCLS();

	HighScoreData highscore;
	highscore.score = Score;
	dbClearEntryBuffer();
	while(dbKeyState(28) != 1)
	{
		dbCLS(dbRGB(0, 0, 0));
		string txt;
		txt += dbEntry();

		if(txt != " ")
			highscore.name += txt;
		txt.clear();

		dbClearEntryBuffer();
		dbSetTextSize(72);
		dbCenterText(400, 200, "GAME OVER!");

		dbSetTextSize(26);
		string text;
		stringstream ss;
		ss << "Your Score: " << Score;
		text = ss.str();
		dbCenterText(400, 300, const_cast<char*>(text.c_str()));
	
		dbSetTextSize(18);
		dbText(30, 400, "Enter Your Name: ");

		dbText(306, 400, const_cast<char*>(highscore.name.c_str()));
		if(dbKeyState(14))
		{
			if(highscore.name.size() != 0)
			{
				highscore.name.erase(highscore.name.end()-1);
			}
		}
		dbSync();	
	}

	std::ofstream file;
	file.open("highscores.db", std::ios::binary | std::ios::app);

	file.write((char*)(&highscore), sizeof(HighScoreData));

	file.close();
	dbWait(500);
	CurrentState = MENU;
}

void GameState::Win()
{
	dbCLS();

	HighScoreData highscore;
	highscore.score = Score;
	dbClearEntryBuffer();
	while(dbKeyState(28) != 1)
	{
		dbCLS(dbRGB(0, 0, 0));
		string txt;
		txt += dbEntry();

		if(txt != " ")
			highscore.name += txt;
		txt.clear();

		dbClearEntryBuffer();
		dbSetTextSize(60);
		dbCenterText(400, 200, "GAME OVER, YOU WON!");

		dbSetTextSize(26);
		string text;
		stringstream ss;
		ss << "Your Score: " << Score;
		text = ss.str();
		dbCenterText(400, 300, const_cast<char*>(text.c_str()));
	
		dbSetTextSize(18);
		dbText(30, 400, "Enter Your Name: ");

		dbText(306, 400, const_cast<char*>(highscore.name.c_str()));
		if(dbKeyState(14))
		{
			if(highscore.name.size() != 0)
			{
				highscore.name.erase(highscore.name.end()-1);
			}
		}
		dbSync();	
	}

	std::ofstream file;
	file.open("highscores.db", std::ios::binary | std::ios::app);

	file.write((char*)(&highscore), sizeof(HighScoreData));

	file.close();
	dbWait(500);
	CurrentState = MENU;
}

void GameState::Shutdown()
{
	
}
