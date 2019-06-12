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
	
	
	if (current_scene_)
		current_scene_->Init();

	return true;
}

bool Sample::Frame()
{	

	if (current_scene_)
		current_scene_->Frame();

	
	return true;
}

bool  Sample::Render()
{

	//map_->Render();
	//player_character_->Render();
	//monster_[0]->Render();
	//monster_[1]->Render();

	//충돌 테스트 코드(콜리전박스 확인용) 
	//FLOAT_RECT player_collision_rect = player_character_->get_collision_rect_();
	//draw_test_rect(player_collision_rect);

	//draw_test_rect(monster_[0]->get_foot_plane_box());
	//draw_test_rect(monster_[1]->get_foot_plane_box());

	//PObjectRotateUtil::RotateAndDraw(monster_[1]->get_sprite_(), 0, 300, 200, angle, 1.0f, 4.0f, true);
	//PObjectRotateUtil::RotateAndDraw(player_character_->get_sprite_(), 0,600, 200, angle, 0.3f, 2.0f,  false);
	angle += 0.1f  * g_SecondPerFrame * 600.f;

	if (current_scene_)
		current_scene_->Render();

	



	return true;
}

bool Sample::Release()
{

	if(current_scene_)
		current_scene_->Release();

	

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
	PScene *scene1 = new PScene();
	PUIDataManager::GetInstance().LoadDataFromScript(L"data/UI/UI_composition_list.txt");
	PUIComponent* uicomp_settingbar = PUIDataManager::GetInstance().get_ui_composition_list_from_map(L"MYSETTINGBTN");
	PUIComponent* uicomp_hpmp_guage = PUIDataManager::GetInstance().get_ui_composition_list_from_map(L"HPMP_GUAGE");
	PObjectDataManager::GetInstance().LoadDataFromScript(L"data/character/character_composition_list.txt");
	std::vector<PRectObject*> game_objects_ = PObjectDataManager::GetInstance().get_object_list_from_map(L"MUSHROOMLAND");
	scene1->InsertObject(uicomp_settingbar);
	scene1->InsertObject(game_objects_);
	scene1->InsertObject(uicomp_hpmp_guage);
	
	current_scene_ = scene1;

	

	return true;
}



PCORE_RUN(L"BoxCollision", 0, 0, 1024, 768);

