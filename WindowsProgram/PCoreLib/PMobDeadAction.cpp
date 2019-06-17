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
	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::DEAD)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::DEAD));
	}

	float current_alpha = owner_->get_sprite_()->get_alpha_();
	current_alpha -= g_SecondPerFrame * 1.0f;
	owner_->get_sprite_()->set_alpha_(current_alpha);

	if (owner_->get_sprite_()->get_alpha_() < 0.1f)
	{
		owner_->get_sprite_()->set_alpha_(0.0f);
	}
}
