#include "PMobJumpAction.h"
#include "PMonster.h"


PMobJumpAction::PMobJumpAction(PMonster* parent) : PMobState(parent)
{
}


PMobJumpAction::~PMobJumpAction()
{
}

void PMobJumpAction::Process(PPlayerCharacter* target)
{



	if (PCollision::GetInstance().RectInRect(target->get_collision_rect_(), owner_->get_collision_rect_()))
	{  //�÷��̾���� �浹 üũ 
		target->set_hit_(true);
	}

	
	if (owner_->get_ishit_())
	{
		owner_->set_ishit_(false);
		owner_->SetTransition(FSM_Event::HIT);
	}

	if (owner_->get_physics_().get_isjump() == false)
	{
		owner_->SetTransition(FSM_Event::JUMP_END);
	}

}