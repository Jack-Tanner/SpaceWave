#include "Game.h"
// #include "Keyboard.h"
using namespace Game;

bool GameHandler::Init(string title, GameVector screenSize)
{
	Title = title;
	ScreenSize = screenSize;
	AddFontResource("Media/Coalition_v2.ttf");
	dbSyncOn();
	dbSyncRate(60);
	dbSetDisplayMode(800, 600, 32);
//	gameState.Initilize();
	return true;
}

void GameHandler::MainLoop()
{
	//while(gameState.GetCurrentState() != GameState::EXIT)
	//{
	//	Keyboard::GetInstance()->Tick();
	//	gameState.Tick();
	//	gameState.Draw();

	//	if(Keyboard::GetInstance()->IsKeyDown(1))
	//	{
	//		Shutdown();
	//		gameState.SetCurrentState(GameState::EXIT);
	//	}
	//}
}

void GameHandler::Shutdown()
{
//	gameState.Shutdown();
}
