#pragma once
#include "PWindow.h"
#include "PInput.h"
#include "PTimer.h"
#include "PSoundMgr.h"
#include "P2DCamera.h"
#include "PWallAndPlatform.h"
#include "PObjectInfoManager.h"
#include "PObjectDataManager.h"


class PCore : public PWindow
{
public:
	PCore();
	virtual ~PCore();
public:
	PTimer timer;
	
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

