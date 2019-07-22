#include "PInstructionProcessor.h"



PInstructionProcessor::PInstructionProcessor()
{
}


PInstructionProcessor::~PInstructionProcessor()
{
}

void PInstructionProcessor::BindScene(PScene * current_scene)
{
	current_scene_ = current_scene;
}

void PInstructionProcessor::ProcessInstruction()
{

	while (true)
	{

		std::unique_lock<std::mutex> ul(process_mutex_);
		PInstructionManager::GetInstance().process_event_.wait(ul, []()
			{return !PInstructionManager::GetInstance().IsQueueEmpty(); }); //큐가 비지 않았다면 실행

		//아래에 구현내용

	}

}
