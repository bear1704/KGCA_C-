#include "PInstructionManager.h"

std::condition_variable PInstructionManager::process_event_;

PInstructionManager::PInstructionManager()
{
}


PInstructionManager::~PInstructionManager()
{
}

void PInstructionManager::AddInstruction(PACKET packet)
{
	instruction_queue_.push(packet);
}

PACKET PInstructionManager::PopBackInstruction()
{
	PACKET p =  instruction_queue_.front();
	instruction_queue_.pop();
	return p;
}

bool PInstructionManager::IsQueueEmpty()
{
	return instruction_queue_.empty();
}

void PInstructionManager::NotifyProcessEvent()
{
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
