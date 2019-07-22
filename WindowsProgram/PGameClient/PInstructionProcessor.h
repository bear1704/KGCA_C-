#pragma once
#include "PScene.h"
#include "TServerStd.h"
#include "PProtocol.h"
#include "PInstructionManager.h"

class PInstructionProcessor
{
private:
	PScene* current_scene_;
	std::mutex process_mutex_;

public:
	PInstructionProcessor();
	~PInstructionProcessor();
	
	void BindScene(PScene* current_scene);
	std::thread process_thread_;
	void ProcessInstruction();


};

