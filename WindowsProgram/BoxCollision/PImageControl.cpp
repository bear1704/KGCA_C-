#include "PImageControl.h"



PImageControl::PImageControl()
{
}


PImageControl::~PImageControl()
{
}

bool PImageControl::Init()
{
	return false;
}

bool PImageControl::Frame()
{
	sprite_.Frame();
	set_collision_box_(collision_box_norm_);
	return false;
}

bool PImageControl::Render()
{
	sprite_.Draw();
	return false;
}

bool PImageControl::Release()
{
	PRectObject::Release();
	return true;
}
