#pragma once
#include "PNetwork.h"
#include "PServerInstructionProcessor.h"

class Sample
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

private:
	std::thread instruction_process_thread_;

	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:

	Sample();
	virtual ~Sample();
};

