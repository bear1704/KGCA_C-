#pragma once
#include "PSelectModel.h"
#include "PPacketManager.h"

const int kMaxEventSize = 64;

class PEventSelect :
	public PSelectModel
{
public:
	HANDLE event_array[kMaxEventSize];
	bool Init();
	bool Frame();

public:
	PEventSelect(SOCKET sock);
	virtual ~PEventSelect();

};

