#include "PPlayerCharacter.h"
#include "PIdleAction.h"
#include "PMoveAction.h"
#include "PJumpAction.h"
#include "PAttackAction.h"
#include "PDeadAction.h"
#include "PHitAction.h"

PPlayerCharacter::PPlayerCharacter()
{
}


PPlayerCharacter::~PPlayerCharacter()
{
	
}

bool PPlayerCharacter::Init()
{
	status.Init();
	action_list_.insert(std::make_pair(FSM_State::IDLE, new PIdleAction(this)));
	action_list_.insert(std::make_pair(FSM_State::MOVE, new PMoveAction(this)));
	action_list_.insert(std::make_pair(FSM_State::JUMP, new PJumpAction(this)));
	action_list_.insert(std::make_pair(FSM_State::ATTACK, new PAttackAction(this)));
	//action_list_.insert(std::make_pair(FSM_State::DEAD, new PDeadAction(this)));
	//action_list_.insert(std::make_pair(FSM_State::HIT, new PHitAction(this)));
	current_player_action_ = action_list_[FSM_State::IDLE];
	current_player_state_ = FSM_State::IDLE;
	
	//MOVE
	player_fsm_.Add(FSM_State::IDLE, FSM_Event::INPUT_MOVE, FSM_State::MOVE);
	player_fsm_.Add(FSM_State::MOVE, FSM_Event::INPUT_NONE, FSM_State::IDLE);
	//JUMP
	player_fsm_.Add(FSM_State::IDLE, FSM_Event::INPUT_JUMP, FSM_State::JUMP);
	player_fsm_.Add(FSM_State::MOVE, FSM_Event::INPUT_JUMP, FSM_State::JUMP);
	player_fsm_.Add(FSM_State::JUMP, FSM_Event::JUMP_END, FSM_State::MOVE);
	//ATTACK
	player_fsm_.Add(FSM_State::IDLE, FSM_Event::INPUT_ATTACK, FSM_State::ATTACK);
	player_fsm_.Add(FSM_State::MOVE, FSM_Event::INPUT_ATTACK, FSM_State::ATTACK);
	player_fsm_.Add(FSM_State::JUMP, FSM_Event::INPUT_ATTACK, FSM_State::ATTACK);
	player_fsm_.Add(FSM_State::ATTACK, FSM_Event::ATTACK_END, FSM_State::IDLE);//MOVE, JUMP는 공격시에 불가능함. 오직 IDLE로만 회귀





	return true;
}

bool PPlayerCharacter::Frame()
{
	SavePrevPosition();
	sprite_.Frame();
	set_collision_box_(collision_box_norm_);
	Movement();
	ProcessAction();
	physics_.Jump(physics_.jump_init_time, position_, 800, 0.2f);
	physics_.Gravity(position_, gravity_);
	PlatformWallCollision();
	status.Frame();
	return true;
}

bool PPlayerCharacter::Render()
{
	Spawn();
	status.Render();
	return true;
}

bool PPlayerCharacter::Release()
{
	sprite_.Release();
	status.Release();
	return true;
}

void PPlayerCharacter::Movement()
{


	//if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
	//{
	//	is_reversal_ = false;
	//	set_position_(pPoint(position_.x - move_speed_ * g_SecondPerFrame, position_.y));
	//}
	//if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
	//{
	//	is_reversal_ = true;
	//	set_position_(pPoint(position_.x + move_speed_ * g_SecondPerFrame, position_.y));
	//}

	if (g_InputActionMap.jumpKey == KEYSTAT::KEY_PUSH)
	{
		physics_.StartJump();
	}
	if (g_InputActionMap.qKey == KEYSTAT::KEY_PUSH)
	{
		status.ModifyHP(240);
	}
	if (g_InputActionMap.wKey == KEYSTAT::KEY_PUSH)
	{
		status.ModifyHP(1930);
	}
	if (g_InputActionMap.aKey == KEYSTAT::KEY_PUSH)
	{
		status.ModifyMP(10);
	}
	if (g_InputActionMap.sKey == KEYSTAT::KEY_PUSH)
	{
		status.ModifyMP(300);
	}
	if (g_InputActionMap.dKey == KEYSTAT::KEY_PUSH)
	{
		status.ModifyEXP(30);
	}if (g_InputActionMap.fKey == KEYSTAT::KEY_PUSH)
	{
		status.ModifyEXP(10000);
	}

}

void PPlayerCharacter::Set(multibyte_string data_path, multibyte_string object_name, pPoint position)
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

	attack_collision_box_ = { 0, 0, 40, 100 }; //임시로 position,크기 지정 

	P2DCamera::GetInstance().set_character_collision_rect(&collision_box_); //캐릭터 only
}


void PPlayerCharacter::SetTransition(FSM_Event event)
{
	PFiniteState* state = player_fsm_.get_state(current_player_state_); //FSM공간에서 플레이어의 현재 스테이트를 가져온다.
	if (!state) return; //현재 스테이트가 없으면 에러 

	FSM_State next = state->get_next_state(event); //현재 스테이트에서 이벤트로 트랜지션되는 다음 스테이트 가져오기
	current_player_action_ = action_list_[next]; //그 다음 스테이트에 맞게 액션 가져오기.(스테이트 전환)
	current_player_state_ = next;  //현재 스테이트 변수도 다음스테이트를 가리키게 전환
}

void PPlayerCharacter::ProcessAction()
{
	current_player_action_->Process();
}
