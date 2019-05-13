#pragma once
#include "PWindow.h"
#include "PInput.h"
#include "PTimer.h"
#include "PSoundMgr.h"


class PCore :
	public PWindow
{
public:
	PCore();
	virtual ~PCore();
public:
	PTimer timer;
	HDC handle_ScreenDC;
	HDC handle_off_screenDC;
	HBITMAP handle_off_screen_bitmap;
	DWORD background_color;
	HBRUSH handle_background_brush;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();

private:
	bool PCoreInit();
	bool PCoreFrame();
	bool PCoreRender();
	bool PCoreRelease();
	void MessageProc(MSG msg);

public:
	bool Run();


};

