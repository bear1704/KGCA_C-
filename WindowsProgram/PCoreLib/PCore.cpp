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
	handle_ScreenDC = GetDC(hWnd); //스크린에 출력하기 위한 Device Context를 GetDC를 통해 생성한다.
	g_handle_screenDC = handle_ScreenDC; //다른 곳에서 참조할 수 있도록 전역변수와 스크린DC를 공유한다.

	handle_off_screenDC = CreateCompatibleDC(handle_ScreenDC); //백버퍼를 만들고, screenDC와 호환되도록 형태를 만든다.
	handle_off_screen_bitmap = CreateCompatibleBitmap(handle_ScreenDC, rectangle_client.right, rectangle_client.bottom); //백버퍼에 사용할 비트맵
	SelectObject(handle_off_screenDC, handle_off_screen_bitmap); //비트맵과 백버퍼를 바인드

	background_color = RGB(255, 255, 255);
	handle_background_brush = CreateSolidBrush(background_color); //백그라운드에 사용할 컬러 브러시(블랙)
	SelectObject(handle_off_screenDC, handle_background_brush); //브러시와 백버퍼를 바인드

	g_handle_off_screenDC = handle_off_screenDC;

	handle_pen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	SelectObject(handle_off_screenDC, handle_pen);

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
