#pragma once
#include <Windows.h>

template <typename T>
class PNetworkSingleton
{
public:
	static T& GetInstance()
	{
		static T singleton;
		return singleton;
	}
};

class PNetworkTimer : public PNetworkSingleton<PNetworkTimer>
{

private:
	friend class PNetworkSingleton<PNetworkTimer>;
	PNetworkTimer();
public:
	~PNetworkTimer();
private:
	HANDLE handle_timer_;
	HANDLE handle_100ms_timer_queue_;
public:
	void Init();


};

extern bool g_custom_tick;