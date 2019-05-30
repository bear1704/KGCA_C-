#include "PMonster.h"



PMonster::PMonster()
{

}


PMonster::~PMonster()
{
}

bool PMonster::Init()
{

	return false;
}

bool PMonster::Frame()
{
	sprite_.Frame();
	set_collision_box_(collision_box_norm_);
	Movement();
	return false;
}

bool PMonster::Render()
{
	sprite_.Draw();
	return false;
}

bool PMonster::Release()
{
	sprite_.Release();
	return false;
}
