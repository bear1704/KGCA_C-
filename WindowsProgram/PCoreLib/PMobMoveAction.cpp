#include "PMobMoveAction.h"
#include "PMonster.h"


PMobMoveAction::PMobMoveAction(PMonster* parent) : PMobState(parent)
{
}


PMobMoveAction::~PMobMoveAction()
{
}

void PMobMoveAction::Process()
{
	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::MOVE)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::MOVE));
	}


	progress_time_ += g_SecondPerFrame;
	direction_change_progress_time_ += g_SecondPerFrame;


	
	if (direction_change_progress_time_ > direction_change_time)
	{
		std::random_device r;
		std::mt19937 engine(r());
		std::uniform_int_distribution<int> distribution(0, 1);
		auto generator = std::bind(distribution, engine);
		int random = generator();

		//if (owner_->get_direction_side_() == SIDE::LEFT)
		if(random == 0)
		{
			owner_->set_direction_side_(SIDE::RIGHT);
			direction_change_progress_time_ = 0.0f;
		}
		else
		{
			owner_->set_direction_side_(SIDE::LEFT);
			direction_change_progress_time_ = 0.0f;
		}

		direction_change_time = random + 3;
	}

	if (progress_time_ > change_time_)
	{
		std::random_device r;
		std::mt19937 engine(r());
		std::uniform_int_distribution<int> distribution(0, 1);
		auto generator = std::bind(distribution, engine);
		int random = generator();

		if (random == 0)
		{
			owner_->SetTransition(FSM_Event::MOB_TIME_OUT);
		}
		else
		{
			owner_->SetTransition(FSM_Event::MOB_TIME_OUT);
			//owner_->SetTransition(FSM_Event::MOB_JUMP_TIME_OUT); //Jump
		}
		progress_time_ = 0.0f;
		change_time_ = random + 5;
	}

	if (owner_->get_direction_side_() == SIDE::LEFT)
	{
		owner_->get_is_reversal_() = false;
		owner_->set_position_(pPoint(owner_->get_position_().x - owner_->get_move_speed_() * g_SecondPerFrame, owner_->get_position_().y));
	}
	else
	{
		owner_->get_is_reversal_() = true;
		owner_->set_position_(pPoint(owner_->get_position_().x + owner_->get_move_speed_() * g_SecondPerFrame, owner_->get_position_().y));
	}
	

}
