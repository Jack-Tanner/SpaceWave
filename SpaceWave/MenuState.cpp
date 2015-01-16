#include "MenuState.h"
#include "GameState.h"
#include "Keyboard.h"
#include <DarkGDK.h>
#include <sstream>
#include <fstream>
using namespace Game;

bool MenuState::Initilize()
{
	State = NONE;
	Selection = 1;
	Backgroundx = 0;
	Backgroundx1 = 800;
	dbLoadImage("Media/Backdrop.png", 1);
	return true;
}

void MenuState::Tick(GameState& gameState)
{
	Backgroundx -= 2;
	Backgroundx1 -= 2;
	if(Backgroundx <= -800)
		Backgroundx = 800;
	if(Backgroundx1 <= -800)
		Backgroundx1 = 800;

	if(State == NONE)
	{
		if(Keyboard::GetInstance()->IsKeyDown(DIK_UP) && dbTimer() - 100 >= Keyboard::GetInstance()->KeyLastPressed(DIK_UP))
		{
				Keyboard::GetInstance()->SetLastKeyPress(DIK_UP, dbTimer());
				--Selection;
		}
		if(Keyboard::GetInstance()->IsKeyDown(DIK_DOWN) && dbTimer() - 100 >= Keyboard::GetInstance()->KeyLastPressed(DIK_DOWN))
		{
			Keyboard::GetInstance()->SetLastKeyPress(DIK_DOWN, dbTimer());
			++Selection;
		}

		if(Selection < 1)
			Selection = 1;
		else if(Selection > 5)
			Selection = 5;

		if(Keyboard::GetInstance()->IsKeyDown(DIK_SPACE) && dbTimer() - 100 >= Keyboard::GetInstance()->KeyLastPressed(DIK_SPACE))
		{
			Keyboard::GetInstance()->SetLastKeyPress(DIK_SPACE, dbTimer());
			switch(Selection)
			{
			case 1:
				gameState.SetCurrentState(GameState::LOADING);
				return;
				break;
			case 2:
				State = LOADMAP;
				break;
			case 3:
				State = HIGHSCORES;
				break;
			case 4:
				gameState.SetCurrentState(GameState::EDITOR);
				break;
			case 5:
				gameState.SetCurrentState(GameState::EXIT);
				break;
			}
		}
	}
	else if(State == HIGHSCORES)
		TickHighscores();
	else if(State == LOADMAP)
		TickLoadMap(gameState);
}

void MenuState::Draw()
{
	dbCLS(dbRGB(255, 255, 255));
	dbPasteImage(1, Backgroundx, 0);
	dbPasteImage(1, Backgroundx1, 0);

	if(State == NONE)
		{
		//Draw Menu Text
		dbSetTextToOpaque();
		dbInk(RGB(0, 204, 0), dbRGB(0, 0, 0));
		dbSetTextFont("Coalition");
		dbSetTextSize(72);
		dbCenterText(400, 80, "Space Wave");
		
		dbSetTextSize(48);
		dbCenterText(400, 200, "Play");
		dbCenterText(400, 260, "Load Map");
		dbCenterText(400, 320, "High Scores");
		dbCenterText(400, 380, "Editor");
		dbCenterText(400, 440, "Exit");

		if(Selection == 1)
		{
			dbInk(RGB(0, 130, 0), dbRGB(0, 0, 0));
			dbSetTextSize(48);
			dbCenterText(400, 200, "Play");
		}
		else if(Selection == 2)
		{
			dbInk(RGB(0, 130, 0), dbRGB(0, 0, 0));
			dbSetTextSize(48);
			dbCenterText(400, 260, "Load Map");
		}
		else if(Selection == 3)
		{
			dbInk(RGB(0, 130, 0), dbRGB(0, 0, 0));
			dbSetTextSize(48);
			dbCenterText(400, 320, "High Scores");
		}
		else if(Selection == 4)
		{
			dbInk(RGB(0, 130, 0), dbRGB(0, 0, 0));
			dbSetTextSize(48);
			dbCenterText(400, 380, "Editor");
		}
		else if(Selection == 5)
		{
			dbInk(RGB(0, 130, 0), dbRGB(0, 0, 0));
			dbSetTextSize(48);
			dbCenterText(400, 440, "Exit");
		}
	}
	else if(State == HIGHSCORES)
		DrawHighscores();

	dbSync();
}

