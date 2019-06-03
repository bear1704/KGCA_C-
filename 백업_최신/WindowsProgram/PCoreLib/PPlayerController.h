#pragma once
#include "PRectObject.h"

class PPlayerController : public PRectObject
{
public:
	PPlayerController();
	virtual ~PPlayerController();

public:
	bool Frame();

};

