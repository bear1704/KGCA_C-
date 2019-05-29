#include "PCharacter.h"



PCharacter::PCharacter()
{

}

PCharacter::PCharacter(float x, float y, multibyte_string character_name)
{
	position_.x = x;
	position_.y = y;
	character_name_ = character_name;
}

PCharacter::~PCharacter()
{
}

bool PCharacter::Init()
{

	PCharacterDataManager::GetInstance().LoadDataFromScript(L"data/character/character_data.txt");
	CharacterStatus* status = PCharacterDataManager::GetInstance().get_character_status_list_from_map(L"player");
	Set(pPoint(position_.x, position_.y), status->collision_box, status->move_speed);//위치값은 이미 생성자에서 초기화
	scale_ = 1.0f;

	PSpriteManager::GetInstance().LoadDataFromScript(L"data/character/sprite/character_coord.txt");

	sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"playerCharacter"), 1.0f, scale_);
	sprite_.SetPosition(position_.x, position_.y);


	return true;
}

bool PCharacter::Frame()
{
	sprite_.Frame();
	set_collision_box_(collision_box_norm_);
	Movement();


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

	sprite_.SetPosition(position_.x, position_.y);
}

