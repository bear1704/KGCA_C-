#include "PMeteor.h"


PMeteor::PMeteor(int initypos, int randdownspeed)
{
	rand_init_ypos_ = initypos;
	rand_downspeed_ = randdownspeed;
}

PMeteor::~PMeteor()
{
}

void PMeteor::Init()
{
	PSpriteManager::GetInstance().LoadSpriteDataFromScript(L"data/character/sprite/character_coord.txt", ObjectLoadType::CHARACTER);
	PSprite* sprite = PSpriteManager::GetInstance().get_sprite_from_map_ex(L"meteor");

	std::random_device r;
	std::mt19937 engine(r());
	std::uniform_int_distribution<int> distribution(100, 300);
	auto generator = std::bind(distribution, engine);

	
	for (int i = 0; i < 8; i++)
	{
		FLOAT_RECT rect = { 0,-1000, 50,123 };
		pPoint pos = pPoint(23 + 150 * i, -500);
		Stone st;
		st.position_ = pos;
		st.stone_sprite_.Clone(sprite, 1.0f, 1.0f);
		st.drop_speed_ = generator();
		stone_list_.push_back(st);
	}
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
	}
}

void PMeteor::Release()
{
	for (int i = 0; i < stone_list_.size(); i++)
	{
		stone_list_[i].stone_sprite_.Release();
	}
}

void PMeteor::Start()
{




}

Stone::Stone()
{
}

Stone::~Stone()
{
}
