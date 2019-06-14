#include "PPlayerCharacter.h"



PPlayerCharacter::PPlayerCharacter()
{
}


PPlayerCharacter::~PPlayerCharacter()
{
	
}

bool PPlayerCharacter::Init()
{
	status.Init();
	return true;
}

bool PPlayerCharacter::Frame()
{
	SavePrevPosition();
	sprite_.Frame();
	set_collision_box_(collision_box_norm_);
	Movement();
	physics_.Gravity(position_, gravity_);
	physics_.Jump(physics_.jump_init_time, position_, 600, 0.2f);
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

	float cam_speed = P2DCamera::GetInstance().get_camera_scroll_speed_();

	if (g_InputActionMap.upArrowKey == KEYSTAT::KEY_PUSH)
	{
		//	P2DCamera::GetInstance().add_camera_position_(pPoint(0, -cam_speed));
		
	}
	if (g_InputActionMap.downArrowKey == KEYSTAT::KEY_PUSH)
	{
		//P2DCamera::GetInstance().add_camera_position_(pPoint(0, cam_speed));
		//position_.y += move_speed_ * g_SecondPerFrame;
	}
	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_PUSH)
	{
		position_.x -= move_speed_ * g_SecondPerFrame;
		is_reversal_ = false;
		sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"pc_move"), alpha_, scale_);
		sprite_.SetPosition(position_.x, position_.y);
	}
	if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_PUSH)
	{
		position_.x += move_speed_ * g_SecondPerFrame;
		is_reversal_ = true;
		sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"pc_move"), alpha_, scale_);
		sprite_.SetPosition(position_.x, position_.y);
	}
	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.x -= move_speed_ * g_SecondPerFrame;
		sprite_.SetPosition(position_.x, position_.y);
	}
	if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.x += move_speed_ * g_SecondPerFrame;
		sprite_.SetPosition(position_.x, position_.y);
	}
	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_UP)
	{
		sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"pc_idle"), alpha_, scale_);
		sprite_.SetPosition(position_.x, position_.y);
	}
	if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_UP)
	{
		sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"pc_idle"), alpha_, scale_);
		sprite_.SetPosition(position_.x, position_.y);
	}

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

	sprite_.SetPosition(position_.x, position_.y);
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

	P2DCamera::GetInstance().set_character_collision_rect(&collision_box_); //Ä³¸¯ÅÍ only
}

PPlayerStatus& PPlayerCharacter::get_status()
{
	return status;
}

void PPlayerCharacter::StatusSet(multibyte_string status_path, multibyte_string object_name)
{
	status.StatusSet(status_path,object_name);
}
