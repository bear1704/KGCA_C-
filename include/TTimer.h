#pragma once
#include "TStd.h"
class TTimer
{
public:
	float     m_fSecondPerFrame; // 1프레임 경과시간
	float     m_fAccumulation; // 실행된 경과 시간
	int       m_iFPS; // 1초에 진행된 프레임 카운터
	DWORD	  m_dwBeforeTick;
	float     m_fFrameTime;
	DWORD     m_dwFrameCount;
	TCHAR     m_csBuffer[MAX_PATH];
public:
	bool       Init();
	bool       Frame();
	bool       Render();
	bool       Release();
public:
	TTimer();
	virtual ~TTimer();
};

