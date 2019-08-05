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

	if (PCollision::GetInstance().RectInRect(target->get_collision_rect_(), owner_->get_collision_rect_()))
	{  //플레이어와의 충돌 체크 
		if(target->get_hit_() == false)
			target->set_hit_(true);
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
