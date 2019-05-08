#pragma once
#include "PWindow.h"
class PCore :
	public PWindow
{
public:
	PCore();
	virtual ~PCore();

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

public:
	bool Run();


};

