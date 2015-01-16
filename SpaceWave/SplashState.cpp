#include "SplashState.h"
#include "GameState.h"
#include "Keyboard.h"
#include <DarkGDK.h>

using namespace Game;

bool SplashState::Initilize()
{
	AddFontResource("Coalition_v2.ttf");
	return true;
}

void SplashState::Tick(GameState& gameState)
{
	if(Keyboard::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		Keyboard::GetInstance()->SetLastKeyPress(DIK_SPACE, dbTimer());
		gameState.SetCurrentState(GameState::MENU);
	}
}

void SplashState::Draw()
{
	dbCLS(dbRGB(255, 255, 255));
	dbSetTextToOpaque();

	dbInk(RGB(0, 0, 0), dbRGB(255, 255, 255));
	dbSetTextFont("Coalition");
	
	dbSetTextSize(72);
	dbCenterText(400, 150, "Space Wave");
	
	dbSetTextSize(24);
	dbCenterText(400, 300, "Press Space To Continue...");
	dbSync();
}

void SplashState::Shutdown()
{

}
