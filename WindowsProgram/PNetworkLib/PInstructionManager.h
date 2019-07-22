#pragma once
#include "TServerStd.h"
#include "PProtocol.h"

class PInstructionManager : public PSingleton<PInstructionManager>
{

private:
	PInstructionManager();
	friend class PSingleton<PInstructionManager>;
public:
	~PInstructionManager();

private:
	std::queue<PACKET> instruction_queue_;
	
public:
	void AddInstruction(PACKET packet);
	PACKET PopBackInstruction();
	bool IsQueueEmpty();
	void NotifyProcessEvent();
	
	static condition_variable process_event_;

	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

};
