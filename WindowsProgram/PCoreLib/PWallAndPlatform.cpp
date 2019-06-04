#include "PWallAndPlatform.h"
#include <assert.h>


PWallAndPlatform::PWallAndPlatform()
{
}


PWallAndPlatform::~PWallAndPlatform()
{
}

bool PWallAndPlatform::Init()
{
	platform_list_.reserve(10);
	monster_wall_list_.reserve(6);
	wall_list_.reserve(2);

	return true;
}

bool PWallAndPlatform::Frame()
{
	return true;
}

bool PWallAndPlatform::Render()
{
	return true;
}

bool PWallAndPlatform::Release()
{
	return true;
}

void PWallAndPlatform::Set()
{
	LoadPlatformData(data_path_);
}

std::vector<FLOAT_RECT>& PWallAndPlatform::get_platform_list_()
{
	return platform_list_;
}

std::vector<FLOAT_RECT>& PWallAndPlatform::get_monster_wall_list_()
{
	return monster_wall_list_;
}

std::vector<FLOAT_RECT>& PWallAndPlatform::get_wall_list_()
{
	return wall_list_;
}



void PWallAndPlatform::LoadPlatformData(multibyte_string filepath)
{

	FILE* fp = nullptr;

	_wfopen_s(&fp, filepath.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR buffer[256] = { 0, };
	TCHAR temp_buffer[32] = { 0, }; //type
	int number_of_platform_data = -1;

	_fgetts(buffer, _countof(buffer), fp); //콜리전, 콜리전 갯수 받아오기
	_stscanf_s(buffer, _T("%s%d"), temp_buffer, _countof(temp_buffer), &number_of_platform_data);

	int number_of_max_frames;
	for (int data_count = 0; data_count < number_of_platform_data; data_count++)
	{
		FLOAT_RECT load_rect_list;

		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%f%f%f%f%s"),
			&load_rect_list.left, &load_rect_list.top, &load_rect_list.right, &load_rect_list.bottom,
			temp_buffer, _countof(temp_buffer));

		std::wstring object_type = temp_buffer;

		if (object_type.compare(L"PLATFORM") == 0)
		{
			platform_list_.push_back(load_rect_list);
		}
		else if (object_type.compare(L"MONSTERWALL") == 0)
		{
			monster_wall_list_.push_back(load_rect_list);

		}
		else if (object_type.compare(L"WALL") == 0)
		{
			wall_list_.push_back(load_rect_list);
		}

	}
	fclose(fp);
}


void PWallAndPlatform::set_data_path_(std::wstring str)
{
	data_path_ = str;
}
