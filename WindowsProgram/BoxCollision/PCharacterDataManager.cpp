#include "PCharacterDataManager.h"



PCharacterDataManager::PCharacterDataManager()
{
}


PCharacterDataManager::~PCharacterDataManager()
{
}

bool PCharacterDataManager::Init()
{
	return false;
}

bool PCharacterDataManager::Frame()
{
	return false;
}

bool PCharacterDataManager::Render()
{
	return false;
}

bool PCharacterDataManager::Release()
{
	return false;
}

CharacterStatus* PCharacterDataManager::get_character_status_list_from_map(std::wstring key)
{
	auto iter = character_status_list.find(key);
	if (iter != character_status_list.end())
	{
		CharacterStatus* status = (*iter).second;
		return status;
	}

	return nullptr;
}

void PCharacterDataManager::LoadDataFromScript(multibyte_string filepath)
{

	FILE* fp = nullptr;

	_wfopen_s(&fp, filepath.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR buffer[256] = { 0, };
	TCHAR temp_buffer[256] = { 0, };
	TCHAR temp_name_buffer[256] = { 0, };
	int number_of_data = -1;

	_fgetts(buffer, _countof(buffer), fp); //한줄 받아오기(캐릭터 데이터 갯수)
	_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_data);

	for (int index_data = 0; index_data < number_of_data; index_data++)
	{
	
		CharacterStatus* status = new CharacterStatus();
		RECT collision_box;
		float move_speed;

		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%f%d%d%d%d"), temp_buffer, _countof(temp_buffer),
			&move_speed ,&collision_box.left, &collision_box.top, &collision_box.right, &collision_box.bottom);
		
		std::wstring character_name(temp_buffer);
		
		status->collision_box = collision_box;
		status->move_speed = move_speed;

		character_status_list.insert(std::make_pair(character_name, status));
	}
	fclose(fp);
}
