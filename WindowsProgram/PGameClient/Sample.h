#pragma once
#include "PNetwork.h"
#include "PCore.h"
#include "PCore.h"
#include "PMonster.h"
#include "PCollision.h"
#include "PObjectRotateUtil.h"
#include "PWallAndPlatform.h"
#include "PUIDataManager.h"
#include "PObjectDataManager.h"
#include "PScene.h"
#include "PParser.h"



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
	bool		Release();
	bool		PacketProcess();
	bool		Render();
	bool		InitDataLoad();

	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	void draw_test_rect(FLOAT_RECT rect);
	float timer;
	bool sound_flag;
private:
	float angle = 0;

public:
	Sample();
	virtual ~Sample();
};

