#include "PMonster.h"
#include "PMobIdleAction.h"
#include "PMobAttackAction.h"
#include "PMobMoveAction.h"
#include "PMobJumpAction.h"
#include "PMobDeadAction.h"
#include "PMobHitAction.h"


PMonster::PMonster()
{

}


PMonster::~PMonster()
{
}

bool PMonster::Init()
{
	

	action_list_.insert((std::make_pair(FSM_State::IDLE, new PMobIdleAction(this))));
	action_list_.insert((std::make_pair(FSM_State::MOVE, new PMobMoveAction(this))));
	action_list_.insert((std::make_pair(FSM_State::JUMP, new PMobJumpAction(this))));

	current_monster_action_ = action_list_[FSM_State::IDLE];
	current_monster_state_ = FSM_State::IDLE;

	monster_fsm_.Add(FSM_State::IDLE, FSM_Event::MOB_TIME_OUT, FSM_State::MOVE);
	monster_fsm_.Add(FSM_State::MOVE, FSM_Event::MOB_TIME_OUT, FSM_State::IDLE);
	monster_fsm_.Add(FSM_State::IDLE, FSM_Event::MOB_JUMP_TIME_OUT, FSM_State::JUMP);
	monster_fsm_.Add(FSM_State::MOVE, FSM_Event::MOB_JUMP_TIME_OUT, FSM_State::JUMP);
	monster_fsm_.Add(FSM_State::JUMP, FSM_Event::JUMP_END, FSM_State::MOVE);


	return false;
}

bool PMonster::Frame()
{
	SavePrevPosition();
	sprite_.Frame();
	set_collision_box_(collision_box_norm_);
	ProcessAction();
	Movement();
	physics_.Gravity(position_, gravity_);
	physics_.Jump(physics_.jump_init_time, position_, 650, 0.25f);
	PlatformWallCollision();
	MonsterWallCollision();
	return false;
}

bool PMonster::Render()
{
	Spawn();
	return false;
}

bool PMonster::Release()
{
	sprite_.Release();
	return false;
}

void PMonster::Set(multibyte_string data_path, multibyte_string object_name, pPoint position)
{
	PObjectInfoManager::GetInstance().LoadDataFromScript(data_path);
	ObjectInfo info = *(PObjectInfoManager::GetInstance().get_object_info_list_from_map(object_name));

	character_name_ = info.object_name_;
	object_name_ = info.object_name_;
	position_ = position;
	collision_box_norm_ = info.collision_box_;
	alpha_ = info.alpha_;
	scale_ = info.scale_;
	move_speed_ = info.move_speed_;

	PSpriteManager::GetInstance().LoadDataFromScript(info.sprite_path);
	sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(info.sprite_name), alpha_, scale_);
	sprite_.SetPosition(position_.x, position_.y);

	FLOAT_RECT scaled_collisionbox_norm = { collision_box_norm_.left*scale_, collision_box_norm_.top*scale_ ,
	collision_box_norm_.right*scale_, collision_box_norm_.bottom*scale_ };

	collision_box_norm_ = scaled_collisionbox_norm;
	set_collision_box_(collision_box_norm_);

	direction_side_ = SIDE::RIGHT;
	//몬스터는 카메라를 붙이지 않음.
}

void PMonster::MonsterWallCollision()
{

	const std::vector<FLOAT_RECT>& monster_wall_list = PWallAndPlatform::GetInstance().get_monster_wall_list_();

	for (auto& it : monster_wall_list)
	{
		if (PCollision::GetInstance().RectInRect(it, collision_box_))
		{
			if (direction_side_ == SIDE::LEFT)
			{
				direction_side_ = SIDE::RIGHT;
				position_.x = it.left + it.right + collision_box_.right / 2 + 1.0f; //1.0f =  가중치
			}
			else
			{
				direction_side_ = SIDE::LEFT;
				position_.x = it.left -  collision_box_.right / 2  - 1.0f;
			}
		}
	}
}

void PMonster::Movement()
{
	sprite_.SetPosition(position_.x, position_.y);
}

SIDE PMonster::get_direction_side_()
{
	return direction_side_;
}

void PMonster::set_direction_side_(SIDE side)
{
	direction_side_ = side;
}

void PMonster::SetTransition(FSM_Event event)
{
	PFiniteState* state = monster_fsm_.get_state(current_monster_state_); //FSM공간에서 플레이어의 현재 스테이트를 가져온다.
	if (!state) return; //현재 스테이트가 없으면 에러 

	FSM_State next = state->get_next_state(event); //현재 스테이트에서 이벤트로 트랜지션되는 다음 스테이트 가져오기
	current_monster_action_ = action_list_[next]; //그 다음 스테이트에 맞게 액션 가져오기.(스테이트 전환)
	current_monster_state_ = next;  //현재 스테이트 변수도 다음스테이트를 가리키게 전환

}

void PMonster::ProcessAction()
{
	current_monster_action_->Process();
}

bool PMonster::check_hit(FLOAT_RECT player_attack_col)
{
	if (PCollision::GetInstance().RectInRect(player_attack_col, collision_box_))
		return true;

	return false;
}

void PMonster::set_ishit_(bool hit)
{
	ishit_ = hit;
}
