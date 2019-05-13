#include "PCore.h"

HDC g_handle_off_screenDC;
HDC g_handle_screenDC;


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

bool PCore::PreRender()
{
	PatBlt(handle_off_screenDC, 0, 0, rectangle_client.right, rectangle_client.bottom, PATCOPY);
	return true;
}

bool PCore::Render()
{
	return true;
}

bool PCore::PostRender()
{
	BitBlt(handle_ScreenDC, 0, 0, rectangle_client.right, rectangle_client.bottom, handle_off_screenDC, 0, 0, SRCCOPY);
	return false;
}

bool PCore::Release()
{
	return true;
}

bool PCore::PCoreInit()
{
	handle_ScreenDC = GetDC(hWnd);
	g_handle_screenDC = handle_ScreenDC;

	handle_off_screenDC = CreateCompatibleDC(handle_ScreenDC);
	handle_off_screen_bitmap = CreateCompatibleBitmap(handle_ScreenDC, rectangle_client.right, rectangle_client.bottom);
	SelectObject(handle_off_screenDC, handle_off_screen_bitmap);

	background_color = RGB(0, 0, 0);
	handle_background_brush = CreateSolidBrush(background_color);
	SelectObject(handle_off_screenDC, handle_background_brush);

	g_handle_off_screenDC = handle_off_screenDC;


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

	timer.Render();
	PInput::GetInstance().Render();
	PSoundMgr::GetInstance().Render();
	PreRender();
	Render();
	PostRender();

	return true;
}

bool PCore::PCoreRelease()
{
	DeleteObject(handle_background_brush);
	ReleaseDC(hWnd, handle_ScreenDC);


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
