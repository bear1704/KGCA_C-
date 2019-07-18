#include "PPacketManager.h"

bool PPacketManager::is_both_pool_empty_ = false;
std::mutex PPacketManager::mutex_;
std::mutex PPacketManager::process_mutex_;
std::mutex PPacketManager::recv_mutex_;
std::condition_variable PPacketManager::recv_event_;
std::condition_variable PPacketManager::process_event_;


bool PPacketManager::SendPacketFromPacketPool(SOCKET socket, PACKET packet)
{
	int send_bytes = 0;
	do
	{
		int once_send = send(socket, (char*)& packet, packet.ph.len - send_bytes, 0);
		if (once_send == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
			}
			else
			{
				E_MSG("send");
				return false;
			}
		}
		else
		{
			if (once_send >= 0)
			{
				send_bytes += once_send;
			}
		}

	} while (packet.ph.len > send_bytes);


	return true;
}


unsigned __stdcall RecvPacketThread(LPVOID param) //��Ŷ�� �޴� recv�� �����ϴ� ������
{
	int		recv_bytes_ = 0;
	char	recv_buffer[PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE]; //2052
	ZeroMemory(recv_buffer, sizeof(recv_buffer));
	PACKET* packet = nullptr;

	ThreadParamSet* param_set = (ThreadParamSet*)param; //����, recv_pool, send_pool�� ���ִ� �Ķ���� ��Ʈ

	int& notify_request_count_from_paramater = *(param_set->recv_notify_request_count); //�򰥸��ϱ� �ƿ� ������ �޾ƿ´�.
	SOCKET& socket_ref_from_parameter = *(param_set->socket);

	while (1)
	{
		

		std::unique_lock<std::mutex> recv_lock(PPacketManager::recv_mutex_);  //Lock(mutex)�� ��´�. recv_notify_req...�� �����Ǵ°� ���� ����
		PPacketManager::recv_event_.wait(recv_lock, [&notify_request_count_from_paramater]()
		{return notify_request_count_from_paramater > 0; });
		notify_request_count_from_paramater -= 1;

		//lock�� return()�� ������ ��ȣ�ϱ� ���� 
		//wait�տ��� ���, notify�� �ݵǸ� �μ��� ������ üũ�Ͽ�, false�� recv_lock�� Ǯ��(�����尡 ����� �� �ֵ���)
		//Thread�� block�Ѵ�. ���� true�� recv_lock�� �ɰ�(������ �ϳ��� ����) ����� �����Ѵ�(�ڵ� ����)
		//�ǹ� : 1ȸ���� ���Ҵ�. 2ȸ������ wait�� ������ notify�� �� ���������� ��ٸ� ���ΰ�, ���ǿ� �±⸸ �ϸ� ������ ���ΰ�?
		 
		if (recv_bytes_ < PACKET_HEADER_SIZE)
		{
			int once_recv = recv(socket_ref_from_parameter, &recv_buffer[recv_bytes_], PACKET_HEADER_SIZE - recv_bytes_, 0);
			
			if (once_recv == 0)
			{
				//return true;
			}

			if (once_recv == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{	//���� ������ ����, ������ ����
	
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
					packet = (PACKET*)recv_buffer; //����� �ϴ� ��Ŷ�� ����� �д�.

				if (packet->ph.len == recv_bytes_)
				{
					PPacketManager::GetInstance().PushPacket(PushType::RECV, *packet);
					PPacketManager::GetInstance().NotifyProcessEvent();
					recv_bytes_ = 0;
					//return true; //�����ϸ� �� �Ǵ°�, �� recv�ؼ� 0�� �� �� ����..
				}

			}
		}
		else
		{

			//packet = (UPACKET*)recv_buffer;
			int once_recv = recv(socket_ref_from_parameter, &recv_buffer[recv_bytes_],
				packet->ph.len - recv_bytes_, 0);

			if (once_recv == 0)
			{
				//return true; //��������
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
				PPacketManager::GetInstance().PushPacket(PushType::RECV, *packet);
				recv_bytes_ = 0;
				PPacketManager::GetInstance().NotifyProcessEvent();
				//return true;// �����ϸ� �� �Ǵ°�, �� recv�ؼ� 0�� �� �� ���� �޾ƾ� ��
			}

		}
	}


	//return true;
}



unsigned __stdcall ProcessThread(LPVOID param)
{

	ThreadParamSet* param_set = (ThreadParamSet*)param;

	std::list<PACKET>& recv_packet_pool = *param_set->recv_packet_pool;
	std::list<PACKET>& send_packet_pool = *param_set->send_packet_pool;

	/*if (recv_packet_pool->size() == 0 && send_packet_pool->size() == 0)
		return false;*/

	SOCKET& socket_ref_from_parameter = *(param_set->socket);

	while (true)
	{
		PPacketManager::is_both_pool_empty_ = (recv_packet_pool.size() == 0 && send_packet_pool.size() == 0) ? true : false; //Ǯ ����� ����!
		std::unique_lock<std::mutex> process_lock(PPacketManager::process_mutex_);
		PPacketManager::process_event_.wait(process_lock, []() {return !PPacketManager::is_both_pool_empty_; });
		

			OutputDebugString(L"\nProcess����");
			for (PACKET& packet : recv_packet_pool)
			{
				switch (packet.ph.type)
				{
				case PACKET_SC_SAY_HI:
					//assert(false); //��Ŷ ������ �ٷ� �����ϰ�
					OutputDebugString(L"hi���۵�\n");
					MessageBox(g_hWnd, L"hi���۵�", L"hi", MB_OK);
					break;
				}

			}
			recv_packet_pool.clear(); //clear���� �ʰ�, �׶��׶� ������� ���ؽ�Ʈ ����Ī �� ó�� ���� ��Ŷ clear�ϴ� ���簡 �߻����� �ʴ´�.


			for (PACKET& packet : send_packet_pool)
			{
				PPacketManager::GetInstance().SendPacketFromPacketPool(socket_ref_from_parameter, packet);
			}
			send_packet_pool.clear();
	}


	return true;
}


PPacketManager::PPacketManager()
{

}



void PPacketManager::PushPacket(PushType type, PACKET packet)
{

	std::unique_lock<std::mutex> lock(mutex_);
	{
		if (type == PushType::SEND)
			send_packet_pool_.push_back(packet);
		else
			recv_packet_pool_.push_back(packet);
	}
	lock.unlock();

}

bool PPacketManager::NotifyReceiveEvent()
{

	{
		std::lock_guard<std::mutex> lock_guard(PPacketManager::recv_mutex_);
		recv_notify_request_count_ += 1;  //�������� ��� �ϳ�
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
	return true;
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
	receive_thread_ = (HANDLE)_beginthreadex(NULL, 0, RecvPacketThread, &param_set_, 0, NULL);
	process_thread_ = (HANDLE)_beginthreadex(NULL, 0, ProcessThread, &param_set_, 0, NULL);

}


PPacketManager::~PPacketManager()
{
}
