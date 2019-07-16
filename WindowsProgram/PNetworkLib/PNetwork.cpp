#include "PNetwork.h"

bool			   PNetwork::connect_ = false;

bool PNetwork::CreateSock()
{
	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_ == INVALID_SOCKET)
		return false;

	unsigned long mode = 0;
	ioctlsocket(socket_, FIONBIO, &mode); //nblocking socket
	return true;
}

//bool PNetwork::SendFromPacketPool() //패킷풀로부터 패킷을 전송
//{
//	if (PNetwork::connect_ == false) return true;
//	
//	for (PACKET& packet : PNetwork::send_pool_)
//	{
//		if (current_model_->SendMsg(packet) == false)
//		{
//			ShutDown();
//			break;
//		}
//	}
//
//	PNetwork::send_pool_.clear();
//	return false;
//}

//bool PNetwork::SendMsg(int type, char* msg_data, int msg_size)
//{
//	PACKET packet;
//	ZeroMemory(&packet, sizeof(PACKET));
//	packet.ph.type = type;
//	packet.ph.len = PACKET_HEADER_SIZE + msg_size;
//	if (msg_data != nullptr)
//	{
//		memcpy(packet.msg, msg_data, msg_size);
//	}
//	send_pool_.push_back(packet);
//	return false;
//}

bool PNetwork::Connect(const char* ip_address, int port_number, HWND hwnd)
{
	ip_adress_ = ip_address;
	port_number_ = port_number;
	hwnd_ = hwnd;

	if (CreateSock() == false)
		return false;

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port_number);
	sa.sin_addr.s_addr = inet_addr(ip_address);

	int ret = connect(socket_, (SOCKADDR*)& sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("connect");
		return false;
	}
	connect_ = true;
	return true;

}

bool PNetwork::set_current_model(Sptr<PSelectModel> model)
{
	if (model == nullptr) return false;
	
	current_model_ = model;
	current_model_->set_hwnd(hwnd_);
	current_model_->Init();
	return true;
}

bool PNetwork::ShutDown()
{
	connect_ = false;
	closesocket(socket_);

	return true;
}

LRESULT PNetwork::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (current_model_ == nullptr) return 1;
	
	return current_model_->MsgProc(hwnd, msg, wParam, lParam);
}

bool PNetwork::Init()
{
	return true;
}

bool PNetwork::Frame()
{

	if (current_model_ == nullptr) return true;

	if (connect_ == false)
	{
		//재접속
		if (Connect(ip_adress_.c_str(), port_number_, hwnd_) == false)
		{
			ShutDown();
			return false;
		}

		current_model_->set_socket(socket_);
		current_model_->Init();
	}
		if (current_model_->Frame() == false)
		{
			ShutDown();
			return false;
		}
		return true;
}

bool PNetwork::Render()
{
	return true;
}

bool PNetwork::Release()
{
	ShutDown();
	return true;
}

SOCKET& PNetwork::get_socket()
{
	return socket_;
}

Sptr<PSelectModel>& PNetwork::get_current_model()
{
	return current_model_;
}

bool PNetwork::is_connect()
{
	return connect_;
}

void PNetwork::set_connect(bool connect)
{
	connect_ = connect;
}

PNetwork::PNetwork()
{
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
	current_model_ = nullptr;
}

PNetwork::~PNetwork()
{
	WSACleanup();
}

int main()
{
	return 0;
}