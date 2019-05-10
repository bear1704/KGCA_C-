#include "PInput.h"
#include <iostream>

PInputActionMap g_InputActionMap;


PInput::PInput()
{

}

bool PInput::Init()
{
	std::fill_n(keyboardKeyState, 256, KEYSTAT::KEY_FREE);
	return false;
}

bool PInput::Frame()
{
	g_InputActionMap.wKey = KeyCheck('W');
	g_InputActionMap.sKey = KeyCheck('S');
	g_InputActionMap.aKey = KeyCheck('A');
	g_InputActionMap.dKey = KeyCheck('D');
	g_InputActionMap.exitKey = KeyCheck(VK_ESCAPE);
	g_InputActionMap.jumpKey = KeyCheck(VK_SPACE);




	return false;
}

bool PInput::Release()
{
	return false;
}

bool PInput::Render()
{
	return false;
}


PInput::~PInput()
{
}


KEYSTAT PInput::KeyCheck(DWORD key)
{
	INT sKey = GetAsyncKeyState(key);

	if (sKey & 0x8000)
	{
		if (keyboardKeyState[key] == KEYSTAT::KEY_FREE || keyboardKeyState[key] == KEYSTAT::KEY_UP)
		{
			keyboardKeyState[key] = KEYSTAT::KEY_PUSH;
		}
		else
		{
			keyboardKeyState[key] = KEYSTAT::KEY_HOLD;
		}
	}
	else
	{
		if (keyboardKeyState[key] == KEYSTAT::KEY_PUSH || keyboardKeyState[key] == KEYSTAT::KEY_HOLD)
		{
			keyboardKeyState[key] = KEYSTAT::KEY_UP;
		}
		else
		{
			keyboardKeyState[key] = KEYSTAT::KEY_FREE;
		}

	}
	return keyboardKeyState[key];
}
