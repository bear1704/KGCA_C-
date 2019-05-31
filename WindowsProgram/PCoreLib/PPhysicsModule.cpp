#include "PPhysicsModule.h"



PPhysicsModule::PPhysicsModule() 
{

}


PPhysicsModule::~PPhysicsModule()
{
}

void PPhysicsModule::Jump(float first_time, pPoint & position, float jump_force,float jump_length)
{
	
	float last_time = g_fGameTimer;
	if ((last_time - first_time) <= (jump_length - jump_length/5) && isjump == true)
	{
		position.y -= jump_force * g_SecondPerFrame;
	}
	else if ((last_time - first_time) >= (jump_length - jump_length / 5)&& (last_time - first_time) <= jump_length && isjump == true)
	{
   		position.y = position.y;
	}
	else 
	{
 		isjump = false;
	}
	

}

void PPhysicsModule::StartJump()
{
	isjump = true;
	jump_init_time = g_fGameTimer;
}


void PPhysicsModule::Gravity(pPoint & position, float gravity)
{
	if (isjump == false)
		position.y += gravity * g_SecondPerFrame;
}

bool PPhysicsModule::HitCalc()
{
	return true;
}
