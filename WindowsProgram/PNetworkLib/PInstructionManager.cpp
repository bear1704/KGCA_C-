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
	std::lock_guard<std::mutex> lk(mutex_);
	{
		instruction_queue_.push(packet);
	}
		NotifyProcessEvent();
}

PACKET PInstructionManager::PopBackInstruction()
{
	
	
	if (!instruction_queue_.empty())
	{
		std::lock_guard<std::mutex> lk(mutex_);
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
	process_event_.notify_all();
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
