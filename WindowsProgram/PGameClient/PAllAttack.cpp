#include "PAllAttack.h"

PAllAttack::PAllAttack()
{
	spawn_position_vec_.push_back(pPoint(188, 290));
	spawn_position_vec_.push_back(pPoint(370, 397));
	spawn_position_vec_.push_back(pPoint(440, 506));
	spawn_position_vec_.push_back(pPoint(309, 600));
	spawn_position_vec_.push_back(pPoint(990, 594));
	spawn_position_vec_.push_back(pPoint(1040, 476));
	barrier_area_ = { 0, 0, 150, 100 };



}

PAllAttack::~PAllAttack()
{
}

void PAllAttack::Init()
{


}

void PAllAttack::Frame()
{


}

void PAllAttack::Render()
{
	goddess_.Render();
}

void PAllAttack::Release()
{
	goddess_.Release();
}

void PAllAttack::Start(int randnum)
{
	PSpriteManager::GetInstance().LoadSpriteDataFromScript(L"data/character/sprite/character_coord.txt", ObjectLoadType::CHARACTER);
	PSprite* gd = PSpriteManager::GetInstance().get_sprite_from_map_ex(L"SL");
	goddess_.Clone(gd, 1.0f, 1.0f);
	pPoint pos = spawn_position_vec_[randnum];
	goddess_.SetPosition(pos.x, pos.y);
	barrier_area_.left = pos.x - barrier_area_.right / 2;
	barrier_area_.top = pos.y - barrier_area_.bottom/ 2;

	UserListForStorage uls;
	WORD cid = PUserManager::GetInstance().oneself_user_.get_character_id();
	uls.cid = cid;
	uls.safe_zone = barrier_area_;

	PNetworkDataStorage::GetInstance().AddData(uls);
}
