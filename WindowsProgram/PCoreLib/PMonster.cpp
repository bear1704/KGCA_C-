#include "PMonster.h"



PMonster::PMonster(pPoint point, multibyte_string monster_name)
{
	position_ = point;
	monster_name_ = monster_name;
}


PMonster::~PMonster()
{
}

bool PMonster::Init()
{
	PCharacterDataManager::GetInstance().LoadDataFromScript(L"data/character/character_data.txt");
	CharacterStatus* status = PCharacterDataManager::GetInstance().get_character_status_list_from_map(monster_name_);
	Set(pPoint(position_.x, position_.y), status->collision_box, status->move_speed);//위치값은 이미 생성자에서 초기화
	scale_ = 1.0f;

	PSpriteManager::GetInstance().LoadDataFromScript(L"data/character/sprite/character_coord.txt");
	sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(monster_name_), 1.0f, scale_);
	sprite_.SetPosition(position_.x, position_.y);

	return false;
}

bool PMonster::Frame()
{
	sprite_.Frame();
	set_collision_box_(collision_box_norm_);
	return false;
}

bool PMonster::Render()
{
	sprite_.Draw();
	return false;
}

bool PMonster::Release()
{
	sprite_.Release();
	return false;
}
