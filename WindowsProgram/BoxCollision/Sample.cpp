#include "Sample.h"

Sample::Sample()
{

}


Sample::~Sample()
{
}

bool Sample::Init()
{
	
	
	InitDataLoad();
	//버튼 테스트

	ui_componentset_list.Init();
	return true;
}

bool Sample::Frame()
{
	
	player_character_->Frame();
	monster_[0]->Frame();
	monster_[1]->Frame();
	map_->Frame();
	ui_componentset_list.Frame();
	

	return true;
}

bool  Sample::Render()
{

	map_->Render();
	player_character_->Render();
	monster_[0]->Render();
	monster_[1]->Render();

	//충돌 테스트 코드(콜리전박스 확인용) 
	//FLOAT_RECT player_collision_rect = player_character_->get_collision_rect_();
	//draw_test_rect(player_collision_rect);
	FLOAT_RECT cam_center_pos_rect = P2DCamera::GetInstance().get_center_rect_();
	draw_test_rect(cam_center_pos_rect);
	


	int platform_size = PWallAndPlatform::GetInstance().get_platform_list_().size();
	int monsterwall_size = PWallAndPlatform::GetInstance().get_monster_wall_list_().size();
	int wall_size = PWallAndPlatform::GetInstance().get_wall_list_().size();


	for (int i = 0; i < platform_size; i++)
	{
		draw_test_rect(PWallAndPlatform::GetInstance().get_platform_list_().at(i));
	}
	for (int i = 0; i < monsterwall_size; i++)
	{
		draw_test_rect(PWallAndPlatform::GetInstance().get_monster_wall_list_().
			at(i));
	}
	for (int i = 0; i < wall_size; i++)
	{
		draw_test_rect(PWallAndPlatform::GetInstance().get_wall_list_().at(i));
	}
	draw_test_rect(player_character_->get_foot_plane_box());
	draw_test_rect(monster_[0]->get_foot_plane_box());
	draw_test_rect(monster_[1]->get_foot_plane_box());

	//PObjectRotateUtil::RotateAndDraw(monster_[1]->get_sprite_(), 0, 300, 200, angle, 1.0f, 4.0f, true);
	//PObjectRotateUtil::RotateAndDraw(player_character_->get_sprite_(), 0,600, 200, angle, 0.3f, 2.0f,  false);
	angle += 0.1f  * g_SecondPerFrame * 600.f;



	//버튼 테스트
	ui_componentset_list.Render();
	return true;
}

bool Sample::Release()
{
	player_character_->Release();
	monster_[0]->Release();
	monster_[1]->Release();
	map_->Release();
	ui_componentset_list.Release();
	return true;
}

void Sample::draw_test_rect(FLOAT_RECT rect)
{

	SetROP2(g_handle_off_screenDC, R2_NOTXORPEN);
	FLOAT_RECT arect = P2DCamera::GetInstance().WorldToGamescreenRECT(rect);
	int prevMode2 = Rectangle(g_handle_off_screenDC, arect.left, arect.top,
		arect.left + arect.right, arect.top + arect.bottom);
	SetROP2(handle_off_screenDC, prevMode2);
}

bool Sample::InitDataLoad()
{
	player_character_ = new PPlayerCharacter();
	player_character_->Set(L"data/character/character_data.txt", L"player", pPoint(500, 500));
	player_character_->SetGravity(450.f);
	monster_[0] = new PMonster();
	monster_[0]->Set(L"data/character/character_data.txt", L"orange_mushroom_normal", pPoint(1400, 500));
	monster_[0]->SetGravity(450.f);
	monster_[1] = new PMonster();
	monster_[1]->Set(L"data/character/character_data.txt", L"orange_mushroom_other", pPoint(1000, 300));
	monster_[1]->SetGravity(450.f);
	map_ = new PRectObject();
	map_->Set(L"data/map/map_data.txt", L"map1", pPoint(P2DCamera::GetInstance().get_world_size_().x / 2, P2DCamera::GetInstance().get_world_size_().y / 2));
	
	LoadUIDataFromScript(L"data/UI/UI_composition_list.txt");


	return true;
}

void Sample::LoadUIDataFromScript(multibyte_string filepath)
{
	//#LIST 리스트갯수
	//리스트이름 종속요소갯수 리스트포지션x 리스트포지션y
	//객체이름 상대포지션x 상대포지션y 객체타입(버튼,이미지)

	const std::wstring const path = L"data/UI/UI_data.txt";

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
				&relative_pos.x, &relative_pos.y , type_buffer, _countof(type_buffer));

			std::wstring type(type_buffer);
			std::wstring uiobject_name(temp_buffer);

			PUIComponent* uicomponent = new PUIComponent();
			
			if (type.compare(L"BUTTON") == 0)
				uicomponent = (PButtonControl*) new PButtonControl();
			else if (type.compare(L"IMAGE"))
				uicomponent = (PImageControl*) new PImageControl();

			uicomponent->Set(path, uiobject_name, pPoint(composition_pos.x + relative_pos.x, composition_pos.y + relative_pos.y));
			ui_componentset_list.Add(uicomponent);

		}

		ui_componentset_list.set_position_(composition_pos);
	}
	fclose(fp);
}


PCORE_RUN(L"BoxCollision", 0, 0, 1024, 768);

