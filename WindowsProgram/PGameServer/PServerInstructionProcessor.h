#pragma once
#include "TServerStd.h"
#include "PProtocol.h"
#include "PInstructionManager.h"
#include "PUserManager.h"
#include "PPacketManager.h"
#include "PScene.h"
#include "PNetworkTimer.h"
#include "TServerStd.h"


class PServerInstructionProcessor : public PSingleton<PServerInstructionProcessor>
{
private:
	friend class PSingleton<PServerInstructionProcessor>;
	

	PServerInstructionProcessor();
public:
	~PServerInstructionProcessor();
	
	std::thread process_thread_;
	void ProcessInstruction();

	static std::mutex process_mutex1_;
	std::mutex spawn_mutex_;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	bool Broadcast(PACKET& packet);

};

