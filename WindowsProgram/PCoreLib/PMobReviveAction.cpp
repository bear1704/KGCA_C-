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
	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::IDLE) //Revive는 IDLE과 공유
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::IDLE));
		owner_->set_position_(owner_->get_spawn_position_());
		owner_->get_sprite_()->set_alpha_(0.0f);
		owner_->get_status().ModifyHP(owner_->get_status().get_max_hp());
	}

	float current_alpha = owner_->get_sprite_()->get_alpha_();
	current_alpha += g_SecondPerFrame * 1.0f;
	owner_->get_sprite_()->set_alpha_(current_alpha);

	if (owner_->get_sprite_()->get_alpha_() > 1.0f)
	{
		owner_->get_sprite_()->set_alpha_(1.0f);
	}

	progress_time += g_SecondPerFrame;

	if (progress_time > 7.0f)
	{
		progress_time = 0.0f;
		owner_->SetTransition(FSM_Event::MOB_TIME_OUT);
	}

}
