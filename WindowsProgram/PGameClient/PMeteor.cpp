#include "PMeteor.h"


PMeteor::PMeteor(int initypos, int randdownspeed)
{
	rand_init_ypos_ = initypos;
	rand_downspeed_ = randdownspeed;
}

PMeteor::PMeteor()
{
}

PMeteor::~PMeteor()
{
}

void PMeteor::Init()
{
	
}

void PMeteor::Frame()
{
	for (int i = 0; i < stone_list_.size(); i++)
	{
		stone_list_[i].stone_sprite_.Frame();
		stone_list_[i].position_.y = stone_list_[i].position_.y + stone_list_[i].drop_speed_ * g_SecondPerFrame;
		stone_list_[i].stone_sprite_.SetPosition(stone_list_[i].position_.x, stone_list_[i].position_.y);
		stone_list_[i].stone_rect_.left = stone_list_[i].position_.x;
		stone_list_[i].stone_rect_.top = stone_list_[i].position_.y;
		PNetworkDataStorage::GetInstance().AddData(stone_list_[i].stone_rect_);
	}


}

void PMeteor::Render()
{
	for (int i = 0; i < stone_list_.size(); i++)
	{
		stone_list_[i].stone_sprite_.Render();
		FLOAT_RECT arect = P2DCamera::GetInstance().WorldToGamescreenRECT(stone_list_[i].stone_rect_);
		int prevMode2 = Rectangle(g_handle_off_screenDC, arect.left, arect.top,
			arect.left + arect.right, arect.top + arect.bottom);
		SetROP2(g_handle_off_screenDC, prevMode2);
	}

}

void PMeteor::Release()
{
	for (int i = 0; i < stone_list_.size(); i++)
	{
		stone_list_[i].stone_sprite_.Release();
	}

	//스킬은 재사용해야 하므로..
}

void PMeteor::Start(std::vector<int> initpos, std::vector<int> initspeed)
{

	PSpriteManager::GetInstance().LoadSpriteDataFromScript(L"data/character/sprite/character_coord.txt", ObjectLoadType::CHARACTER);
	PSprite* sprite = PSpriteManager::GetInstance().get_sprite_from_map_ex(L"meteor");




	for (int i = 0; i < 8; i++)
	{
		FLOAT_RECT rect = { 0,0, 50,123 };
		pPoint pos = pPoint(23 + 150 * i, initpos[i]);
		Stone st;
		st.position_ = pos;
		st.stone_sprite_.Clone(sprite, 1.0f, 1.0f);
		st.drop_speed_ = initspeed[i];
		stone_list_.push_back(st);
	}


}

Stone::Stone()
{
}

Stone::~Stone()
{
}
