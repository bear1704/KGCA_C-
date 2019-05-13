#pragma once
#include "PCore.h"
class Sample :
	public PCore
{
public:
	Sample();
	~Sample();
public:
	bool Init();
	bool Frame();
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

};

