#include "PStd.h"

#pragma once


class PPhysicsModule
{
public:
	PPhysicsModule();
	~PPhysicsModule();

	

private:
	bool isjump = false;
	

public:
	void Gravity(pPoint& position, float gravity);
	bool HitCalc();
	void Jump(float first_time, pPoint& position, float jump_force, float jump_length);
	void StartJump();
	bool get_isjump();
	float jump_init_time = 999.0f;
};

