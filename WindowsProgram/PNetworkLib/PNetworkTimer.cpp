#include "PNetworkTimer.h"
#include <cstdio>

bool g_custom_tick = false;
bool g_skill_time = false;

HANDLE g_handle_200ms_timer_queue_;
HANDLE g_handle_timer_;

HANDLE g_handle_20s_timer_queue_;
HANDLE g_handle_20s_timer_;


VOID CALLBACK TimerCallBack(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	g_custom_tick = true;

	//DeleteTimerQueueTimer(g_handle_200ms_timer_queue_, g_handle_timer_, nullptr);
}
VOID CALLBACK SkillTimerCallBack(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	g_skill_time = true;

	//DeleteTimerQueueTimer(g_handle_200ms_timer_queue_, g_handle_timer_, nullptr);
}

PNetworkTimer::PNetworkTimer()
{

}

PNetworkTimer::~PNetworkTimer()
{
	printf("\n[Network timer delete]");
	Sleep(1000);
	//DeleteTimerQueueTimer(handle_100ms_timer_queue_, handle_timer_, nullptr);
	printf("[\nNetwork timer delete OK]");
}

void PNetworkTimer::Init()
{
	g_handle_200ms_timer_queue_ = CreateTimerQueue();
	CreateTimerQueueTimer(&g_handle_timer_, g_handle_200ms_timer_queue_, (WAITORTIMERCALLBACK)TimerCallBack,
		nullptr, 0, 200, WT_EXECUTEDEFAULT);

	CreateTimerQueueTimer(&g_handle_20s_timer_, g_handle_20s_timer_queue_, (WAITORTIMERCALLBACK)SkillTimerCallBack,
		nullptr, 10000, 10000, WT_EXECUTEDEFAULT);
	printf("\n[Network timer start]");
}
