#include "PEventSelect.h"
#include "PNetwork.h"

bool PEventSelect::Init()
{
	event_array[0] = WSACreateEvent();
	int ret = WSAEventSelect(socket_, event_array[0], FD_CONNECT |
		FD_CLOSE | FD_READ | FD_WRITE);

	if (ret == SOCKET_ERROR)
	{
		E_MSG("event_select");
	}
	return true;
}

bool PEventSelect::Frame()
{
	int index = WSAWaitForMultipleEvents(1, event_array, TRUE, 0, FALSE);
	assert(index != WSA_WAIT_FAILED);
	//assert(index != WSA_WAIT_TIMEOUT);

	if (index == WSA_WAIT_TIMEOUT)
		return true;

	index -= WSA_WAIT_EVENT_0;

	WSANETWORKEVENTS networkevent;

	int ret = WSAEnumNetworkEvents(socket_, event_array[index], &networkevent); //어떤 이벤트인지 확인 , sig->non-sig

	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	assert(ret != SOCKET_ERROR);

	if (networkevent.lNetworkEvents & FD_READ)
	{
		if (networkevent.iErrorCode[FD_READ_BIT] != 0)
		{
			return false;
		}
	PPacketManager::GetInstance().RunRecvThread(&socket_); //thread에서 리시브하게 명령

	}
	if (networkevent.lNetworkEvents & FD_WRITE)
	{
		if (networkevent.iErrorCode[FD_WRITE_BIT] != 0)
		{
			return false;
		}
		//WRITE동작 
	}
	if (networkevent.lNetworkEvents & FD_CLOSE)
	{
		if (networkevent.iErrorCode[FD_CLOSE_BIT] != 0)
		{
			return false;
		}
		//PNetwork::connect_ = false;
	}

	return true;
}

PEventSelect::PEventSelect(SOCKET sock)
{
	socket_ = sock;
	
}

PEventSelect::~PEventSelect()
{
}
