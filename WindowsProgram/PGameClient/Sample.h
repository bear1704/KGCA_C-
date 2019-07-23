#pragma once
#include "PNetwork.h"
#include "PMonster.h"
#include "PCollision.h"
#include "PObjectRotateUtil.h"
#include "PWallAndPlatform.h"
#include "PUIDataManager.h"
#include "PObjectDataManager.h"
#include "PScene.h"
#include "PCore.h"
#include "PParser.h"
#include "PInstructionProcessor.h"



PScene* g_current_scene_;



class Sample : public PCore
{
	PNetwork		m_Network;
	HWND			m_hEdit;
	HWND			m_hButton;
	HWND			m_hList;
public:
	bool		Init();
	bool		PreFrame() override;
	bool		Frame();
	bool		Release();
	bool		Render();
	bool		InitDataLoad();

	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//LRESULT CALLBACK DlgProc(HWND hDlg,
	//	UINT iMessage, WPARAM wParam, LPARAM lParam);
public:
	void draw_test_rect(FLOAT_RECT rect);
	float timer;
	bool sound_flag;

private:
	float angle = 0;
	std::thread instruction_process_thread_;
public:
	Sample();
	virtual ~Sample();
};

