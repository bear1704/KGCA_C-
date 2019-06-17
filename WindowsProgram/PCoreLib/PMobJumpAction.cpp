#include "PMobJumpAction.h"
#include "PMonster.h"


PMobJumpAction::PMobJumpAction(PMonster* parent) : PMobState(parent)
{
}


PMobJumpAction::~PMobJumpAction()
{
}

void PMobJumpAction::Process()
{

	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::JUMP)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::JUMP));
		owner_->get_physics_().StartJump();
	}


	if (owner_->get_physics_().get_isjump() == false)
	{
		owner_->SetTransition(FSM_Event::JUMP_END);
	}

}
