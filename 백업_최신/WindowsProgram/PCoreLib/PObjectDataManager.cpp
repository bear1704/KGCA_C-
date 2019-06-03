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

ObjectInfo* PObjectDataManager::get_object_info_list_from_map(std::wstring key)
{
	auto iter = object_info_list.find(key);
	if (iter != object_info_list.end())
	{
		ObjectInfo* status = (*iter).second;
		return status;
	}

	return nullptr;
}

void PObjectDataManager::LoadDataFromScript(multibyte_string filepath)
{
	//이름, 이동속도, 박스 LTRB, 알파, 스케일, 스프라이트 경로, 스프라이트 이름
	FILE* fp = nullptr;

	_wfopen_s(&fp, filepath.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR buffer[256] = { 0, };
	TCHAR temp_buffer[256] = { 0, };
	TCHAR sprite_path_buffer[256] = { 0, };
	TCHAR sprite_name_buffer[64] = { 0, };
	int number_of_data = -1;

	_fgetts(buffer, _countof(buffer), fp); //한줄 받아오기(캐릭터 데이터 갯수)
	_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_data);

	for (int index_data = 0; index_data < number_of_data; index_data++)
	{
	
		ObjectInfo* status = new ObjectInfo();
		FLOAT_RECT collision_box;
		float move_speed;
		float alpha; float scale;

		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%f%f%f%f%f%f%f%s%s"), temp_buffer, _countof(temp_buffer),
			&move_speed ,&collision_box.left, &collision_box.top, &collision_box.right, &collision_box.bottom, &alpha, &scale, 
			sprite_path_buffer, _countof(sprite_path_buffer), sprite_name_buffer, _countof(sprite_name_buffer));
		
		std::wstring character_name(temp_buffer);
		std::wstring path(sprite_path_buffer);
		std::wstring sprite_name(sprite_name_buffer);

		status->collision_box_ = collision_box;
		status->move_speed_ = move_speed;
		status->object_name_ = character_name;
		status->scale_ = scale;
		status->alpha_ = alpha;
		status->sprite_path = path;
		status->sprite_name = sprite_name;

		object_info_list.insert(std::make_pair(character_name, status));
	}
	fclose(fp);
}
