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

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
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

