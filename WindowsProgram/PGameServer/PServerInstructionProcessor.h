#pragma once
#include "TServerStd.h"
#include "PProtocol.h"
#include "PInstructionManager.h"
#include "PUserManager.h"
#include "PPacketManager.h"
#include "PScene.h"


class PServerInstructionProcessor : public PSingleton<PServerInstructionProcessor>
{
private:
	friend class PSingleton<PServerInstructionProcessor>;
	
	std::mutex process_mutex1_;

	PServerInstructionProcessor();
public:
	~PServerInstructionProcessor();
	
	std::thread process_thread_;
	void ProcessInstruction();


public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

