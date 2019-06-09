#pragma once
#include "TStd.h"
class TBitmap
{
public:
	// ºñÆ®¸Ê ÇÚµé
	HBITMAP  m_hBitmap;
	HDC      m_hMemDC;
	T_STR	 m_szPath;
	T_STR	 m_szName;
	int		 m_iIndex;
	float    m_fScale;
	BITMAP   m_BitmapInfo;
public:
	bool	Init();
	bool    Load(std::wstring filename);
	bool	Frame();
	bool	Render();
	bool    Draw(float x, float y, RECT rt, DWORD iMode = SRCCOPY);
	bool    Draw(float x, float y, RECT rt,	BLENDFUNCTION bf);
	bool    Draw(RECT rtDesk, RECT rtSrc,BLENDFUNCTION bf);
	bool    Draw(RECT rtDesk, RECT rtSrc, DWORD iMode = SRCCOPY);
	bool    DrawColorKey(float x, float y, RECT rt, COLORREF color);
	bool	Release();
public:
	TBitmap();
	virtual ~TBitmap();
};

