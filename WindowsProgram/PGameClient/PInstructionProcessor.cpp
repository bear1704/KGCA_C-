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
			{return !PInstructionManager::GetInstance().IsQueueEmpty(); }); //ť�� ���� �ʾҴٸ� ����

		//�Ʒ��� ��������

	}

}
