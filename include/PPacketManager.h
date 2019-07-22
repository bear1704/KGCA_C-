#pragma once
#include "TServerStd.h"
#include "PProtocol.h"
#include <process.h>
#include "PInstructionManager.h"

class PUserManager;
class PUser;



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
	int* recv_notify_request_count;
	int* send_notify_request_count;

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
	HANDLE send_thread_;
	HANDLE process_thread_;
	ThreadParamSet param_set_;



public:
	void PushPacket(PushType type, PACKET packet);
	void PushPacket(PUser* user, int protocol, char* data, int data_size, PushType type);
	bool NotifyReceiveEvent();
	bool NotifyProcessEvent();
	bool SendPacketFromPacketPool(SOCKET socket, PACKET packet);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void ThreadInit(SOCKET* socket);
	static bool is_both_pool_empty_;
	static std::mutex mutex_;
	static std::mutex process_mutex_;
	static std::mutex recv_mutex_;
	int recv_notify_request_count_;
	int send_notify_request_count_;

	static std::condition_variable recv_event_;
	static std::condition_variable process_event_;


public:
	~PPacketManager();


};

