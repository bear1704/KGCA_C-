#include "PSelectModel.h"
#include "PNetwork.h"
//bool PSelectModel::RecvPacket()
//{
//	PACKET* packet = nullptr;
//	while (1)
//	{ 
//		if (recv_bytes_ < PACKET_HEADER_SIZE)
//		{
//			int once_recv = recv(socket_, &recv_buffer[recv_bytes_], PACKET_HEADER_SIZE - recv_bytes_, 0);
//			if (once_recv == 0)
//			{
//				return false;
//			}
//
//			if (once_recv == SOCKET_ERROR)
//			{
//				if (WSAGetLastError() == WSAEWOULDBLOCK) {}
//				else
//				{
//					E_MSG("recv error");
//					return false;
//				}
//			}
//			else
//			{
//				recv_bytes_ += once_recv;
//				if(recv_bytes_ == PACKET_HEADER_SIZE)
//					packet = (PACKET*)recv_buffer; //헤더로 일단 패킷을 만들어 둔다.
//
//				if (packet->ph.len == recv_bytes_)
//				{
//					PNetwork::get_recv_pool().push_back(*packet);
//					recv_bytes_ = 0;
//					return true;
//				}
//
//			}
//		}
//		else
//		{
//			//packet = (UPACKET*)recv_buffer;
//			int once_recv = recv(socket_, &recv_buffer[recv_bytes_], 
//				packet->ph.len - recv_bytes_, 0);
//
//			if (once_recv == 0)
//				return false;
//			if (once_recv == SOCKET_ERROR)
//			{
//				if (WSAGetLastError() == WSAEWOULDBLOCK)
//				{ }
//				else
//				{
//					E_MSG("recv");
//					return false;
//				}
//			}
//
//			recv_bytes_ += once_recv;
//
//			if (packet->ph.len == recv_bytes_)
//			{
//				PNetwork::get_recv_pool().push_back(*packet);
//				recv_bytes_ = 0;
//				return true;
//			}
//
//		}
//	}
//	
//	return true;
//}

bool PSelectModel::RecvMsg(SOCKET sock, char* buffer, int data_bytes)
{
	if (data_bytes < 0) return true;

	int recv_bytes = 0;

	do
	{
		int once_recv = recv(sock, &buffer[recv_bytes], data_bytes - recv_bytes, 0);
		if (once_recv == 0)
			return false;
		if (once_recv == SOCKET_ERROR)
			return false;

		recv_bytes += once_recv;
	} while (data_bytes > recv_bytes);

	return true;

}

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

bool PSelectModel::SendMsg(PACKET& packet) //패킷을 
{
	int send_bytes = 0;
	do
	{
		int once_send = send(socket_, (char*)& packet, packet.ph.len - send_bytes, 0);
		if (once_send == SOCKET_ERROR)
		{
			if(WSAGetLastError() == WSAEWOULDBLOCK)
			{ }
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
