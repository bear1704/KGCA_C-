#include "PBossMonster.h"
#include "PBossMobIdleAction.h"
#include "PBossMobHitAction.h"
#include "PPlayerCharacter.h"
#include "PScene.h"

HANDLE g_handle_4s_sprite_timer_queue_;
HANDLE g_handle_4s_sprite_timer_;



PBossMonster::PBossMonster()
{
}

PBossMonster::~PBossMonster()
{
}

bool PBossMonster::Init()
{
	action_list_.insert((std::make_pair(FSM_State::BOSS_IDLE, new PBossMobIdleAction(this))));
	action_list_.insert((std::make_pair(FSM_State::BOSS_HIT, new PBossMobHitAction(this))));

	current_boss_monster_action_ = action_list_[FSM_State::BOSS_IDLE];
	current_boss_monster_state_ = FSM_State::BOSS_IDLE;

	boss_monster_fsm_.Add(FSM_State::BOSS_IDLE, FSM_Event::HIT, FSM_State::BOSS_HIT);
	boss_monster_fsm_.Add(FSM_State::BOSS_HIT, FSM_Event::INPUT_NONE, FSM_State::BOSS_IDLE);

	return false;
}

void PBossMonster::Set(multibyte_string data_path, multibyte_string object_name, pPoint position)
{
	PObjectInfoManager::GetInstance().LoadDataFromScript(data_path, ObjectLoadType::CHARACTER);
	ObjectInfo info = *(PObjectInfoManager::GetInstance().get_object_info_list_from_map(object_name));

	character_name_ = info.object_name_;
	object_name_ = info.object_name_;
	position_ = position;
	collision_box_norm_ = info.collision_box_;
	alpha_ = info.alpha_;
	scale_ = info.scale_;



	FLOAT_RECT scaled_collisionbox_norm = { collision_box_norm_.left * scale_, collision_box_norm_.top * scale_ ,
	collision_box_norm_.right * scale_, collision_box_norm_.bottom * scale_ };

	collision_box_norm_ = scaled_collisionbox_norm;
	set_collision_box_(collision_box_norm_);

	spawn_position_ = position;

}

void PBossMonster::SetForServer(multibyte_string data_path, multibyte_string object_name, pPoint position)
{
	PObjectInfoManager::GetInstance().LoadDataFromScript(data_path, ObjectLoadType::CHARACTER);
	ObjectInfo info = *(PObjectInfoManager::GetInstance().get_object_info_list_from_map(object_name));

	character_name_ = info.object_name_;
	object_name_ = info.object_name_;
	position_ = position;
	collision_box_norm_ = info.collision_box_;
	alpha_ = info.alpha_;
	scale_ = info.scale_;

	FLOAT_RECT scaled_collisionbox_norm = { collision_box_norm_.left * scale_, collision_box_norm_.top * scale_ ,
	collision_box_norm_.right * scale_, collision_box_norm_.bottom * scale_ };

	collision_box_norm_ = scaled_collisionbox_norm;
	set_collision_box_(collision_box_norm_);
}

void PBossMonster::SetTransition(FSM_Event event)
{
	
		PFiniteState* state = boss_monster_fsm_.get_state(current_boss_monster_state_); //FSM�������� �÷��̾��� ���� ������Ʈ�� �����´�.
		if (!state) assert(!state); //���� ������Ʈ�� ������ ���� 

		FSM_State next = state->get_next_state(event); //���� ������Ʈ���� �̺�Ʈ�� Ʈ�����ǵǴ� ���� ������Ʈ ��������

		if (next == FSM_State::ERR) //���� ������Ʈ�� ������ ���� ������Ʈ ����
			next = current_boss_monster_state_;

		current_boss_monster_action_ = action_list_[next]; //�� ���� ������Ʈ�� �°� �׼� ��������.(������Ʈ ��ȯ)
		current_boss_monster_state_ = next;  //���� ������Ʈ ������ ����������Ʈ�� ����Ű�� ��ȯ

	
}

void PBossMonster::ProcessAction()
{
	current_boss_monster_action_->Process();
}

bool PBossMonster::check_hit(FLOAT_RECT player_attack_col)
{
	if (PCollision::GetInstance().RectInRect(player_attack_col, collision_box_))
		return true;

	return false;
}

FSM_State PBossMonster::get_current_monster_state_()
{
	return FSM_State();
}

bool PBossMonster::Frame()
{

	ProcessAction();
	set_collision_box_(collision_box_norm_);

	if (current_skill_ != nullptr)
		current_skill_->Frame();


	return false;
}

bool PBossMonster::Render()
{

	if (current_skill_ != nullptr)
		current_skill_->Render();
	return false;
}

bool PBossMonster::Release()
{

	return false;
}


void PBossMonster::set_ishit_(bool hit)
{
	ishit_ = hit;
}

bool PBossMonster::get_ishit_()
{
	return ishit_;
}

void PBossMonster::set_be_received_damage_(int damage)
{
	be_received_damage_ = damage;
}

int PBossMonster::get_be_received_damage()
{
	return be_received_damage_;
}

void PBossMonster::StatusSet(multibyte_string status_path, multibyte_string object_name)
{

	
	
}
