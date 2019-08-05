#include "PObjectDataManager.h"





PObjectDataManager::~PObjectDataManager()
{
}

bool PObjectDataManager::Init()
{
	need_load_data_ = true;
	return true;
}

bool PObjectDataManager::Frame()
{
	return false;
}

bool PObjectDataManager::Render()
{
	return false;
}

bool PObjectDataManager::Release()
{
	return false;
}

std::vector<PRectObject*> PObjectDataManager::get_object_list_from_map(std::wstring key)
{
	auto iter = object_composition_list_.find(key);
	if (iter != object_composition_list_.end())
	{
		std::vector<PRectObject*>& data = (*iter).second;
		return data;
	}

	
}




void PObjectDataManager::LoadDataFromScript(multibyte_string filepath)
{
	//#CHARLIST 리스트갯수
	//리스트이름 요소갯수
	//객체이름 절대포지션x 절대포지션y 객체타입(몬스터, NPC, 캐릭터, MAP)

	if (!need_load_data_)
		return;

	const std::wstring path = L"data/character/character_data.txt";
	const std::wstring map_path = L"data/map/map_data.txt";
	const std::wstring status_path = L"data/character/character_status_data.txt";
	const std::wstring animation_path = L"data/character/sprite/animation_list.txt";



	pPoint map_pos = pPoint(P2DCamera::GetInstance().get_world_size_().x / 2, P2DCamera::GetInstance().get_world_size_().y / 2);


	std::vector<std::pair<std::string, std::string>> ret_parse;  //데이터 컴포지션
	std::string str;
	str.assign(filepath.begin(), filepath.end());
	PParser parser;
	parser.XmlParse(str, &ret_parse);
	
	std::vector<PRectObject*> object_list;

	for (auto iter = ret_parse.begin(); iter != ret_parse.end(); iter++)
	{


		if (iter->second.compare("CHARLIST") == 0)
		{
			std::string composition_name;
			std::string object_name;
			std::string object_type; 

			while (true)
			{
				PRectObject* component;
				iter++;
				if (iter->first.compare("END") == 0)
					break;
				else if (iter->first.compare("name") == 0)
					composition_name.assign(iter->second.begin(), iter->second.end());
				else if (iter->first.compare("MONSTER") == 0)
				{
					object_name = iter->second;
					iter++; //COORD 확인용

					std::vector<string> pos_vec = parser.SplitString(iter->second, ',');
					pPoint pos = { std::stof(pos_vec[0].c_str()), std::stof(pos_vec[1].c_str()) };

					component = (PMonster*) new PMonster();
					component->Set(path, string_to_multibyte(object_name), pPoint( pos.x, pos.y));
					component->set_gravity_(450.0f);
					component->set_type_(Type::MONSTER);
					object_list.push_back(component);
				}
				else if (iter->first.compare("MAP") == 0)
				{
					object_name = iter->second;
					iter++; //COORD 확인용

					component =  new PRectObject();
					component->Set(map_path, string_to_multibyte(object_name), pPoint(map_pos.x, map_pos.y));
					component->set_type_(Type::MAP);
					object_list.insert(object_list.begin(), component); //map은 가장 먼저 렌더되도록 제일 앞에 위치.
				}
				else if (iter->first.compare("PLAYER") == 0)
				{
					object_name = iter->second;
					iter++; //COORD 확인용

					std::vector<string> pos_vec = parser.SplitString(iter->second, ',');
					pPoint pos = { std::stof(pos_vec[0].c_str()), std::stof(pos_vec[1].c_str()) };

					component = (PPlayerCharacter*) new PPlayerCharacter();
					component->Set(path, string_to_multibyte(object_name), pPoint(pos.x, pos.y));
					component->set_gravity_(450.0f);
					component->set_type_(Type::PLAYER);
					object_list.push_back(component);
				}
				else if (iter->first.compare("OTHER_PLAYER") == 0)
				{
					object_name = iter->second;
					iter++; //COORD 확인용

					std::vector<string> pos_vec = parser.SplitString(iter->second, ',');
					pPoint pos = { std::stof(pos_vec[0].c_str()), std::stof(pos_vec[1].c_str()) };

					component = (PPlayerCharacter*) new PPlayerCharacter();
					component->Set(path, string_to_multibyte(object_name), pPoint(pos.x, pos.y));
					component->set_gravity_(450.0f);
					component->set_type_(Type::OTHER_PLAYER);
					object_list.push_back(component);
				}
				else if (iter->first.compare("BOSSMONSTER") == 0)
				{
					object_name = iter->second;
					iter++; //COORD 확인용

					std::vector<string> pos_vec = parser.SplitString(iter->second, ',');
					pPoint pos = { std::stof(pos_vec[0].c_str()), std::stof(pos_vec[1].c_str()) };

					component = (PBossMonster*) new PBossMonster();
					component->Set(path, string_to_multibyte(object_name), pPoint(pos.x, pos.y));
					component->set_type_(Type::BOSS_MONSTER);
					component->StatusSet(status_path, component->get_object_name());

					object_list.push_back(component);
				}
				else if (iter->first.compare("BOSSMONSTER_SERV") == 0)
				{

					const std::wstring path = L"data/character_data.txt";
					const std::wstring status_path = L"data/character_status_data.txt";

					object_name = iter->second;
					iter++; //COORD 확인용

					std::vector<string> pos_vec = parser.SplitString(iter->second, ',');
					pPoint pos = { std::stof(pos_vec[0].c_str()), std::stof(pos_vec[1].c_str()) };

					PBossMonster* component = new PBossMonster();
					component->SetForServer(path, string_to_multibyte(object_name), pPoint(pos.x, pos.y));
					component->set_type_(Type::BOSS_MONSTER);
					component->StatusSetForServer(status_path, component->get_object_name());
					
					component->set_id(20000); //hard_coded


					PRectObject* rect_component = component;



					object_list.insert(object_list.begin(), rect_component); //맵 다음으로 보여지도록
				}
			}

			object_composition_list_.insert(std::make_pair(multibyte_to_unicode_str(composition_name), object_list));
		}


	}

	if(need_load_data_)
		need_load_data_ = false;

}

