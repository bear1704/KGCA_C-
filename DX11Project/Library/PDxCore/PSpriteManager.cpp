#include "PSpriteManager.h"


PSpriteManager::~PSpriteManager()
{
}

PSpriteManager::PSpriteManager() : kDamageFontLifetime(1.2f), kDamageFontGap(35.0f)
{
	dmg_font_index_ = 0;
}

bool PSpriteManager::Init()
{
	need_load_character_sprite_data_ = true;
	need_load_UI_sprite_data_ = true;
	need_load_map_sprite_data_ = true;
	return true;
}

bool PSpriteManager::Frame()
{
	for (PSprite& sprite : render_wait_list_)
	{
		if (sprite.get_is_dmg())
		{
			pPoint pos = sprite.get_position_();
			sprite.SetPosition(pos.x, pos.y - 0.5f);
		}

		sprite.Frame();
	}

	return false;
}

bool PSpriteManager::Render()
{
	//for (PSprite& sprite : render_wait_list_)
	//{
	//	sprite.Render();
	//}

	return false;
}

bool PSpriteManager::Release()
{
	for (auto iter = render_wait_list_.begin(); iter != render_wait_list_.end(); )
	{
		PSprite& sprite = *iter;
		if (sprite.get_is_dead_())
		{
			sprite.Release();
			iter = render_wait_list_.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	
	return false;
}

//SpriteDataInfo * PSpriteManager::get_sprite_data_list_from_map(std::wstring key)
//{
//
//	auto iter = sprite_data_list_.find(key);
//	if (iter != sprite_data_list_.end())
//	{
//		SpriteDataInfo* data =  (*iter).second;
//		return data;
//	}
//	return nullptr;
//}

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

PSprite* PSpriteManager::get_sprite_from_dmgfont_list(std::wstring key)
{
	auto iter = damage_font_list_.find(key);
	if (iter != damage_font_list_.end())
	{
		PSprite* data = (*iter).second;
		return data;
	}
	return nullptr;
}


void PSpriteManager::LoadSpriteDataFromScript(multibyte_string filepath, ObjectLoadType type)
{

	if (!need_load_character_sprite_data_ && type == ObjectLoadType::CHARACTER)
		return;
	if (!need_load_UI_sprite_data_ && type == ObjectLoadType::UI)
		return;
	if (!need_load_map_sprite_data_ && type == ObjectLoadType::MAP)
		return;

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
			std::vector<DX::PTex_uv4> rt;
			while (true)
			{
				iter++;
				if (iter->first.compare("name") == 0)
					sprite_name.assign(iter->second.begin(), iter->second.end());
				else if (iter->first.compare("max_frame") == 0)
					info.max_frame = std::atoi(iter->second.c_str());
				else if (iter->first.compare("lifetime") == 0)
					info.lifetime = std::atof(iter->second.c_str());
				else if (iter->first.compare("once_playtime") == 0)
					info.once_playtime = std::atof(iter->second.c_str());
				else if (iter->first.compare("tex_name") == 0)
					info.texture_name.assign(iter->second.begin(), iter->second.end());
				else if (iter->first.compare("uv1") == 0)
				{
					DX::PTex_uv4 uv;
					
					for (int i = 0; i < kPlaneTextureUvMax; i++)
					{
						std::vector<string> uv_vec = parser.SplitString(iter->second, ',');
						uv.u[i] = std::atof(uv_vec[0].c_str());
						uv.v[i] = std::atof(uv_vec[1].c_str());
						iter++;
					}
					iter--;// 마지막 한칸 되돌리기(위에서 한번더 iter++를 하므로)
					rt.push_back(uv);
				}
				else if (iter->first.compare("END") == 0)
					break;
			}

			info.tex_boundary_list = std::move(rt); //오류 예감

			PSprite* sprite = new PSprite();
			sprite->Set(info, 1.0, 1.0);
			sprite_list_.insert(std::make_pair(sprite_name, sprite));

		}
		else if (iter->second.compare("dmg_sprite") == 0)
		{
			SpriteDataInfo info;
			std::wstring sprite_name;
			std::vector<DX::PTex_uv4> rt;


			info.lifetime = kDamageFontLifetime;
			info.once_playtime = kDamageFontLifetime;

			while (true)
			{
				iter++;
				if (iter->first.compare("name") == 0)
					sprite_name.assign(iter->second.begin(), iter->second.end());
				else if (iter->first.compare("max_frame") == 0)
					info.max_frame = std::atoi(iter->second.c_str());					
				else if (iter->first.compare("tex_name") == 0)
					info.texture_name.assign(iter->second.begin(), iter->second.end());
				else if (iter->first.compare("uv1") == 0)
				{
					DX::PTex_uv4 uv;

					for (int i = 0; i < 4; i++)
					{
						std::vector<string> uv_vec = parser.SplitString(iter->second, ',');
						uv.u[i] = std::atof(uv_vec[i].c_str());
						uv.v[i] = std::atof(uv_vec[i].c_str());
						iter++;
					}
					iter--;// 마지막 한칸 되돌리기(위에서 한번더 iter++를 하므로)
					rt.push_back(uv);
				}
				else if (iter->first.compare("END") == 0)
					break;
			}
			info.tex_boundary_list = std::move(rt); //오류 예감

			PSprite* sprite = new PSprite();
			sprite->Set(info, 1.0, 1.0);
			damage_font_list_.insert(std::make_pair(sprite_name, sprite));

		}
		
	}
	if (need_load_character_sprite_data_ && type == ObjectLoadType::CHARACTER)
		need_load_character_sprite_data_ = false;
	if (need_load_UI_sprite_data_ && type == ObjectLoadType::UI)
		need_load_UI_sprite_data_ = false;
	if (need_load_map_sprite_data_ && type == ObjectLoadType::MAP)
		need_load_map_sprite_data_ = false;
}

bool PSpriteManager::Delete(int key)
{
	return false;
}

void PSpriteManager::AddRenderWaitList(PSprite sprite)
{
	render_wait_list_.push_back(sprite);
}

void PSpriteManager::CreateDamageFontFromInteger(int damage, pPoint firstPos)
{
	std::string damage_str = std::to_string(damage);
	
	float gap = 0; 

	for (int i = 0; i < damage_str.size(); i++)
	{
		std::wstring nthstr(1, damage_str[i]);
		PSprite* sprite = get_sprite_from_dmgfont_list(nthstr);
		
		PSprite clone_sprite;
		clone_sprite.Clone(sprite, 1.0f, 1.5f);
		clone_sprite.SetPosition(firstPos.x + gap, firstPos.y);
		clone_sprite.set_is_dmg(true);
		gap += kDamageFontGap;
		AddRenderWaitList(clone_sprite);
	}


}

