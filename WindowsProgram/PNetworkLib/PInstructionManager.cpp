#include "PInstructionManager.h"

std::condition_variable PInstructionManager::process_event_;

PInstructionManager::PInstructionManager()
{
	instruction_event_count_ = 0;
}


PInstructionManager::~PInstructionManager()
{
}

void PInstructionManager::AddInstruction(PACKET packet)
{
		instruction_queue_.push(packet);
		NotifyProcessEvent();
}

PACKET PInstructionManager::PopBackInstruction()
{
	//std::lock_guard<std::mutex> lk(mutex_);
	
	if (!instruction_queue_.empty())
	{
		PACKET p = instruction_queue_.front();
		instruction_queue_.pop();
		return p;
	}

	assert(false);
}

bool PInstructionManager::IsQueueEmpty()
{
	return instruction_queue_.empty();
}

void PInstructionManager::NotifyProcessEvent()
{
	//std::lock_guard<std::mutex> lk(mutex_);
	instruction_event_count_ += 1;
	process_event_.notify_one();
}

bool PInstructionManager::Init()
{
	return false;
}

bool PInstructionManager::Frame()
{
	return false;
}

bool PInstructionManager::Render()
{
	return false;
}

bool PInstructionManager::Release()
{
	return false;
}
