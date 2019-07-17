#include "PSelectModel.h"
#include "PNetwork.h"

//
//bool PSelectModel::RecvMsg(SOCKET sock, char* buffer, int data_bytes)
//{
//	if (data_bytes < 0) return true;
//
//	int recv_bytes = 0;
//
//	do
//	{
//		int once_recv = recv(sock, &buffer[recv_bytes], data_bytes - recv_bytes, 0);
//		if (once_recv == 0)
//			return false;
//		if (once_recv == SOCKET_ERROR)
//			return false;
//
//		recv_bytes += once_recv;
//	} while (data_bytes > recv_bytes);
//
//	return true;
//
//}

bool PSelectModel::SendMsg(SOCKET sock, int packet_type, char* data, int datasize)
{

	PACKET packet;
	ZeroMemory(&packet, sizeof(PACKET));
	packet.ph.type = packet_type;
	packet.ph.len = PACKET_HEADER_SIZE + datasize;

	if (data != nullptr)
		memcpy(packet.msg, data, datasize);

	int send_bytes = 0;

	do 
	{
		int once_send = send(sock, (char*)& packet, packet.ph.len - send_bytes, 0);

		if (once_send == SOCKET_ERROR)
			return false;

		send_bytes += once_send;
	} while (packet.ph.len > send_bytes);
	
	return true;
}
//
//bool PSelectModel::SendMsg(PACKET& packet) //ÆÐÅ¶À» 
//{
//	int send_bytes = 0;
//	do
//	{
//		int once_send = send(socket_, (char*)& packet, packet.ph.len - send_bytes, 0);
//		if (once_send == SOCKET_ERROR)
//		{
//			if(WSAGetLastError() == WSAEWOULDBLOCK)
//			{ }
//			else
//			{
//				E_MSG("send");
//				return false;
//			}
//		}
//		else
//		{
//			if (once_send >= 0)
//			{
//				send_bytes += once_send;
//			}
//		}
//
//	} while (packet.ph.len > send_bytes);
//
//	return true;
//}

void PSelectModel::set_hwnd(HWND hwnd)
{
	hwnd_ = hwnd;
}

void PSelectModel::set_socket(SOCKET socket)
{
	socket_ = socket;
}


PSelectModel::PSelectModel()
{
}

PSelectModel::PSelectModel(SOCKET sock)
{
	socket_ = sock;
	//recv_bytes_ = 0;
}

PSelectModel::~PSelectModel()
{
}
