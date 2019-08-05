#include "PMobDeadAction.h"
#include "PMonster.h"


PMobDeadAction::PMobDeadAction(PMonster* parent) : PMobState(parent)
{
}


PMobDeadAction::~PMobDeadAction()
{
}

void PMobDeadAction::Process(PPlayerCharacter * target)
{


	progress_time += g_SecondPerFrame;

	if (progress_time > 15.0f)
	{
		progress_time = 0.0f;
		owner_->SetTransition(FSM_Event::MOB_TIME_OUT);
	}
}
