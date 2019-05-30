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
	sprite_.Draw();
	return true;
}

bool PCharacter::Release()
{
	sprite_.Release();
	return true;
}

void PCharacter::Movement()
{

	if (g_InputActionMap.upArrowKey == KEYSTAT::KEY_HOLD)
	{
		//Æ÷Å» Å°
	}
	if (g_InputActionMap.downArrowKey == KEYSTAT::KEY_PUSH)
	{


	}if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.x -= move_speed_ * g_SecondPerFrame;
	}
	if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.x += move_speed_ * g_SecondPerFrame;
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

}

void PCharacter::SetGravity(float gravity)
{
	gravity_ = gravity;
}

