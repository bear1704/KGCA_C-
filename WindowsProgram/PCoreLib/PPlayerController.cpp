#include "PPlayerController.h"



PPlayerController::PPlayerController()
{
}


PPlayerController::~PPlayerController()
{
}

bool PPlayerController::Frame()
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
