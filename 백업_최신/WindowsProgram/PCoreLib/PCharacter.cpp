#include "PCharacter.h"



PCharacter::PCharacter()
{

}

PCharacter::PCharacter(float x, float y, multibyte_string character_name)
{

}

PCharacter::~PCharacter()
{
}

bool PCharacter::Init()
{


	return true;
}

bool PCharacter::Frame()
{
	sprite_.Frame();
	set_collision_box_(collision_box_norm_);
	Movement();
	physics_.Gravity(position_, gravity_);
	physics_.Jump(physics_.jump_init_time, position_, 600, 0.2f);


	return true;
}

bool PCharacter::Render()
{
	Spawn();
	return true;
}

bool PCharacter::Release()
{
	sprite_.Release();
	return true;
}

void PCharacter::Movement()
{

	float cam_speed = P2DCamera::GetInstance().get_camera_scroll_speed_();

	if (g_InputActionMap.upArrowKey == KEYSTAT::KEY_HOLD)
	{
	//	P2DCamera::GetInstance().add_camera_position_(pPoint(0, -cam_speed));
	}
	if (g_InputActionMap.downArrowKey == KEYSTAT::KEY_HOLD)
	{
		//P2DCamera::GetInstance().add_camera_position_(pPoint(0, cam_speed));
		position_.y += move_speed_ * g_SecondPerFrame;

	}if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.x -= move_speed_ * g_SecondPerFrame;
		//P2DCamera::GetInstance().add_camera_position_(pPoint(-cam_speed, 0));
	}
	if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.x += move_speed_ * g_SecondPerFrame;
		//P2DCamera::GetInstance().add_camera_position_(pPoint(cam_speed , 0));
	}
	if (g_InputActionMap.jumpKey == KEYSTAT::KEY_PUSH)
	{
		physics_.StartJump();
	}


	float aaaa = g_fGameTimer;
	





	sprite_.SetPosition(position_.x, position_.y);
}

void PCharacter::Set(multibyte_string data_path, multibyte_string object_name, pPoint position)
{
	PObjectDataManager::GetInstance().LoadDataFromScript(data_path);
	ObjectInfo info = *(PObjectDataManager::GetInstance().get_object_info_list_from_map(object_name));

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
	P2DCamera::GetInstance().set_character_collision_rect(&collision_box_); //Ä³¸¯ÅÍ only
}

void PCharacter::SetGravity(float gravity)
{
	gravity_ = gravity;
}

