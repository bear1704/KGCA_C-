#pragma once
#include "TStd.h"



class TInput : public TSingleton<TInput>
{
	friend class TSingleton<TInput>;
public:
	DWORD m_dwKeyState[256];
	DWORD m_dwMouseState[3];
	DWORD m_dwBeforeMouseState[3];
	POINT m_MousePos;
public:
	bool       Init();
	bool       Frame();
	bool       Render();
	bool       Release();
	DWORD      Key(DWORD dwKey);
	LRESULT		MsgProc(MSG msg);
private:
	DWORD      KeyCheck(DWORD dwKey);	
private:
	TInput();
public:
	virtual ~TInput();
};
#define I_Input TInput::GetInstance()
