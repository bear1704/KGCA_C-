#include "PEventSelect.h"
#include "PNetwork.h"

OperateMode g_operate_mode;


bool PEventSelect::Init()
{
	if (g_operate_mode == OperateMode::CLIENT)
	{

		event_array_[0] = WSACreateEvent();
		int ret = WSAEventSelect(socket_, event_array_[0], FD_CONNECT |
			FD_CLOSE | FD_READ | FD_WRITE);

		if (ret == SOCKET_ERROR)
		{
			E_MSG("event_select");
		}

		PUserManager::GetInstance().oneself_user_.set_event(event_array_[0]);
		PPacketManager::GetInstance().ThreadInit(&socket_); //쓰레드 초기화 및 생성

		PACKET pack;
		ZeroMemory(&pack, sizeof(PACKET));
		pack.ph.id = 0;
		pack.ph.type = PACKET_ANYDIR_SAY_HI;
		pack.ph.len = PACKET_HEADER_SIZE;
		
		PPacketManager::GetInstance().PushPacket(PushType::SEND, pack);

	}
	else if (g_operate_mode == OperateMode::SERVER)
	{
		HANDLE listen_event = WSACreateEvent();
		event_array_[0] = listen_event;
		int ret = WSAEventSelect(socket_, event_array_[0], FD_ACCEPT);

		if (ret == SOCKET_ERROR)
		{
			E_MSG("accept_error");
		}
	PPacketManager::GetInstance().ThreadInit(&socket_); //쓰레드 초기화 및 생성
	}
	else
		assert(false);
	

	return true;
}

bool PEventSelect::Frame()
{
	if (g_operate_mode == OperateMode::CLIENT)
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
	else if(g_operate_mode == OperateMode::SERVER)
	{
		std::vector<PUser*>& user_list_ref = PUserManager::GetInstance().user_list_;

		int index = WSAWaitForMultipleEvents(
			user_list_ref.size() + 1,
			event_array_,
			FALSE,
			0,
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
				SOCKET clientsock = accept(socket_, (SOCKADDR*)user->get_client_addr_by_ptr(), &addr_len);
				

				if (clientsock == INVALID_SOCKET) { E_MSG("Server:accept"); }

				user->set_socket(clientsock);

				printf("\n[AddUserFirstTime작업 시작]");
				PUserManager::GetInstance().AddUserFirstTime(user);
				printf("\n[AddUserFirstTime작업 끝]");
				event_array_[user_list_ref.size()] = *(user->get_event_by_ptr());
				WSAEventSelect(*(user->get_socket_by_ptr()), *(user->get_event_by_ptr()), FD_READ | FD_WRITE | FD_CLOSE);


				//PPacketManager::GetInstance().PushPacket(user, PACKET_ANYDIR_SAY_HI, nullptr, NULL, PushType::SEND, false);
			}		

		}
		
		for (int i = index - 1; i < user_list_ref.size(); i++)  //원래 get_event()를 참조로 받던 곳인데, 주의) 문제 생길 수 있음!
		{		
			HANDLE* user_event = user_list_ref[i]->get_event_by_ptr();

			INT signal = WSAWaitForMultipleEvents(
				1,
				user_event,
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
				//소켓지정
				PPacketManager::GetInstance().ChangeSocketToParam(user_list_ref[i]->get_socket_by_ptr());
				PPacketManager::GetInstance().NotifyReceiveEvent();
			}
			if (networkevent.lNetworkEvents & FD_WRITE)
			{
				if (networkevent.iErrorCode[FD_WRITE_BIT] != 0) { continue; }
			
			}
			if (networkevent.lNetworkEvents & FD_CLOSE) //몬가 클로즈 이벤트를 하나씩 놓치는 버그가 있음. 주의요망
			{
				if (networkevent.iErrorCode[FD_CLOSE_BIT] == 10053)
					PUserManager::GetInstance().DeleteUser(user_list_ref[i]);
				if (networkevent.iErrorCode[FD_CLOSE_BIT] != 0) 
				{ continue; }
			
				PUserManager::GetInstance().DeleteUser(user_list_ref[i]);
			}

		}

	}
	else { assert(false); }
	return true;
}

PEventSelect::PEventSelect(SOCKET sock, OperateMode mode)
{
	socket_ = sock;
	g_operate_mode = mode;
}

PEventSelect::~PEventSelect()
{
}
