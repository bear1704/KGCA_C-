#include "PMonster.h"



PMonster::PMonster()
{

}


PMonster::~PMonster()
{
}

bool PMonster::Init()
{

	return false;
}

bool PMonster::Frame()
{
	SavePrevPosition();
	sprite_.Frame();
	set_collision_box_(collision_box_norm_);
	Movement();
	physics_.Gravity(position_, gravity_);
	PlatformWallCollision();
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
	//몬스터는 카메라를 붙이지 않음.
}

void PMonster::Movement()
{
	sprite_.SetPosition(position_.x, position_.y);
}
