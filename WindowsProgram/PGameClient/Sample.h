#pragma once
#include "PNetwork.h"
#include "PCore.h"




PScene* g_current_scene_;



class Sample : public PCore
{
	PNetwork		m_Network;
	HWND			m_hEdit;
	HWND			m_hButton;
	HWND			m_hList;
public:
	bool		Init();
	bool		PreFrame();
	bool		Frame();
	bool		PostRender();
	bool		Release();
	bool		PacketProcess();


	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Sample();
	virtual ~Sample();
};

