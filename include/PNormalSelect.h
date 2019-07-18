#pragma once
#include "PSelectModel.h"

class PNormalSelect : public PSelectModel
{
public:
	FD_SET read_set_;
	FD_SET write_set_;

public:
	virtual bool Init();
	virtual bool Frame();

public:
	PNormalSelect(SOCKET sock);
	virtual ~PNormalSelect();


};

