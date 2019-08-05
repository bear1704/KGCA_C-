#include "PTimer.h"

float g_SecondPerFrame = 0.0f;
float g_fGameTimer = 0.0f;



bool PTimer::Init()
{
	beforeTick = timeGetTime();

	return true;
}

bool PTimer::Frame()
{
	DWORD currentTick = timeGetTime();
	DWORD elapseTick = currentTick - beforeTick;
	
	secondPerFrame = elapseTick / 1000.0f;
	accumulationTime += secondPerFrame;
	frameTime += secondPerFrame;
	g_SecondPerFrame = secondPerFrame;
	g_fGameTimer = accumulationTime;

	if (frameTime >= 1.0f)
	{
		FPS = frameCount;
		frameCount = 0;
		frameTime -= 1.0f;

		_stprintf_s(csBuffer, _T("\nTimer:[%10.4f], FPS:[%d]"),
			accumulationTime, FPS);
		//OutputDebugString(csBuffer);
	}

	frameCount++;

	beforeTick = currentTick;
	return false;
}

bool PTimer::Render()
{

	return true;
}

bool PTimer::Release()
{

	return false;
}

PTimer::PTimer()
{
	secondPerFrame = 0.0f;
	accumulationTime = 0.0f;
	FPS = 0;
	frameTime = 0.0f;
	frameCount = 0;
}


PTimer::~PTimer()
{
}
