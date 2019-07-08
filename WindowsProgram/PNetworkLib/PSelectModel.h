#pragma once
#include "TserverStd.h"
#include "PProtocol.h"


class PSelectModel
{
protected:
	HWND	hwnd_;
	SOCKET	socket_;
	int		recv_bytes_;
	char	recv_buffer[PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE]; //2052
public:
	virtual bool Init() { return true; }
	virtual bool Frame() { return true; }
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { return 1; }
	bool RecvPacket(); //origin:RecvData
	bool RecvMsg(SOCKET sock, char* buffer, int data_bytes);
	bool SendMsg(SOCKET sock, int packet_type, char* data, int datasize);
	bool SendMsg(UPACKET& packet);

public:
	void set_hwnd(HWND hwnd);
	void set_socket(SOCKET socket);
	
public:
	PSelectModel() = delete;
	PSelectModel(SOCKET sock);
	PSelectModel(const PSelectModel&) = delete;
	virtual ~PSelectModel();
};

