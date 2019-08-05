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

bool PCore::PreFrame()
{
	
	return true;
}

bool PCore::Frame()
{

	return true;
}

bool PCore::PostFrame()
{
	return true;
}

bool PCore::PreRender()
{
	
	return true;
}

bool PCore::Render()
{
	return true;
}

bool PCore::PostRender()
{
	
	return false;
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
	P2DCamera::GetInstance().Init();
	PCollision::GetInstance().Init();
	PWallAndPlatform::GetInstance().Init();
	PObjectInfoManager::GetInstance().Init();
	PObjectDataManager::GetInstance().Init();


	return Init();
}

bool PCore::PCoreFrame()
{
	PreFrame();
	timer.Frame();
	PInput::GetInstance().Frame();
	PSoundMgr::GetInstance().Frame();
	P2DCamera::GetInstance().Frame();
	Frame();
	return PostFrame();
}

bool PCore::PCoreRender()
{
	timer.Render();
	PInput::GetInstance().Render();
	PSoundMgr::GetInstance().Render();
	P2DCamera::GetInstance().Render();

	
	PreRender();
	Render();
	PostRender();
	return true;
}

bool PCore::PCoreRelease()
{
	timer.Release();
	PInput::GetInstance().Release();
	PSoundMgr::GetInstance().Release();
	P2DCamera::GetInstance().Release();

	return Release();
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
