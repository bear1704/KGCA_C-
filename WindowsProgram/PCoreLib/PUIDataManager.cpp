#include "PUIDataManager.h"



PUIDataManager::PUIDataManager()
{
}


PUIDataManager::~PUIDataManager()
{
}

bool PUIDataManager::Init()
{
	return false;
}

bool PUIDataManager::Frame()
{
	return false;
}

bool PUIDataManager::Render()
{
	return false;
}

bool PUIDataManager::Release()
{
	return false;
}

PUIComponent * PUIDataManager::get_ui_composition_list_from_map(std::wstring key)
{

	auto iter = ui_composition_list_.find(key);
	if (iter != ui_composition_list_.end())
	{
		PUIComponent* data = (*iter).second;
		return data;
	}
	return nullptr;
	
}

void PUIDataManager::LoadDataFromScript(multibyte_string filepath)
{
	//#LIST 리스트갯수
	//리스트이름 종속요소갯수 리스트포지션x 리스트포지션y
	//객체이름 상대포지션x 상대포지션y 객체타입(버튼,이미지)
	
	const std::wstring path = L"data/UI/UI_data.txt";

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
		int numberof_uiobject;
		pPoint composition_pos;
		PUIComponent* component_list = new PUIComponent();

		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%d%f%f"), temp_buffer, _countof(temp_buffer),
			&numberof_uiobject, &composition_pos.x, &composition_pos.y);

		std::wstring UIcomposition_name(temp_buffer);

		for (int i = 0; i < numberof_uiobject; i++)
		{
			pPoint relative_pos;
			//ZeroMemory(type_buffer, sizeof(TCHAR) * 25);
			_fgetts(buffer, _countof(buffer), fp);
			_stscanf_s(buffer, _T("%s%f%f%s"), temp_buffer, _countof(temp_buffer),
				&relative_pos.x, &relative_pos.y, type_buffer, _countof(type_buffer));

			std::wstring type(type_buffer);
			std::wstring uiobject_name(temp_buffer);

			PUIComponent* uicomponent = nullptr;

			if (type.compare(L"BUTTON") == 0)
				uicomponent = (PButtonControl*) new PButtonControl();
			else if (type.compare(L"IMAGE") == 0)
				uicomponent = (PImageControl*) new PImageControl();

			uicomponent->Set(path, uiobject_name, pPoint(composition_pos.x + relative_pos.x, composition_pos.y + relative_pos.y));
			component_list->Add(uicomponent);

		}

		component_list->set_position_(composition_pos);
		ui_composition_list_.insert(std::make_pair(UIcomposition_name, component_list));
	}
	fclose(fp);


}
