#include "PCore.h"



PCore::PCore()
{
}


PCore::~PCore()
{
}

bool PCore::Init()
{
	return true;
}

bool PCore::Frame()
{

	return true;
}

bool PCore::Render()
{
	return true;
}

bool PCore::Release()
{
	return true;
}

bool PCore::PCoreInit()
{
	PInput::GetInstance().Init();
	return true;
}

bool PCore::PCoreFrame()
{
	PInput::GetInstance().Frame();
	return true;
}

bool PCore::PCoreRender()
{
	return true;
}

bool PCore::PCoreRelease()
{
	return true;
}

bool PCore::Run()
{
	PCoreInit();
	MSG msg = { 0, };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			PCoreFrame();
			PCoreRender();
		}
	}

	PCoreRelease();

	return true;
}
