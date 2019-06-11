#pragma once
#include "PCore.h"
#include "PButtonControl.h"

class Sample : public PCore
{
public:
	Sample();
	~Sample();
	PButtonControl* button1;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void draw_test_rect(FLOAT_RECT rect);
};

PCORE_RUN(L"UI", 0, 0, 1024, 768);

