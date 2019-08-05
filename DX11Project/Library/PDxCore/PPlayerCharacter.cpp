#include "PPlayerCharacter.h"
#include "PIdleAction.h"
#include "PMoveAction.h"
#include "PJumpAction.h"
#include "PAttackAction.h"
#include "PDeadAction.h"
#include "PHitAction.h"

PPlayerCharacter::PPlayerCharacter()
{
	flickering_rate = 0.0f;
	invincible_rate = 0.0f;
}


PPlayerCharacter::~PPlayerCharacter()
{
	
}

bool PPlayerCharacter::Init()
{

	action_list_.insert(std::make_pair(FSM_State::IDLE, new PIdleAction(this)));
	action_list_.insert(std::make_pair(FSM_State::MOVE, new PMoveAction(this)));
	action_list_.insert(std::make_pair(FSM_State::JUMP, new PJumpAction(this)));
	action_list_.insert(std::make_pair(FSM_State::ATTACK, new PAttackAction(this)));
	action_list_.insert(std::make_pair(FSM_State::HIT, new PHitAction(this)));
	action_list_.insert(std::make_pair(FSM_State::DEAD, new PDeadAction(this)));

	current_player_action_ = action_list_[FSM_State::IDLE];
	current_player_state_ = FSM_State::IDLE;
	
	player_fsm_.Add(FSM_State::IDLE, FSM_Event::HPEMPTY, FSM_State::DEAD);
	//MOVE
	player_fsm_.Add(FSM_State::IDLE, FSM_Event::INPUT_MOVE, FSM_State::MOVE);
	player_fsm_.Add(FSM_State::MOVE, FSM_Event::INPUT_NONE, FSM_State::IDLE);
	player_fsm_.Add(FSM_State::MOVE, FSM_Event::HPEMPTY, FSM_State::DEAD);
	//JUMP
	player_fsm_.Add(FSM_State::IDLE, FSM_Event::INPUT_JUMP, FSM_State::JUMP);
	player_fsm_.Add(FSM_State::MOVE, FSM_Event::INPUT_JUMP, FSM_State::JUMP);
	player_fsm_.Add(FSM_State::JUMP, FSM_Event::JUMP_END, FSM_State::MOVE);

	//ATTACK
	player_fsm_.Add(FSM_State::IDLE, FSM_Event::INPUT_ATTACK, FSM_State::ATTACK);
	player_fsm_.Add(FSM_State::MOVE, FSM_Event::INPUT_ATTACK, FSM_State::ATTACK);
	player_fsm_.Add(FSM_State::JUMP, FSM_Event::INPUT_ATTACK, FSM_State::ATTACK);
	player_fsm_.Add(FSM_State::ATTACK, FSM_Event::ATTACK_END, FSM_State::IDLE);//MOVE, JUMP�� ���ݽÿ� �Ұ�����. ���� IDLE�θ� ȸ��

	//HIT
	player_fsm_.Add(FSM_State::IDLE, FSM_Event::HIT, FSM_State::HIT);
	player_fsm_.Add(FSM_State::MOVE, FSM_Event::HIT, FSM_State::HIT);
	player_fsm_.Add(FSM_State::JUMP, FSM_Event::HIT, FSM_State::HIT);
	player_fsm_.Add(FSM_State::ATTACK, FSM_Event::HIT, FSM_State::HIT);
	player_fsm_.Add(FSM_State::HIT, FSM_Event::TIME_OUT, FSM_State::IDLE);
	player_fsm_.Add(FSM_State::HIT, FSM_Event::HPEMPTY, FSM_State::DEAD);



	return true;
}

bool PPlayerCharacter::Frame()
{
	SavePrevPosition();
	ProcessAction();
	set_collision_box_(collision_box_norm_);
	Movement();
	physics_.Jump(physics_.jump_init_time, position_, 800, 0.2f);
	physics_.Gravity(position_, gravity_);
	PlatformWallCollision();
	return true;
}

bool PPlayerCharacter::Render()
{

	return true;
}

bool PPlayerCharacter::Release()
{

	return true;
}

void PPlayerCharacter::Movement()
{

	if (g_InputActionMap.jumpKey == KEYSTAT::KEY_PUSH)
	{
		if(client_owner_character_)
			physics_.StartJump();
	}
	if (g_InputActionMap.dKey == KEYSTAT::KEY_PUSH)
	{
		//status.ModifyEXP(30);
	}if (g_InputActionMap.fKey == KEYSTAT::KEY_PUSH)
	{
		//status.ModifyEXP(10030);
	}

}

void PPlayerCharacter::Set(multibyte_string data_path, multibyte_string object_name, pPoint position)
{
	PObjectInfoManager::GetInstance().LoadDataFromScript(data_path, ObjectLoadType::CHARACTER);
	ObjectInfo info = *(PObjectInfoManager::GetInstance().get_object_info_list_from_map(object_name));

	character_name_ = info.object_name_;
	object_name_ = info.object_name_;
	position_ = position;
	collision_box_norm_ = info.collision_box_;
	alpha_ = info.alpha_;
	scale_ = info.scale_;
	move_speed_ = info.move_speed_;

	if (character_name_ == L"player")
		client_owner_character_ = true;

	FLOAT_RECT scaled_collisionbox_norm = { collision_box_norm_.left*scale_, collision_box_norm_.top*scale_ ,
	collision_box_norm_.right*scale_, collision_box_norm_.bottom*scale_ };

	collision_box_norm_ = scaled_collisionbox_norm;
	set_collision_box_(collision_box_norm_);

	spawn_position_ = position;
	attack_collision_box_ = { 0, 0, 105, 100 }; //�ӽ÷� position,ũ�� ���� 

	if(get_client_owner_character())
		P2DCamera::GetInstance().set_character_collision_rect(&collision_box_); //ĳ���� only
}


void PPlayerCharacter::SetTransition(FSM_Event event)
{
	PFiniteState* state = player_fsm_.get_state(current_player_state_); //FSM�������� �÷��̾��� ���� ������Ʈ�� �����´�.
	if (!state) return; //���� ������Ʈ�� ������ ���� 

	FSM_State next = state->get_next_state(event); //���� ������Ʈ���� �̺�Ʈ�� Ʈ�����ǵǴ� ���� ������Ʈ ��������
	
	if (next == FSM_State::ERR) //���� ������Ʈ�� ������ ���� ������Ʈ ����
		next = current_player_state_;


	current_player_action_ = action_list_[next]; //�� ���� ������Ʈ�� �°� �׼� ��������.(������Ʈ ��ȯ)
	current_player_state_ = next;  //���� ������Ʈ ������ ����������Ʈ�� ����Ű�� ��ȯ
}

void PPlayerCharacter::ProcessAction()
{
	current_player_action_->Process();
}

void PPlayerCharacter::set_hit_(bool hit)
{
	hit_ = hit;
}


void PPlayerCharacter::set_client_owner_character(bool isowner)
{
	client_owner_character_ = isowner;
}

void PPlayerCharacter::set_right_dir(bool isright)
{
	automata_right_dir_ = isright;
}



void PPlayerCharacter::set_is_character_dead(bool isdead)
{
	is_character_dead_ = isdead;
}

bool PPlayerCharacter::get_hit_()
{
	return hit_;
}



bool PPlayerCharacter::get_client_owner_character()
{
	return client_owner_character_;
}

bool PPlayerCharacter::get_is_character_dead()
{
	return is_character_dead_;
}

bool PPlayerCharacter::is_right_dir()
{
	return automata_right_dir_;
}
