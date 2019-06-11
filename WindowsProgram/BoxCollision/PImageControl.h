#pragma once
#include "PUIComponent.h"

class PImageControl : public PUIComponent
{
public:
	PImageControl();
	virtual ~PImageControl();

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

};

