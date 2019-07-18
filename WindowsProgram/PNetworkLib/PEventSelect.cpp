#include "PEventSelect.h"
#include "PNetwork.h"

bool PEventSelect::Init()
{
	if (operate_mode_ == OperateMode::CLIENT)
	{
		event_array_[0] = WSACreateEvent();
		int ret = WSAEventSelect(socket_, event_array_[0], FD_CONNECT |
			FD_CLOSE | FD_READ | FD_WRITE);

		if (ret == SOCKET_ERROR)
		{
			E_MSG("event_select");
		}
	}
	else if (operate_mode_ == OperateMode::SERVER)
	{
		HANDLE listen_event = WSACreateEvent();
		event_array_[0] = listen_event;
		int ret = WSAEventSelect(socket_, event_array_[0], FD_ACCEPT);

		if (ret == SOCKET_ERROR)
		{
			E_MSG("accept_error");
		}
	}
	else
		assert(false);
	
	PPacketManager::GetInstance().ThreadInit(&socket_); //쓰레드 초기화 및 생성

	return true;
}

bool PEventSelect::Frame()
{
	if (operate_mode_ == OperateMode::CLIENT)
	{
		int index = WSAWaitForMultipleEvents(1, event_array_, TRUE, 0, FALSE);
		assert(index != WSA_WAIT_FAILED);

		if (index == WSA_WAIT_TIMEOUT)
			return true;

		index -= WSA_WAIT_EVENT_0;

		WSANETWORKEVENTS networkevent;

		int ret = WSAEnumNetworkEvents(socket_, event_array_[index], &networkevent); //어떤 이벤트인지 확인 , Signal->non-signal

		if (ret == SOCKET_ERROR)
		{
			return false;
		}
		assert(ret != SOCKET_ERROR);

		if (networkevent.lNetworkEvents & FD_READ) //Read이벤트 (connect, recv인데 여기선 recv만)
		{
			if (networkevent.iErrorCode[FD_READ_BIT] != 0)
			{
				return false;
			}
			PPacketManager::GetInstance().NotifyReceiveEvent(); //thread에서 리시브하게 명령
		}

		if (networkevent.lNetworkEvents & FD_WRITE) //Write이벤트 (미구현)
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
	
	}
	else if(operate_mode_ == OperateMode::SERVER)
	{
		std::vector<PUser*>& user_list_ref = PUserManager::GetInstance().user_list_;

		int index = WSAWaitForMultipleEvents(
			user_list_ref.size() + 1,
			event_array_,
			FALSE,
			1000,
			FALSE);

		if (index == WSA_WAIT_FAILED) return false;
		if (index == WSA_WAIT_TIMEOUT) return false;
		index -= WSA_WAIT_EVENT_0;
				
		if (index == 0) //어떤 이벤트였는지 판별 , 이 부분은 Accept시에만 적용
		{
			WSANETWORKEVENTS networkevent;
				
			int ret = WSAEnumNetworkEvents(socket_, event_array_[index], &networkevent);
			if (ret == SOCKET_ERROR) return false;

			if (networkevent.lNetworkEvents & FD_ACCEPT)
			{
				if (networkevent.iErrorCode[FD_ACCEPT_BIT] != 0) { assert(false); }
				
				int addr_len = sizeof(SOCKADDR_IN);
				PUser* user = new PUser;
				SOCKET clientsock = accept(socket_, (SOCKADDR*)& user->get_client_addr(), &addr_len);

				if (clientsock == INVALID_SOCKET) { E_MSG("Server:accept"); }

				user->set_socket(clientsock);

				PUserManager::GetInstance().AddUser(user);

				event_array_[user_list_ref.size()] = user->get_event();
				WSAEventSelect(user->get_socket(), user->get_event(), FD_READ | FD_WRITE | FD_CLOSE);
			}		

		}
		
		for (int i = index - 1; i < user_list_ref.size(); i++)
		{		
			INT signal = WSAWaitForMultipleEvents(
				1,
				&user_list_ref[i]->get_event(),
				TRUE,
				0, 
				FALSE);
			
			if (signal == WSA_WAIT_FAILED || signal == WSA_WAIT_TIMEOUT) { continue; }

			WSANETWORKEVENTS networkevent;
			int ret = WSAEnumNetworkEvents(
				user_list_ref[i]->get_socket(),
				user_list_ref[i]->get_event(),
				&networkevent);

			if (ret == SOCKET_ERROR) continue;

			if (networkevent.lNetworkEvents & FD_READ)
			{
				if (networkevent.iErrorCode[FD_READ_BIT] != 0) { continue; }
				PPacketManager::GetInstance().NotifyReceiveEvent();
			}
			if (networkevent.lNetworkEvents & FD_WRITE)
			{
				if (networkevent.iErrorCode[FD_WRITE_BIT] != 0) { continue; }
			
			}
			if (networkevent.lNetworkEvents & FD_CLOSE)
			{
				if (networkevent.iErrorCode[FD_CLOSE_BIT] == 10053)
					PUserManager::GetInstance().DeleteUser(user_list_ref[i]);
				if (networkevent.iErrorCode[FD_CLOSE_BIT] != 0) 
				{ continue; }
			
			}

		}

	}
	else { assert(false); }
	return true;
}

PEventSelect::PEventSelect(SOCKET sock, OperateMode mode)
{
	socket_ = sock;
	operate_mode_ = mode;
}

PEventSelect::~PEventSelect()
{
}
