#pragma once
#include "TserverStd.h"
#include "PProtocol.h"


class PSelectModel
{
protected:
	HWND	hwnd_;
	SOCKET	socket_;
public:
	virtual bool Init() { return true; }
	virtual bool Frame() { return true; }
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { return 1; }
	//bool RecvMsg(SOCKET sock, char* buffer, int data_bytes);
	bool SendMsg(SOCKET sock, int packet_type, char* data, int datasize);
	//bool SendMsg(PACKET& packet);

public:
	void set_hwnd(HWND hwnd);
	void set_socket(SOCKET socket);
	
public:
	PSelectModel();
	PSelectModel(SOCKET sock);
	PSelectModel(const PSelectModel&) = delete;
	virtual ~PSelectModel();
};

