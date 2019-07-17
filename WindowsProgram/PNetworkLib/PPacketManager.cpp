#include "PPacketManager.h"

bool PPacketManager::is_both_pool_empty_ = false;
std::mutex PPacketManager::mutex_;
std::mutex PPacketManager::process_mutex_;
std::mutex PPacketManager::recv_mutex_;
std::condition_variable PPacketManager::recv_event_;
std::condition_variable PPacketManager::send_event_;
std::condition_variable PPacketManager::process_event_;



unsigned __stdcall RecvPacketThread(LPVOID param)
{
	int		recv_bytes_ = 0;
	char	recv_buffer[PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE]; //2052
	ZeroMemory(recv_buffer, sizeof(recv_buffer));
	PACKET* packet = nullptr;

	ThreadParamSet* param_set = (ThreadParamSet*)param;

	
	while (1)
	{
		
		std::unique_lock<std::mutex> recv_lock(PPacketManager::recv_mutex_);  //Lock(mutex)을 얻는다.
		PPacketManager::recv_event_.wait(recv_lock, []()
		//	{return false; });
		//MessageBox(g_hWnd, L"falseeeeee", L"hi", MB_OK);
		{return PPacketManager::GetInstance().recv_notify_request_count_ > 0; });
		*param_set->recv_notify_request_count -= 1;
		recv_lock.unlock();
		//lock은 return()의 조건을 보호하기 위함 
		//wait앞에서 대기, notify가 콜되면 인수의 조건을 체크하여, false면 recv_lock을 풀고(쓰레드가 대기할 수 있도록)
		//Thread를 block한다. 만약 true면 recv_lock을 걸고(쓰레드 하나만 접근) 블록을 해제한다(코드 진행)
		//의문 : 1회차는 돌았다. 2회차에서 wait을 만나면 notify가 또 터질때까지 기다릴 것인가, 조건에 맞기만 하면 진행할 것인가?
		 
		if (recv_bytes_ < PACKET_HEADER_SIZE)
		{
			int once_recv = recv(*(param_set->socket), &recv_buffer[recv_bytes_], PACKET_HEADER_SIZE - recv_bytes_, 0);
			
			if (once_recv == 0)
			{
				//return true;
			}

			if (once_recv == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{	//받을 데이터 없음, 쓰레드 슬립
	
					continue;
				}
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
					PPacketManager::GetInstance().NotifyProcessEvent();
					recv_bytes_ = 0;
					//return true; //리턴하면 안 되는게, 또 recv해서 0이 될 때 까지..
				}

			}
		}
		else
		{

			//packet = (UPACKET*)recv_buffer;
			int once_recv = recv(*(param_set->socket), &recv_buffer[recv_bytes_],
				packet->ph.len - recv_bytes_, 0);

			if (once_recv == 0)
			{
				//return true; //정상종료
			}
			if (once_recv == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{

					continue;
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
				PPacketManager::GetInstance().NotifyProcessEvent();
				//return true;// 리턴하면 안 되는게, 또 recv해서 0이 될 때 까지 받아야 함
			}

		}
	}


	//return true;
}



unsigned __stdcall ProcessThread(LPVOID param)
{

	ThreadParamSet* param_set = (ThreadParamSet*)param;

	std::list<PACKET>* recv_packet_pool = param_set->recv_packet_pool;
	std::list<PACKET>* send_packet_pool = param_set->send_packet_pool;

	/*if (recv_packet_pool->size() == 0 && send_packet_pool->size() == 0)
		return false;*/

	while (true)
	{
		PPacketManager::is_both_pool_empty_ = (recv_packet_pool->size() == 0 && send_packet_pool->size() == 0) ? true : false; //풀 방법이 없음!
		std::unique_lock<std::mutex> process_lock(PPacketManager::process_mutex_);
		PPacketManager::process_event_.wait(process_lock, []() {return !PPacketManager::is_both_pool_empty_; });
		



			OutputDebugString(L"\nProcess접근");
			for (PACKET& packet : *recv_packet_pool)
			{
				switch (packet.ph.type)
				{
				case PACKET_SC_SAY_HI:
					//assert(false); //패킷 감지시 바로 반응하게
					OutputDebugString(L"hi전송됨\n");
					MessageBox(g_hWnd, L"hi전송됨", L"hi", MB_OK);
					break;
				}

			}


			recv_packet_pool->clear(); //clear하지 않고, 그때그때 지워줘야 컨텍스트 스위칭 중 처리 안한 패킷 clear하는 참사가 발생하지 않는다.


			for (PACKET& packet : *send_packet_pool)
			{
				switch (packet.ph.type)
				{
				case PACKET_SC_SAY_HI:
					break;

				}

			}
			send_packet_pool->clear();
	}


	return true;
}


PPacketManager::PPacketManager()
{

}



void PPacketManager::PushPacket(PushType type, PACKET packet)
{
	//WaitForSingleObject(mutex_, INFINITE);
	std::unique_lock<std::mutex> lock(mutex_);
	{
		if (type == PushType::SEND)
			send_packet_pool_.push_back(packet);
		else
			recv_packet_pool_.push_back(packet);
	}
	lock.unlock();
	//ReleaseMutex(mutex_);
}

bool PPacketManager::NotifyReceiveEvent()
{

	{
		std::lock_guard<std::mutex> lock_guard(PPacketManager::recv_mutex_);
		recv_notify_request_count_ += 1;
	}
	PPacketManager::recv_event_.notify_all();

	return true;
}

bool PPacketManager::NotifyProcessEvent()
{

	{
		std::lock_guard<std::mutex> lock_guard(PPacketManager::process_mutex_);
		PPacketManager::is_both_pool_empty_ = false;
	}
	PPacketManager::process_event_.notify_all();
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

void PPacketManager::ThreadInit(SOCKET* socket)
{
	recv_notify_request_count_ = 0;
	send_notify_request_count_ = 0;
	param_set_.recv_packet_pool = &recv_packet_pool_;
	param_set_.send_packet_pool = &send_packet_pool_;
	param_set_.socket = socket;
	param_set_.recv_notify_request_count = &recv_notify_request_count_;
	param_set_.send_notify_request_count = &send_notify_request_count_;
	unsigned int a;
	unsigned int b;

	receive_thread_ = (HANDLE)_beginthreadex(NULL, 0, RecvPacketThread, &param_set_, 0, &a);
	process_thread_ = (HANDLE)_beginthreadex(NULL, 0, ProcessThread, &param_set_, 0, &b);

}


PPacketManager::~PPacketManager()
{
}
