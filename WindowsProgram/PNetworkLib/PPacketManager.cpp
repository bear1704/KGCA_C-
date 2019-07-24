#include "PPacketManager.h"
#include "PUserManager.h"


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
	OutputDebugString(L"\n ����(���ú� ���̶�¶�)");
	int		recv_bytes_ = 0;
	char	recv_buffer[PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE]; //2052
	ZeroMemory(recv_buffer, sizeof(recv_buffer));
	PACKET* packet = nullptr;
	

	ThreadParamSet* param_set = (ThreadParamSet*)param; //����, recv_pool, send_pool�� ���ִ� �Ķ���� ��Ʈ

	int& notify_request_count_from_paramater = *(param_set->recv_notify_request_count); //�򰥸��ϱ� �ƿ� ������ �޾ƿ´�.
	SOCKET& socket_ref_from_parameter = *(param_set->socket);

	while (g_window_terminated == false)
	{
		

		std::unique_lock<std::mutex> recv_lock(PPacketManager::recv_mutex_);  //Lock(mutex)�� ��´�. recv_notify_req...�� �����Ǵ°� ���� ����
		PPacketManager::recv_event_.wait(recv_lock, [&notify_request_count_from_paramater]()
		{return notify_request_count_from_paramater > 0; });
		notify_request_count_from_paramater -= 1;

		if (g_window_terminated == true)
			break;

		//lock�� return()�� ������ ��ȣ�ϱ� ���� 
		//wait�տ��� ���, notify�� �ݵǸ� �μ��� ������ üũ�Ͽ�, false�� recv_lock�� Ǯ��(�����尡 ����� �� �ֵ���)
		//Thread�� block�Ѵ�. ���� true�� recv_lock�� �ɰ�(������ �ϳ��� ����) ����� �����Ѵ�(�ڵ� ����)
		//�ǹ� : 1ȸ���� ���Ҵ�. 2ȸ������ wait�� ������ notify�� �� ���������� ��ٸ� ���ΰ�, ���ǿ� �±⸸ �ϸ� ������ ���ΰ�?
		 
		SOCKET& socket_ref_from_parameter = *(param_set->socket); //���� ��ü�� �ٲ�����Ƿ� ������ ���� ���� ������ü�� ����ų��.

		if (recv_bytes_ < PACKET_HEADER_SIZE)
		{
			OutputDebugString(L"\n recv �ֻ��"+ __LINE__);
			std::wstring fwc = std::to_wstring(recv_bytes_);
			OutputDebugString(L"\n �ֻ�ܿ����� recv_bytes :  ");
			OutputDebugString(fwc.c_str());
			OutputDebugString(L"\n-----------------------");
			int once_recv = recv(socket_ref_from_parameter, &recv_buffer[recv_bytes_], PACKET_HEADER_SIZE - recv_bytes_, 0);
			
			std::wstring fw = std::to_wstring(once_recv);
			OutputDebugString(L"\n first once_recv :  ");
			OutputDebugString(fw.c_str());
			OutputDebugString(L"\n-----------------------");

			if (once_recv == 0)
			{
				OutputDebugString(L"\n === 0");
				//return true;
			}

			if (once_recv == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{	//���� ������ ����, ������ ����
	
					OutputDebugString(L"\n WSAEWOULDBLOCK ");
					continue;
				}
				else
				{
					OutputDebugString(L"\n recv error �߻�!!");
					int err = WSAGetLastError();
					E_MSG("recv error �߻�!!");
					return false;
				}
			}
			else
			{
				recv_bytes_ += once_recv;
				if (recv_bytes_ == PACKET_HEADER_SIZE)
					packet = (PACKET*)recv_buffer; //����� �ϴ� ��Ŷ�� ����� �д�.
				else
				{
					OutputDebugString(L"\n continue");
					notify_request_count_from_paramater += 1;
					continue;
				}

				std::wstring wstr = std::to_wstring(recv_bytes_);
				std::wstring wstr1 = std::to_wstring(packet->ph.len);
				std::wstring wstr2 = std::to_wstring(packet->ph.type);
				std::wstring wstr3 = std::to_wstring(once_recv);
				OutputDebugString(L"\n else->����1 : ph_len : ");
				OutputDebugString(wstr1.c_str());
				OutputDebugString(L"\nrecvbytes : ");
				OutputDebugString(wstr.c_str());
				OutputDebugString(L"\ntype : ");
				OutputDebugString(wstr2.c_str());
				OutputDebugString(L"\nonce_recv : ");
				OutputDebugString(wstr3.c_str());
				OutputDebugString(L"\n-----------------------");

				if (packet->ph.len == recv_bytes_)
				{
					if (packet->ph.type == PACKET_ANYDIR_SAY_HI)
					{
						OutputDebugString(L"\n === HIPACKET");
						memcpy(packet->msg, &socket_ref_from_parameter, sizeof(SOCKET));
						packet->ph.len = PACKET_HEADER_SIZE + sizeof(SOCKET);
					}

					OutputDebugString(L"\n ���۵� ��Ŷ");
					PPacketManager::GetInstance().PushPacket(PushType::RECV, *packet);
					PPacketManager::GetInstance().NotifyProcessEvent();
					recv_bytes_ = 0;
				
					//return true; //�����ϸ� �� �Ǵ°�, �� recv�ؼ� 0�� �� �� ����..
				}

				
				wstr = std::to_wstring(recv_bytes_);
				wstr1 = std::to_wstring(packet->ph.len);
				wstr2 = std::to_wstring(packet->ph.type);
				wstr3 = std::to_wstring(once_recv);
				OutputDebugString(L"\n else->����� �޾Ҿ�� : ph_len : ");
				OutputDebugString(wstr1.c_str());
				OutputDebugString(L"\nrecvbytes : ");
				OutputDebugString(wstr.c_str());
				OutputDebugString(L"\ntype : ");
				OutputDebugString(wstr2.c_str());
				OutputDebugString(L"\nonce_recv : ");
				OutputDebugString(wstr3.c_str());
				OutputDebugString(L"\n-----------------------");
				//notify_request_count_from_paramater += 1;
			}
		}
		else
		{

			//packet = (UPACKET*)recv_buffer;
			int once_recv = recv(socket_ref_from_parameter, &recv_buffer[recv_bytes_],
				packet->ph.len - recv_bytes_, 0);

			if (once_recv == 0)
			{
				OutputDebugString(L"\n === 0");
				//return true; //��������
			}
			if (once_recv == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					OutputDebugString(L"\n WSAEWOULDBLOCK");
					continue;
				}
				else
				{
					OutputDebugString(L"\n ERR");
					E_MSG("recv");
					return false;
				}
			}

			recv_bytes_ += once_recv;

			std::wstring wstr = std::to_wstring(recv_bytes_);
			std::wstring wstr1 = std::to_wstring(packet->ph.len);
			std::wstring wstr2 = std::to_wstring(packet->ph.type);
			std::wstring wstr3 = std::to_wstring(once_recv);
			OutputDebugString(L"\n else->����2 : ph_len : ");
			OutputDebugString(wstr1.c_str());
			OutputDebugString(L"\nrecvbytes : ");
			OutputDebugString(wstr.c_str());
			OutputDebugString(L"\ntype : ");
			OutputDebugString(wstr2.c_str());
			OutputDebugString(L"\nonce_recv : ");
			OutputDebugString(wstr3.c_str());
			OutputDebugString(L"\n-----------------------");


			if (packet->ph.len == recv_bytes_)
			{
				if (packet->ph.type == PACKET_ANYDIR_SAY_HI)
				{
					OutputDebugString(L"\n === HIPACKET");
					memcpy(packet->msg, &socket_ref_from_parameter, sizeof(SOCKET));
					packet->ph.len = PACKET_HEADER_SIZE + sizeof(SOCKET);
				}
				
				OutputDebugString(L"\n ���۵� ��Ŷ");
				PPacketManager::GetInstance().PushPacket(PushType::RECV, *packet);
				recv_bytes_ = 0;
				PPacketManager::GetInstance().NotifyProcessEvent();
				//return true;// �����ϸ� �� �Ǵ°�, �� recv�ؼ� 0�� �� �� ���� �޾ƾ� ��
			}
			else
			{
				OutputDebugString(L"\n continue2");
				notify_request_count_from_paramater += 1;
				continue;
			}

		}
		OutputDebugString(L"\n  ����Ƕ�1");
	}
	OutputDebugString(L"\n  ����Ƕ�2");

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

	while (g_window_terminated == false)
	{
		//PPacketManager::is_both_pool_empty_ = (recv_packet_pool.size() == 0 && send_packet_pool.size() == 0) ? true : false; //Ǯ ����� ����!
		std::unique_lock<std::mutex> process_lock(PPacketManager::process_mutex_);
		PPacketManager::process_event_.wait(process_lock, [&recv_packet_pool, &send_packet_pool]()
			{return !(((recv_packet_pool.size() == 0) && (send_packet_pool.size() == 0)) ? true : false);  });

		
		if (g_window_terminated == true)
			break;

		SOCKET& socket_ref_from_parameter = *(param_set->socket);

			for (PACKET& packet : recv_packet_pool)
			{
				if (g_operate_mode == OperateMode::CLIENT) // Ŭ���̾�Ʈ
				{
					switch (packet.ph.type)
					{
						case PACKET_SC_ID_PROVIDE:
						{
							//MessageBox(g_hWnd, L"provide_pp", L"PROVIDE_pp", MB_OK);
							PInstructionManager::GetInstance().AddInstruction(packet);	
							break;
						}
						case PACKET_SC_TEST_HPDECREASE:
						{
							PInstructionManager::GetInstance().AddInstruction(packet);
							break;
						}
						case PACKET_SC_SPAWN_CHARACTER:
						{
							//MessageBox(g_hWnd, L"spawn_pp", L"SPAWN_pp", MB_OK);
							PInstructionManager::GetInstance().AddInstruction(packet);
							break;
						}

					}
				}
				else //����
				{
					switch (packet.ph.type)
					{
						case PACKET_ANYDIR_SAY_HI:
						{
							PInstructionManager::GetInstance().AddInstruction(packet);
							break;
						}
						case PACKET_CS_LOGIN_SEND_USERNAME:
						{
							PInstructionManager::GetInstance().AddInstruction(packet);
							break;
						}

					}
				}

			}
			recv_packet_pool.clear(); //clear���� �ʰ�, �׶��׶� ������� ���ؽ�Ʈ ����Ī �� ó�� ���� ��Ŷ clear�ϴ� ���簡 �߻����� �ʴ´�.

			if (g_operate_mode == OperateMode::CLIENT)
			{

				for (PACKET& packet : send_packet_pool)
				{
					PPacketManager::GetInstance().SendPacketFromPacketPool(socket_ref_from_parameter, packet);
				}
				send_packet_pool.clear();
			}
			else if(g_operate_mode == OperateMode::SERVER)
			{
				for (PACKET& packet : send_packet_pool)
				{
					PUser* user = PUserManager::GetInstance().FindUserById(packet.ph.id);

					if(user != nullptr)
						PPacketManager::GetInstance().SendPacketFromPacketPool(user->get_socket() , packet);
					else
					{
						SOCKET sock;
						memcpy(&sock, packet.msg, sizeof(SOCKET));
						PPacketManager::GetInstance().SendPacketFromPacketPool(sock, packet);
					}
				}
				send_packet_pool.clear();
			}
			
	}


	return true;
}


