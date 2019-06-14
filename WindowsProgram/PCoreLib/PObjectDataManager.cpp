#include "PObjectDataManager.h"



PObjectDataManager::PObjectDataManager()
{
}


PObjectDataManager::~PObjectDataManager()
{
}

bool PObjectDataManager::Init()
{
	return false;
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

std::vector<PSprite*> PObjectDataManager::get_animation_list_from_map(std::wstring key)
{
	auto iter = object_animation_list_.find(key);
	if (iter != object_animation_list_.end())
	{
		std::vector<PSprite*>& data = (*iter).second;
		return data;
	}
}

void PObjectDataManager::LoadDataFromScript(multibyte_string filepath)
{
	//#CHARLIST 리스트갯수
	//리스트이름 요소갯수
	//객체이름 절대포지션x 절대포지션y 객체타입(몬스터, NPC, 캐릭터, MAP)
	
	const std::wstring path = L"data/character/character_data.txt";
	const std::wstring map_path = L"data/map/map_data.txt";
	const std::wstring status_path = L"data/character/character_status_data.txt";
	const std::wstring animation_path = L"data/character/sprite/animation_list.txt";



	pPoint map_pos = pPoint(P2DCamera::GetInstance().get_world_size_().x / 2, P2DCamera::GetInstance().get_world_size_().y / 2);
	
	FILE* fp = nullptr;

	_wfopen_s(&fp, filepath.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR buffer[256] = { 0, };
	TCHAR temp_buffer[256] = { 0, };
	TCHAR type_buffer[25] = { 0, };

	int number_of_data = -1;

	_fgetts(buffer, _countof(buffer), fp); //한줄 받아오기(캐릭터 데이터 갯수)
	_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_data);

	for (int index_data = 0; index_data < number_of_data; index_data++)
	{
		int numberof_objectlist;
		pPoint composition_pos;
		std::vector<PRectObject*> object_list;

		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer),
			&numberof_objectlist);

		std::wstring object_composition_name(temp_buffer);

		for (int i = 0; i < numberof_objectlist; i++)
		{
			pPoint absolute_pos;
		
			_fgetts(buffer, _countof(buffer), fp);
			_stscanf_s(buffer, _T("%s%f%f%s"), temp_buffer, _countof(temp_buffer),
				&absolute_pos.x, &absolute_pos.y, type_buffer, _countof(type_buffer));

			std::wstring type(type_buffer);
			std::wstring object_name(temp_buffer);

			PRectObject* component;

			if (type.compare(L"PLAYER") == 0)
			{
				component = (PPlayerCharacter*) new PPlayerCharacter();
				component->Set(path, object_name, pPoint(absolute_pos.x, absolute_pos.y));
				component->set_gravity_(450.0f);
				component->set_type_(Type::PLAYER);
				component->StatusSet(status_path ,component->get_object_name());
				LoadAnimationDataFromScript(animation_path);
				component->set_animation_list_(PObjectDataManager::get_animation_list_from_map(object_name)); //애니메이션 순서는 어차피 FSM정의순서를 따름!
				object_list.push_back(component);
			}
			else if (type.compare(L"MONSTER") == 0)
			{
				component = (PMonster*) new PMonster();
				component->Set(path, object_name, pPoint( absolute_pos.x, absolute_pos.y));
				component->set_gravity_(450.0f);
				component->set_type_(Type::MONSTER);
				object_list.push_back(component);
				component->StatusSet(status_path, component->get_object_name()); //아마 아직 미구현
			}
			else if (type.compare(L"NPC") == 0)
			{
				component = (PMonster*) new PRectObject();//아직 NPC객체가 없음
				component->Set(path, object_name, pPoint(absolute_pos.x, absolute_pos.y));
				component->set_type_(Type::NPC);
				object_list.push_back(component);
			}
			else if (type.compare(L"MAP") == 0)
			{
				component =  new PRectObject();
				component->Set(map_path, object_name, pPoint(map_pos.x, map_pos.y));
				component->set_type_(Type::MAP);
				object_list.insert(object_list.begin(), component); //map은 가장 먼저 렌더되도록 제일 앞에 위치.
			}
			
		

			

		}

		object_composition_list_.insert(std::make_pair(object_composition_name, object_list));
	}
	fclose(fp);

}

void PObjectDataManager::LoadAnimationDataFromScript(multibyte_string filepath)
{

	FILE* fp = nullptr;

	_wfopen_s(&fp, filepath.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR buffer[256] = { 0, };
	TCHAR temp_buffer[256] = { 0, };
	TCHAR name_buffer[256] = { 0, };

	int number_of_data = -1;

	_fgetts(buffer, _countof(buffer), fp); //한줄 받아오기(애니 데이터 갯수)
	_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_data);

	std::vector<PSprite*> vec;

	for (int index_data = 0; index_data < number_of_data; index_data++)
	{

		int number_of_sprite = -1;
		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer),
			&number_of_sprite);

		std::wstring object_name(temp_buffer);

		for (int index_data = 0; index_data < number_of_sprite; index_data++)
		{
			_fgetts(buffer, _countof(buffer), fp);
			_stscanf_s(buffer, _T("%s"), temp_buffer, _countof(temp_buffer));

			std::wstring sprite_name(temp_buffer);

			PSprite* t = new PSprite();
			t->Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(sprite_name), 1.0f, 1.0f);
			
			vec.push_back(t);
		}

		
		object_animation_list_.insert(std::make_pair(object_name, vec));

	}

}
