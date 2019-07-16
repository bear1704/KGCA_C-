#pragma once
#include "TServerStd.h"
#include "PProtocol.h"
#include <process.h>

static HANDLE mutex_;

enum class PushType
{
	SEND,
	RECV,
};

struct ThreadParamSet
{
	std::list<PACKET>* send_packet_pool;
	std::list<PACKET>* recv_packet_pool;
	SOCKET* socket;

};


class PPacketManager : public PSingleton<PPacketManager>
{
private:
	PPacketManager();

private:
	friend class PSingleton<PPacketManager>;
	std::list<PACKET> send_packet_pool_;
	std::list<PACKET> recv_packet_pool_;
	HANDLE receive_thread_;
	HANDLE process_thread_;
	ThreadParamSet param_set_;
public:
	//void Process();
	void PushPacket(PushType type, PACKET packet);
	bool RunRecvThread(SOCKET* socket);
	bool RunPacketProcess(SOCKET* socket);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	~PPacketManager();


};

