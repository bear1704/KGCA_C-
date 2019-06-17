#include "PMobHitAction.h"
#include "PMonster.h"


PMobHitAction::PMobHitAction(PMonster* parent) : PMobState(parent)
{
}


PMobHitAction::~PMobHitAction()
{
}

void PMobHitAction::Process(PPlayerCharacter* target)
{

	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::HIT)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::HIT));
		owner_->dmg_comp->hit_world_pos = pPoint(owner_->get_position_().x, owner_->get_position_().y - 55.0f);
		owner_->dmg_comp->ResetDmgPresent();
	}


	if (owner_->get_status().get_hp_() <= 0)
	{
		owner_->SetTransition(FSM_Event::HPEMPTY);
		knockback_distance_ = 35.0f;
	}
	
	KnockBack();


	if (knockback_distance_ < 0)
	{
		owner_->SetTransition(FSM_Event::MOB_CHASE); 
		knockback_distance_ = 35.0f;
	}
	
}

void PMobHitAction::KnockBack()
{
	if (knockback_distance_ > 0)
	{
		pPoint pos = owner_->get_position_();
		pPoint nextpos;
		if(owner_->get_enemy_to_direction_side_() == SIDE::LEFT)
			nextpos = pPoint(pos.x + knockback_speed_ * g_SecondPerFrame, pos.y);
		else
			nextpos = pPoint(pos.x - knockback_speed_ * g_SecondPerFrame, pos.y);
		
		owner_->set_position_(nextpos);
		knockback_distance_ -= g_SecondPerFrame * knockback_speed_;
	}

}
