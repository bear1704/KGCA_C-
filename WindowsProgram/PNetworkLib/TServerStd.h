#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include "PStd.h"
#include <condition_variable>
#include <queue>
#include <mutex>
#include <concurrent_queue.h>
#pragma comment(lib, "ws2_32.lib")


enum class OperateMode
{
	SERVER,
	CLIENT,
};

extern OperateMode g_operate_mode;

static void E_MSG(const char* pMsg)
{
	void* lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	MessageBoxA(NULL, (char*)lpMsgBuf, pMsg, MB_OK);
	LocalFree(lpMsgBuf);
	return;
}