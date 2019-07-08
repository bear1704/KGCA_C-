#include "PSpriteManager.h"




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

PSprite* PSpriteManager::get_sprite_from_map_ex(std::wstring key)
{
	auto iter = sprite_list_.find(key);
	if (iter != sprite_list_.end())
	{
		PSprite* data = (*iter).second;
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
		vector<FLOAT_RECT> load_rect_list;
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
			FLOAT_RECT rt;
			
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

void PSpriteManager::LoadSpriteDataFromScript(multibyte_string filepath)
{
	PParser parser;
	std::vector<std::pair<string, string>> ret_parse;
	std::string str;
	str.assign(filepath.begin(), filepath.end());
	parser.XmlParse(str, &ret_parse);

	for (auto iter = ret_parse.begin() ; iter != ret_parse.end() ; iter++)
	{
		
		if (iter->second.compare("sprite") == 0)
		{
			SpriteDataInfo info;
			std::wstring sprite_name;

			while (true)
			{
				iter++;
				if (iter->first.compare("name") == 0)
					sprite_name.assign(iter->second.begin(), iter->second.end());
				else if (iter->first.compare("max_frame") == 0)
					info.max_frame = std::atoi(iter->second.c_str());
				else if (iter->first.compare("lifetime") == 0)
					info.lifetime = std::atoi(iter->second.c_str());
				else if (iter->first.compare("once_playtime") == 0)
					info.lifetime = std::atoi(iter->second.c_str());
				else if (iter->first.compare("path") == 0)
					info.bitmap_path.assign(iter->second.begin(), iter->second.end());
				else if (iter->first.compare("coord") == 0)
				{
					FLOAT_RECT rt;
					std::vector<string> coord_vec = parser.SplitString(iter->second, ',');
					rt.left = std::atof(coord_vec[0].c_str());
					rt.top = std::atof(coord_vec[0].c_str());
					rt.right = std::atof(coord_vec[0].c_str());
					rt.bottom = std::atof(coord_vec[0].c_str());
					info.rect_list.push_back(rt);
				}
				else if (iter->first.compare("END") == 0)
					break;
			}

			PSprite* sprite = new PSprite();
			sprite->Set(info, 1.0, 1.0);
			sprite_list_.insert(std::make_pair(sprite_name, sprite));

		}
		
	}

}

bool PSpriteManager::Delete(int key)
{
	return false;
}
