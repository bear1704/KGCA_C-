#include "PMobReviveAction.h"
#include "PMonster.h"


PMobReviveAction::PMobReviveAction(PMonster* parent) : PMobState(parent)
{
}


PMobReviveAction::~PMobReviveAction()
{
}

void PMobReviveAction::Process(PPlayerCharacter * target)
{

	if (PCollision::GetInstance().RectInRect(target->get_collision_rect_(), owner_->get_collision_rect_()) && progress_time > 3.0f)
	{  //플레이어와의 충돌 체크 
		target->set_hit_(true);
	}


	progress_time += g_SecondPerFrame;

	if (owner_->get_ishit_())
	{
		owner_->set_ishit_(false);
		owner_->SetTransition(FSM_Event::HIT);
	}

	if (progress_time > 7.0f)
	{
		progress_time = 0.0f;
		owner_->SetTransition(FSM_Event::MOB_TIME_OUT);
	}

}
