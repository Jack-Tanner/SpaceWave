#include "Keyboard.h"
#include <DarkGDK.h>
using namespace Game;

bool Keyboard::IsKeyDown(unsigned int key)
{
	return CurrentKeys[key];
}

bool Keyboard::IsKeyUp(unsigned int key)
{
	return !CurrentKeys[key];
}

bool Keyboard::IsPreviousKeysKeyDown(unsigned int key)
{
	return PreviousKeys[key];
}

bool Keyboard::IsPreviousKeysKeyUp(unsigned int key)
{
	return !PreviousKeys[key];
}

void Keyboard::Tick()
{
	for(int i = 0; i < 255; i++)
	{
		PreviousKeys[i] = CurrentKeys[i];
	}

	for(int x = 0; x < 255; x++)
	{
		CurrentKeys[x] = dbKeyState(x);

	}
}

void Keyboard::SetLastKeyPress(unsigned int key, int Time)
{
	CurrentKeyLastPressed[key] = Time;
}

int Keyboard::KeyLastPressed(unsigned int key)
{
	return CurrentKeyLastPressed[key];
}

Keyboard* Keyboard::GetInstance()
{
	if(pInstance == nullptr)
	{
		Keyboard::pInstance = new Keyboard();
	}
	
	return Keyboard::pInstance;
}

Keyboard* Keyboard::pInstance = nullptr;