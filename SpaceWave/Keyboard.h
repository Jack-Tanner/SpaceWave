#pragma once
#include <dinput.h>
namespace Game
{
	class Keyboard
	{
	public:
		Keyboard()
		{
			for(int i = 0; i < 255; i++)
			{
				CurrentKeys[i] = false;
				PreviousKeys[i] = false;
				CurrentKeyLastPressed[i] = 0;
			}
		}

		~Keyboard()
		{
			delete pInstance;
		}

		bool IsKeyDown(unsigned int key);
		bool IsKeyUp(unsigned int key);	
		bool IsPreviousKeysKeyDown(unsigned int key);
		bool IsPreviousKeysKeyUp(unsigned int key);	
		void SetLastKeyPress(unsigned int key, int Time);
		int KeyLastPressed(unsigned int key);

		void Tick();

		static Keyboard* GetInstance();

	private:
		bool PreviousKeys[256];
		bool CurrentKeys[256];
		int CurrentKeyLastPressed[256];

		static Keyboard* pInstance;
	};
}