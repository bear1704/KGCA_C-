#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TInput.h"
#include "TSoundMgr.h"
class TCore : public TWindow
{
public:
	TTimer    m_Timer;
	bool	 m_bDebug;
	HDC		 m_hScreenDC;
	HDC		 m_hOffScreenDC;
	HBITMAP  m_hOffScreenBitmap;
	DWORD	 m_bkColor;
	HBRUSH	 m_hbrBack;
	HANDLE	 m_hPen;
	HFONT	 m_fontDefault;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();
	virtual bool DebugRender();
private:
	bool TCoreInit();
	bool TCoreFrame();
	bool TCoreRender();
	bool TCoreRelease();
	void MessageProc(MSG msg);
public:
	bool Run();
public:
	TCore();
	virtual ~TCore();
};

