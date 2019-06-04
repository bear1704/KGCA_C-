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

SpriteDataInfo * PSpriteManager::get_sprite_data_list_from_map(std::wstring key)
{

	auto iter = sprite_data_list_.find(key);
	if (iter != sprite_data_list_.end())
	{
		SpriteDataInfo* data =  (*iter).second;
		return data;
	}
	return nullptr;
}

void PSpriteManager::LoadDataFromScript(multibyte_string filepath)
{
	FILE* fp = nullptr;

	_wfopen_s(&fp, filepath.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR buffer[256] = { 0, };
	TCHAR temp_buffer[256] = { 0, };
	TCHAR temp_name_buffer[256] = { 0, };
	int number_of_sprites = -1;

	_fgetts(buffer, _countof(buffer), fp); //한줄 받아오기(스프라이트, 스프라이트 객체 개수)
	_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_sprites);
	
	//sprite_instance.rect_list.resize(num) //map이므로 리사이즈 불필요
	int number_of_max_frames;
	for (int sprite = 0; sprite < number_of_sprites; sprite++)
	{
		//PSprite* sprite_instance = new PSprite(); //rect_list에 대한 소유권은 sprite 객체에 있다!
		vector<DOUBLE_RECT> load_rect_list;
		SpriteDataInfo* sprite_data_info = new SpriteDataInfo();

		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%d%f%f%s"), temp_buffer, _countof(temp_buffer), 
			&number_of_max_frames, &sprite_data_info->lifetime, &sprite_data_info->once_playtime,
			temp_name_buffer, _countof(temp_buffer));
		
		sprite_data_info->max_frame = number_of_max_frames;
		sprite_data_info->bitmap_path = temp_name_buffer;

		std::wstring rect_name(temp_buffer);
		load_rect_list.reserve(number_of_max_frames);

		int iCount = -1;
		for (int i = 0; i < number_of_max_frames; i++)
		{
			DOUBLE_RECT rt;
			
			_fgetts(buffer, _countof(buffer), fp);
			_stscanf_s(buffer, _T("%d%f%f%f%f"), &iCount,&rt.left,
				&rt.top,
				&rt.right,
				&rt.bottom);
			
			load_rect_list.push_back(rt);
		}
		sprite_data_info->rect_list = load_rect_list;
		sprite_data_list_.insert(std::make_pair(rect_name , sprite_data_info));
	}
	fclose(fp);

}

bool PSpriteManager::Delete(int key)
{
	return false;
}
