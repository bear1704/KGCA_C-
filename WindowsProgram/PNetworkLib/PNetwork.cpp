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

bool PNetwork::BindListen()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	listen_sock_ = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(listen_sock_, (SOCKADDR*)& sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("Server::bind");
		return false;
	}
	printf("\n bind complete");

	ret = listen(listen_sock_, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		E_MSG("SERVER::listen");
		return false;
	}
	printf("\n listen complete");
	unsigned long blocking_mode = 1;
	ioctlsocket(listen_sock_, FIONBIO, &blocking_mode);


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

	if (operate_mode_ == OperateMode::CLIENT)
	{

		if (connect_ == false)
		{
			//ÀçÁ¢¼Ó
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
	}
	else
	{
		current_model_->Frame();
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

SOCKET& PNetwork::get_listen_sock()
{
	return listen_sock_;
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

