#include "PObjectInfoManager.h"



PObjectInfoManager::PObjectInfoManager()
{
}


PObjectInfoManager::~PObjectInfoManager()
{
}

bool PObjectInfoManager::Init()
{
	return false;
}

bool PObjectInfoManager::Frame()
{
	return false;
}

bool PObjectInfoManager::Render()
{
	return false;
}

bool PObjectInfoManager::Release()
{
	return false;
}

ObjectInfo* PObjectInfoManager::get_object_info_list_from_map(std::wstring key)
{
	auto iter = rectobject_list.find(key);
	if (iter != rectobject_list.end())
	{
		ObjectInfo* status = (*iter).second;
		return status;
	}

	return nullptr;
}

void PObjectInfoManager::LoadDataFromScript(multibyte_string filepath)
{
	//이름, 이동속도, 박스 LTRB, 알파, 스케일, 스프라이트 경로, 스프라이트 이름
	FILE* fp = nullptr;

	_wfopen_s(&fp, filepath.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR buffer[256] = { 0, };
	TCHAR temp_buffer[256] = { 0, };
	TCHAR sprite_path_buffer[256] = { 0, };
	TCHAR sprite_name_buffer[64] = { 0, };
	TCHAR map_data_buffer[256] = { 0, }; //맵 로드일 경우, 맵의 콜리전 정보(있으면)

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
		_stscanf_s(buffer, _T("%s%f%f%f%f%f%f%f%s%s%s"), temp_buffer, _countof(temp_buffer),
			&move_speed ,&collision_box.left, &collision_box.top, &collision_box.right, &collision_box.bottom, &alpha, &scale, 
			sprite_path_buffer, _countof(sprite_path_buffer), sprite_name_buffer, _countof(sprite_name_buffer),
			map_data_buffer, _countof(map_data_buffer));
		

		std::wstring character_name(temp_buffer);
		std::wstring path(sprite_path_buffer);
		std::wstring sprite_name(sprite_name_buffer);
		std::wstring map_data(map_data_buffer);

		if (map_data.compare(L"") != 0) //Map data가 있다는 의미
		{
			PWallAndPlatform::GetInstance().set_data_path_(map_data);
			PWallAndPlatform::GetInstance().Set();
		}


		status->collision_box_ = collision_box;
		status->move_speed_ = move_speed;
		status->object_name_ = character_name;
		status->scale_ = scale;
		status->alpha_ = alpha;
		status->sprite_path = path;
		status->sprite_name = sprite_name;

		rectobject_list.insert(std::make_pair(character_name, status));
	}
	fclose(fp);
}


void PObjectDataManager::LoadDataFromScript(multibyte_string filepath)
{

	const std::wstring character_path = L"data/character/character_data.txt";
	const std::wstring map_path = L"data/map/map_data.txt";

	//이름, 이동속도, 박스 LTRB, 알파, 스케일, 스프라이트 경로, 스프라이트 이름
	FILE* fp = nullptr;

	_wfopen_s(&fp, filepath.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR buffer[256] = { 0, };
	TCHAR temp_buffer[256] = { 0, };
	TCHAR sprite_path_buffer[256] = { 0, };
	TCHAR sprite_name_buffer[64] = { 0, };
	TCHAR map_data_buffer[256] = { 0, }; //맵 로드일 경우, 맵의 콜리전 정보(있으면)
	TCHAR type_buffer[32] = { 0, };

	int number_of_data = -1;

	_fgetts(buffer, _countof(buffer), fp); //한줄 받아오기(캐릭터 데이터 갯수)
	_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_data);

	for (int index_data = 0; index_data < number_of_data; index_data++)
	{
		int number_of_field_data = -1;
		_fgetts(buffer, _countof(buffer), fp); //필드당 캐릭터 갯수(몹, NPC포함)
		_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_field_data);

		for (int field_data = 0; field_data < number_of_field_data; field_data++)
		{
			PRectObject* object = new PRectObject();
			pPoint object_position;

			_fgetts(buffer, _countof(buffer), fp);
			_stscanf_s(buffer, _T("%s%f%f%s"), temp_buffer, _countof(temp_buffer), &object_position.x, &object_position.y,
				type_buffer, _countof(type_buffer));

			std::wstring name(temp_buffer);
			std::wstring type(type_buffer);



		}

		FLOAT_RECT collision_box;
		float move_speed;
		float alpha; float scale;

		

		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%f%f%f%f%f%f%f%s%s%s"), temp_buffer, _countof(temp_buffer),
			&move_speed, &collision_box.left, &collision_box.top, &collision_box.right, &collision_box.bottom, &alpha, &scale,
			sprite_path_buffer, _countof(sprite_path_buffer), sprite_name_buffer, _countof(sprite_name_buffer),
			map_data_buffer, _countof(map_data_buffer));

		std::wstring character_name(temp_buffer);
		std::wstring path(sprite_path_buffer);
		std::wstring sprite_name(sprite_name_buffer);
		std::wstring map_data(map_data_buffer);

		if (map_data.compare(L"") != 0) //Map data가 있다는 의미
		{
			PWallAndPlatform::GetInstance().set_data_path_(map_data);
			PWallAndPlatform::GetInstance().Set();
		}


		status->collision_box_ = collision_box;
		status->move_speed_ = move_speed;
		status->object_name_ = character_name;
		status->scale_ = scale;
		status->alpha_ = alpha;
		status->sprite_path = path;
		status->sprite_name = sprite_name;

		rectobject_list.insert(std::make_pair(character_name, status));
	}
	fclose(fp);
}

