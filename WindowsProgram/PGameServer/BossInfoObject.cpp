#include "BossInfoObject.h"

BossInfoObject::BossInfoObject(pPoint position)
{
	position_ = position;
}

BossInfoObject::~BossInfoObject()
{
}

void BossInfoObject::Set()
{
	boss_name_ = L"zakum";
	PObjectInfoManager::GetInstance().LoadDataFromScript(path, ObjectLoadType::CHARACTER);
	ObjectInfo info = *(PObjectInfoManager::GetInstance().get_object_info_list_from_map(boss_name_));
	collision_box_norm_ = info.collision_box_;
	scale_ = info.scale_;
	alpha_ = info.alpha_;

	FLOAT_RECT scaled_collisionbox_norm = { collision_box_norm_.left * scale_, collision_box_norm_.top * scale_ ,
	collision_box_norm_.right * scale_, collision_box_norm_.bottom * scale_ };

	collision_box_norm_ = scaled_collisionbox_norm;
	
	float half_width = collision_box_norm_.right / 2;
	float half_height = collision_box_norm_.bottom / 2;

	collision_box_.left = position_.x - half_width;
	collision_box_.top = position_.y - half_height;
	collision_box_.right = collision_box_norm_.right;
	collision_box_.bottom = collision_box_norm_.bottom;

	status_.StatusSet(status_path, boss_name_);

	id_ = ZAKUM_ID;

	current_state_ = FSM_State::IDLE;

}
