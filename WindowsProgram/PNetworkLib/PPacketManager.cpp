#include "PPacketManager.h"

PPacketManager::PPacketManager()
{
	mutex_ = CreateMutex(NULL, FALSE, NULL);
	receive_thread_ = NULL;
	param_set_.recv_packet_pool = &recv_packet_pool_;
	param_set_.send_packet_pool = &send_packet_pool_;
}


unsigned __stdcall RecvPacketThread(LPVOID param)
{
	int		recv_bytes_ = 0;
	char	recv_buffer[PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE]; //2052
	ZeroMemory(recv_buffer, sizeof(recv_buffer));
	PACKET* packet = nullptr;

	ThreadParamSet* param_set = (ThreadParamSet*)param;
	
	WaitForSingleObject(mutex_, INFINITE);

	while (1)
	{
		if (recv_bytes_ < PACKET_HEADER_SIZE)
		{
			int once_recv = recv(*(param_set->socket), &recv_buffer[recv_bytes_], PACKET_HEADER_SIZE - recv_bytes_, 0);
			if (once_recv == 0)
			{
				return false;
			}

			if (once_recv == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK) {}
				else
				{
					E_MSG("recv error");
					return false;
				}
			}
			else
			{
				recv_bytes_ += once_recv;
				if (recv_bytes_ == PACKET_HEADER_SIZE)
					packet = (PACKET*)recv_buffer; //헤더로 일단 패킷을 만들어 둔다.

				if (packet->ph.len == recv_bytes_)
				{
					(param_set->recv_packet_pool)->push_back(*packet);
					recv_bytes_ = 0;
					return true;
				}

			}
		}
		else
		{
			//packet = (UPACKET*)recv_buffer;
			int once_recv = recv(*(param_set->socket), &recv_buffer[recv_bytes_],
				packet->ph.len - recv_bytes_, 0);

			if (once_recv == 0)
				return false;
			if (once_recv == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
				}
				else
				{
					E_MSG("recv");
					return false;
				}
			}

			recv_bytes_ += once_recv;

			if (packet->ph.len == recv_bytes_)
			{
				(param_set->recv_packet_pool)->push_back(*packet);
				recv_bytes_ = 0;
				return true;
			}

		}
	}

	
	ReleaseMutex(mutex_);

	return true;
}



unsigned __stdcall ProcessThread(LPVOID param)
{
	
	while (true)
	{
		ThreadParamSet* param_set = (ThreadParamSet*)param;

		std::list<PACKET>* recv_packet_pool = param_set->recv_packet_pool;
		std::list<PACKET>* send_packet_pool = param_set->send_packet_pool;

		WaitForSingleObject(mutex_, INFINITE);
		for (PACKET& packet : *recv_packet_pool)
		{
			switch (packet.ph.type)
			{
			case PACKET_SC_SAY_HI:
				//assert(false); //패킷 감지시 바로 반응하게
				OutputDebugString(L"hi\n");
				break;

			}

		}
		recv_packet_pool->clear();
		ReleaseMutex(mutex_);
	}
	return true;
}

void PPacketManager::PushPacket(PushType type, PACKET packet)
{
	WaitForSingleObject(mutex_, INFINITE);
	{
		if (type == PushType::SEND)
			send_packet_pool_.push_back(packet);
		else
			recv_packet_pool_.push_back(packet);
	}
	ReleaseMutex(mutex_);
}

bool PPacketManager::RunRecvThread(SOCKET* socket)
{
	DWORD exitcode;
	GetExitCodeThread(receive_thread_, &exitcode);  //혹시 여기서 널에러 나나?
	if (exitcode != STILL_ACTIVE)
		CloseHandle(receive_thread_);

	param_set_.socket = socket;
	

	receive_thread_ = (HANDLE) _beginthreadex(NULL, 0, RecvPacketThread, &param_set_, 0, NULL);

	return true;
}

bool PPacketManager::RunPacketProcess(SOCKET* socket)
{
	DWORD exitcode;
	GetExitCodeThread(process_thread_, &exitcode);  
	if (exitcode == STILL_ACTIVE)
		return true;


	param_set_.socket = socket;

	process_thread_ = (HANDLE)_beginthreadex(NULL, 0, ProcessThread, &param_set_, 0, NULL);

	return false;
}

bool PPacketManager::Init()
{
	return false;
}

bool PPacketManager::Frame()
{
	return false;
}

bool PPacketManager::Render()
{
	return false;
}

bool PPacketManager::Release()
{
	CloseHandle(process_thread_);
	CloseHandle(receive_thread_);
	return false;
}

PPacketManager::~PPacketManager()
{
}
