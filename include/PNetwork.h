#pragma once
#include "PSelectModel.h"

class PNetwork //PClient?
{
protected:
	std::shared_ptr<PSelectModel> current_model_;
	c_string			ip_adress_;
	int					port_number_;
	HWND				hwnd_;
	SOCKET				socket_;
	static std::list<UPACKET> recv_pool_;
	static std::list<UPACKET> send_pool_;
	static bool connect_;
public:
	bool CreateSock();
	bool SendFromPacketPool();
	bool SendMsg(int type, char* msg_data, int msg_size);
	bool Connect(const char* ip_address, int port_number, HWND hwnd);
	bool set_current_model(Sptr<PSelectModel> model);
	bool ShutDown();
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	SOCKET& get_socket();

public:
	PNetwork();
	virtual ~PNetwork();





};

