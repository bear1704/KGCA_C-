#pragma once
#include "pCore.h"
#include "PBitmap.h"
#include "PRectObject.h"


class PPlayer : public PRectObject
{
public:
	bool Frame()
	{
		if (g_InputActionMap.wKey == KEYSTAT::KEY_HOLD)
		{
			position_.y -= moveSpeed_ * g_SecondPerFrame;
		}
		if (g_InputActionMap.sKey == KEYSTAT::KEY_HOLD)
		{
			position_.y += moveSpeed_ * g_SecondPerFrame;
		}
		if (g_InputActionMap.aKey == KEYSTAT::KEY_HOLD)
		{
			position_.x -= moveSpeed_ * g_SecondPerFrame;
		}
		if (g_InputActionMap.dKey == KEYSTAT::KEY_HOLD)
		{
			position_.x += moveSpeed_ * g_SecondPerFrame;
		}
		return true;
	}

public:
	PPlayer() {};
	~PPlayer() {};

};

class Sample : public PCore
{
private:
	PRectObject character_npc_;
	PPlayer hero_;
	PRectObject object_background_bitmap_;

public:
	Sample();
	~Sample();
public:
	bool Frame();
	bool Init();
	bool Render();
	bool Release();
};
