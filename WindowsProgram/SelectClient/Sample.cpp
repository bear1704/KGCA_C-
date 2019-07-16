#include "..\PNetworkLib\Sample.h"
#include "Sample.h"
#include "PNormalSelect.h"

char username[] = "박수찬";

bool Sample::Init()
{
	//1.초기화
	if (!network_.Init())
		return false;

	//2. 접속
	if (!network_.Connect("192.168.0.27", 10000, hWnd))
		return false;

	//3. 모델 선택
	network_.set_current_model(make_shared<PNormalSelect>(network_.get_socket()));
	return true;

}

bool Sample::PreFrame()
{
	network_.Frame();
	PacketProcessFromRecvPool();
	return true;
}

bool Sample::Frame()
{
	Sleep(500);
	network_.SendMsg(PACKET_CHAR_MSG, username , sizeof(username));
	return true;
}

bool Sample::PostFrame()
{
	network_.SendFromPacketPool();
	return true;
}

bool Sample::PostRender()
{
	return false;
}



bool Sample::Release()
{
	network_.Release();
	return true;
}

bool Sample::PacketProcessFromRecvPool()
{
	std::list<UPACKET>& recv_pool = PNetwork::get_recv_pool();
	for (UPACKET& packet : recv_pool)
	{
		char msgbuf[64];
		ZeroMemory(msgbuf, sizeof(msgbuf));


		switch (packet.ph.type)
		{
		case PACKET_SC_BROADCAST_DROPUSER:
		{
			USER_BASE userinfo;
			ZeroMemory(&userinfo, sizeof(USER_BASE));
			memcpy(&userinfo, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);
			sprintf_s(msgbuf, sizeof(msgbuf),  "[%s님이 퇴장하셨습니다.]\n", userinfo.user_name);
			OutputDebugStringA(msgbuf);
		}break;
		case PACKET_SC_DROP_ACK:
		{
			OutputDebugString(L"채팅방에서 퇴장하였습니다\n");
		}break;
		case PACKET_SC_JOIN_SIGNIN:
		{
			OutputDebugString(L"채팅방에 입장하였습니다\n");
		}
		case PACKET_CHAR_MSG:
		{
			USER_CHAT_MSG message;
			ZeroMemory(&message, sizeof(USER_CHAT_MSG));
			memcpy(&message, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);

			c_string msg = "[";
			msg += message.user_name;
			msg += "] ";
			msg += message.msg;
			OutputDebugStringA(msg.c_str());

		}break;
		case PACKET_SC_CHAR_NAME_REQ:
		{
			USER_BASE data;
			ZeroMemory(&data, sizeof(USER_BASE));
			data.index = 8;
			memcpy(data.user_name, username, strlen(username));
			network_.get_current_model()->SendMsg(network_.get_socket(), PACKET_CS_CHAR_NAME_ACK,
				(char*)& data, sizeof(USER_BASE));
		}break;

		}
	}

	PNetwork::get_recv_pool().clear();


	return true;
}

LRESULT Sample::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return network_.MsgProc(hwnd, msg, wParam, lParam);
}

Sample::Sample()
{

}

Sample::~Sample()
{

}

PNetwork& Sample::get_network_ref()
{
	return network_;
}

PCORE_RUN(L"client", 0, 0, 800, 600);