#pragma once
#include "PNetwork.h"
#include "PCore.h"


class Sample : public PCore
{
	PNetwork	network_;

public:
	bool Init() override;
	bool PreFrame() override;
	bool Frame() override;
	bool PostFrame() override;
	bool PostRender() override;
	bool Release() override;
	bool PacketProcessFromRecvPool();

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	Sample();
	virtual ~Sample();
	PNetwork& get_network_ref();


};

