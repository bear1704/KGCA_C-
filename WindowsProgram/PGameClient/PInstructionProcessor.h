#pragma once
#include "TServerStd.h"
#include "PProtocol.h"
#include "PScene.h"
#include "PInstructionManager.h"
#include "PUserManager.h"
#include "PPacketManager.h"


class PInstructionProcessor : public PSingleton<PInstructionProcessor>
{
private:
	friend class PSingleton<PInstructionProcessor>;
	
	PScene* current_scene_;
	std::mutex process_mutex_;

	PInstructionProcessor();
public:
	~PInstructionProcessor();
	
	void BindScene(PScene* current_scene);
	std::thread process_thread_;
	void ProcessInstruction();


public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

