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
	timer.Init();
	PInput::GetInstance().Init();
	PSoundMgr::GetInstance().Init();
	return Init();
}

bool PCore::PCoreFrame()
{
	timer.Frame();
	PInput::GetInstance().Frame();
	PSoundMgr::GetInstance().Frame();
	return Frame();
}

bool PCore::PCoreRender()
{
	timer.Frame();
	PInput::GetInstance().Render();
	PSoundMgr::GetInstance().Render();
	return Render();
}

bool PCore::PCoreRelease()
{
	timer.Release();
	PInput::GetInstance().Release();
	PSoundMgr::GetInstance().Release();
	return true;
}

void PCore::MessageProc(MSG msg)
{
	PInput::GetInstance().MsgProc(msg);
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
			MessageProc(msg);
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
