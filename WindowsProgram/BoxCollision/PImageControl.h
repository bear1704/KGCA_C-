#pragma once
#include "PUIComponent.h"

class PImageControl : public PUIComponent
{
public:
	PImageControl();
	virtual ~PImageControl();
private:
	pPoint max_rect_size;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void SetRectListSize(FLOAT_RECT size);
	void set_max_rect_size(FLOAT_RECT size);
};

