#include "PBossMonster.h"
#include "PBossMobIdleAction.h"
#include "PBossMobHitAction.h"

PBossMonster::PBossMonster()
{
}

PBossMonster::~PBossMonster()
{
}

bool PBossMonster::Init()
{
	action_list_.insert((std::make_pair(FSM_State::IDLE, new PBossMobIdleAction(this))));
	action_list_.insert((std::make_pair(FSM_State::HIT, new PBossMobHitAction(this))));

	current_boss_monster_action_ = action_list_[FSM_State::IDLE];
	current_boss_monster_state_ = FSM_State::IDLE;

	//boss_monster_fsm_.Add(FSM_State::IDLE, FSM_Event::HIT, FSM_State::HIT);


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

	PSpriteManager::GetInstance().LoadSpriteDataFromScript(info.sprite_path, ObjectLoadType::CHARACTER);
	sprite_.Clone(PSpriteManager::GetInstance().get_sprite_from_map_ex(info.sprite_name), alpha_, scale_);

	sprite_.SetPosition(position_.x, position_.y);

	FLOAT_RECT scaled_collisionbox_norm = { collision_box_norm_.left * scale_, collision_box_norm_.top * scale_ ,
	collision_box_norm_.right * scale_, collision_box_norm_.bottom * scale_ };

	collision_box_norm_ = scaled_collisionbox_norm;
	set_collision_box_(collision_box_norm_);

	spawn_position_ = position;

}

void PBossMonster::ProcessAction()
{
	current_boss_monster_action_->Process();
}

bool PBossMonster::Frame()
{
	sprite_.Frame();
	ProcessAction();
	set_collision_box_(collision_box_norm_);

	return false;
}

bool PBossMonster::Render()
{
	Spawn();
	return false;
}

bool PBossMonster::Release()
{
	sprite_.Release();
	return false;
}
