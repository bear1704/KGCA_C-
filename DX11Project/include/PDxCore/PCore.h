#pragma once
#include "PDevice.h"
#include "PInput.h"
#include "PTimer.h"
#include "PSoundMgr.h"
#include "P2DCamera.h"
#include "PWallAndPlatform.h"
#include "PObjectInfoManager.h"
#include "PObjectDataManager.h"


class PCore : public PDevice
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
	HANDLE handle_pen;

public:
	virtual bool Init();
	virtual bool PreFrame();
	virtual bool Frame();
	virtual bool PostFrame();
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

