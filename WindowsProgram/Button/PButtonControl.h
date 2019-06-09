#pragma once
#include "PUIComponent.h"

enum BTN
{
	NORMAL,
	HOVER,
	PUSH,
	DISABLE,
};


class PButtonControl : public PUIComponent
{
public:
	PButtonControl();
	~PButtonControl();
public:
	bool is_collision;
	int state_normal;
	int state_hover;
	int state_pushed;
	int state_disabled;
	bool is_select;
	PBitmap*  current_bitmap;
	PBitmap*  state_bitmap[4];
	void SetStateButton(int normal, int hover, int push, int disable, bool coll = false);
	virtual void Draw() override;
	//bool Set(TObjectInfo info, int id, int mask);
	bool  Frame();
	bool  Release();
	PUIComponent* Clone();
};

