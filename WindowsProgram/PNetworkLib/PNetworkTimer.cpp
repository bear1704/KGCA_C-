#include "PNetworkTimer.h"
#include <cstdio>

bool g_custom_tick = false;

VOID CALLBACK TimerCallBack(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	g_custom_tick = true;
}

PNetworkTimer::PNetworkTimer()
{

}

PNetworkTimer::~PNetworkTimer()
{
	printf("\n[Network timer delete]");
	Sleep(1000);
	DeleteTimerQueueTimer(handle_100ms_timer_queue_, handle_timer_, nullptr);
	printf("[\nNetwork timer delete OK]");
}

void PNetworkTimer::Init()
{
	handle_100ms_timer_queue_ = CreateTimerQueue();
	CreateTimerQueueTimer(&handle_timer_, handle_100ms_timer_queue_, (WAITORTIMERCALLBACK)TimerCallBack,
		nullptr, 0, 100, WT_EXECUTEDEFAULT);

	printf("\n[Network timer start]");
}