PPacketManager::PPacketManager()
{

}



void PPacketManager::PushPacket(PushType type, PACKET packet)
{

	std::unique_lock<std::recursive_mutex > lock(push_mutex_);
	{
		if (type == PushType::SEND)
			send_packet_pool_.push_back(packet);
		else
			recv_packet_pool_.push_back(packet);
	}
	PPacketManager::GetInstance().NotifyProcessEvent();
	lock.unlock();

}


void PPacketManager::PushPacket(PUser* user, int protocol, char* data, int data_size, PushType type, bool ischar)
{
	std::unique_lock<std::recursive_mutex > lock(push_mutex_);
	{
	PACKET packet;
	ZeroMemory(&packet, sizeof(PACKET));
	packet.ph.type = protocol;
	packet.ph.id = user->get_id();
	packet.ph.len = data_size + PACKET_HEADER_SIZE;

	if (data != nullptr)
	{
		if(ischar) //char �迭�� char*�� �����ͼ� �ּұ���ü�ϰ��
			memcpy(packet.msg, data, data_size);
		else //Ư�� ���� char*�� �����ͼ� ���� char*ȭ�� ���
			memcpy(packet.msg, &data, data_size);
	}
		
	


	if (type == PushType::SEND)
		send_packet_pool_.push_back(packet);
	else
		recv_packet_pool_.push_back(packet);
	
	PPacketManager::GetInstance().NotifyProcessEvent();
	}
	lock.unlock();

}

bool PPacketManager::NotifyReceiveEvent()
{

	recv_notify_request_count_ += 1;  //�������� ��� �ϳ�
	PPacketManager::recv_event_.notify_all();

	return true;
}

bool PPacketManager::NotifyProcessEvent()
{

	PPacketManager::is_both_pool_empty_ = false;
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
	std::lock_guard<std::mutex> lk(mutex_);
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
}

void PPacketManager::ChangeSocketToParam(SOCKET* socket)
{
	param_set_.socket = socket;
}




PPacketManager::~PPacketManager()
{
}
