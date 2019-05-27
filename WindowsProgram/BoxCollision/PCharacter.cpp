#include "PCharacter.h"



PCharacter::PCharacter()
{

}

PCharacter::PCharacter(float x, float y)
{
	position_.x = x;
	position_.y = y;
}

PCharacter::~PCharacter()
{
}

bool PCharacter::Init()
{
	PCharacterDataManager::GetInstance().LoadDataFromScript(L"data/character/character_data.txt");
	CharacterStatus* status = PCharacterDataManager::GetInstance().get_character_status_list_from_map(L"player");
	move_speed_ = status->move_speed;
	collision_box_ = status->collision_box;
	scale_ = 1.0f;

	PSpriteManager::GetInstance().LoadDataFromScript(L"data/character/sprite/character_coord.txt");
	sprite_character_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"playerCharacter"), 1.0f, scale_);
	sprite_character_.SetPosition(position_.x, position_.y);


	return true;
}

bool PCharacter::Frame()
{


	sprite_character_.Frame();
	sprite_character_.SetPosition(position_.x, position_.y);
	Movement();
	return true;
}

bool PCharacter::Render()
{
	sprite_character_.Draw();
	return true;
}

bool PCharacter::Release()
{
	sprite_character_.Release();
	return true;
}

void PCharacter::Movement()
{
	if (g_InputActionMap.upArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.y -= g_SecondPerFrame * move_speed_;
	}
	if (g_InputActionMap.downArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.y += g_SecondPerFrame * move_speed_;

	}if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.x -= g_SecondPerFrame *  move_speed_;
	}
	if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
	{
		position_.x += g_SecondPerFrame *  move_speed_;
	}
}

float PCharacter::get_scale_()
{
	return scale_;
}
