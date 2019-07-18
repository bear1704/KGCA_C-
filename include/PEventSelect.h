#pragma once
#include "PSelectModel.h"
#include "PPacketManager.h"
#include "PUserManager.h"

const int kMaxEventSize = 64;

class PEventSelect :
	public PSelectModel
{
private:
	OperateMode operate_mode_;

public:
	HANDLE event_array_[kMaxEventSize];
	bool Init();
	bool Frame();


public:
	PEventSelect(SOCKET sock, OperateMode mode);
	virtual ~PEventSelect();

};

