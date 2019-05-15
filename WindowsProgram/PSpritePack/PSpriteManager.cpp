#include "PSpriteManager.h"



PSpriteManager::PSpriteManager()
{
}


PSpriteManager::~PSpriteManager()
{
}

bool PSpriteManager::Init()
{
	return false;
}

bool PSpriteManager::Frame()
{
	return false;
}

bool PSpriteManager::Render()
{
	return false;
}

bool PSpriteManager::Release()
{
	return false;
}

PSprite * PSpriteManager::get_sprite_from_map(int key)
{

	auto iter = sprite_list_.find(key);
	if (iter != sprite_list_.end())
	{
		PSprite* sprite_data = (*iter).second;
		return sprite_data;
	}
	return nullptr;
}

void PSpriteManager::LoadRectData(multibyte_string filepath)
{
	FILE* fp = nullptr;

	_wfopen_s(&fp, filepath.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR buffer[256] = { 0, };
	TCHAR temp_buffer[256] = { 0, };
	int number_of_sprites = -1;

	_fgetts(buffer, _countof(buffer), fp); //한줄 받아오기(스프라이트, 스프라이트 객체 개수)
	_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_sprites);
	
	//sprite_instance.sprite_rectlist_.resize(num) //map이므로 리사이즈 불필요
	int number_of_max_frames;
	for (int sprite = 0; sprite < number_of_sprites; sprite++)
	{
		PSprite* sprite_instance = new PSprite(); //rect_list에 대한 소유권은 sprite 객체에 있다!

		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_max_frames);

		sprite_instance->sprite_rectlist_.resize(number_of_max_frames);
		
		int iCount = -1;
		for (int i = 0; i < number_of_max_frames; i++)
		{
			
			_fgetts(buffer, _countof(buffer), fp);
			_stscanf_s(buffer, _T("%d%d%d%d%d"), &iCount, &sprite_instance->sprite_rectlist_[i].left,
				&sprite_instance->sprite_rectlist_[i].top,
				&sprite_instance->sprite_rectlist_[i].right,
				&sprite_instance->sprite_rectlist_[i].bottom);
		}
		sprite_list_.insert(std::make_pair(index_++, sprite_instance));
	}
	fclose(fp);

}