void MenuState::TickHighscores()
{
	//Update Highscores
	if(Keyboard::GetInstance()->IsKeyDown(DIK_SPACE) && dbTimer() - 100 >= Keyboard::GetInstance()->KeyLastPressed(DIK_SPACE))
	{
		Keyboard::GetInstance()->SetLastKeyPress(DIK_SPACE, dbTimer());
		State = NONE;
	}
}

void MenuState::TickLoadMap(GameState& gameState)
{
	std::ifstream file("maps.txt", std::ios::in);
	std::string line;
	std::vector<std::string> MapList;

	if(file.is_open())
	{
		while(!file.eof())
		{
			if(std::getline(file, line))
			{
				MapList.push_back(line);
			}
			line.clear();
		}
	}

	file.close();

	dbWait(200);

	bool CanOpen = false;

	int selection = 1;
	while(dbKeyState(57) == 0)
	{
		dbCLS(dbRGB(255, 255, 255));
		Backgroundx -= 2;
		Backgroundx1 -= 2;
		if(Backgroundx <= -800)
			Backgroundx = 800;
		if(Backgroundx1 <= -800)
			Backgroundx1 = 800;
		dbPasteImage(1, Backgroundx, 0);
		dbPasteImage(1, Backgroundx1, 0);

		dbInk(RGB(0, 204, 0), dbRGB(0, 0, 0));
		dbSetTextSize(72);
		dbCenterText(400, 80, "Map Selection");

		if(MapList.size() != 0)
		{
			CanOpen = true;
			int x = 1;
			std::vector<std::string>::iterator it1;
			for(it1 = MapList.begin(); it1 != (MapList.end()); it1++)
			{
				dbSetTextSize(26);
				dbInk(RGB(0, 204, 0), dbRGB(0, 0, 0));
				dbText(250, (170 + (30*x)), const_cast<char*>(it1->c_str()));
				x++;
			}

			if(dbUpKey() == 1)
			{
				selection--;
			}
			else if(dbDownKey() == 1)
			{
				selection++;
			}

			if(selection < 1)
				selection = 1;
			else if(selection > MapList.size())
				selection = MapList.size();

			dbSetTextSize(26);
			dbInk(RGB(0, 130, 0), dbRGB(0, 0, 0));
			dbText(250, (170 + (30*selection)), const_cast<char*>(MapList[selection-1].c_str()));

		}
		else
		{
			CanOpen = false;
			dbSetTextSize(26);
			dbInk(RGB(0, 204, 0), dbRGB(0, 0, 0));
			dbText(250, 200, "No Maps Avaliable!");
		}
		dbSync();
	}

	if(CanOpen)
	{
		gameState.SetMapPath(MapList[selection-1]);
		gameState.SetCurrentState(GameState::LOADING);
	}
	else
	{
		State = NONE;
	}

	dbWait(200);
	State = NONE;
	MapList.clear();

}

void MenuState::DrawHighscores()
{
	dbInk(RGB(0, 204, 0), dbRGB(0, 0, 0));
	dbSetTextSize(72);
	dbCenterText(400, 80, "High Scores");

	std::ifstream file;
	file.open("highscores.db", std::ios::in|std::ios::binary);
	
	std::vector<HighScoreData> highscorelist;

	if(file.is_open())
	{
		//Read Highscore File
		while(!file.eof())
		{
			HighScoreData data;
			if(file.read((char*)(&data), sizeof(HighScoreData)))
			{
				if(highscorelist.size() < 11)
					highscorelist.push_back(data);
			}
		}

		//Using Bubble Sort, Sort The Highscores In Decending Order
		for(int i = 0; i < highscorelist.size();i++)
		{
			for(int j = i+1; j < highscorelist.size(); j++)
			{
				if(highscorelist[i].score < highscorelist[j].score)
				{
					std::swap(highscorelist[i],highscorelist[j]);
				}
			}
		}

		//Print Top 10 Highscores
		int x = 1;
		std::vector<HighScoreData>::iterator it1;
		for(it1 = highscorelist.begin(); it1 != (highscorelist.end()); it1++)
		{
			dbSetTextSize(24);
			std::string text;
			std::stringstream ss;
			ss << x << ". " << it1->name << "      " << it1->score;
			text = ss.str();
			dbText(250, (200 + (30*x)), const_cast<char*>(text.c_str()));
			x++;
		}
	}
	else
	{
		dbSetTextSize(24);
		dbText(250, 230, "No Highscores!");
	}
	file.close();
	
}

void MenuState::Shutdown()
{

}
