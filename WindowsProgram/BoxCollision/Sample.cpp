#include "Sample.h"


Sample::Sample()
{
	timer = 0.0f;
	sound_flag = false;
	
}


Sample::~Sample()
{
}

bool Sample::Init()
{

	InitDataLoad();
	
	
	if (g_current_scene_)
		g_current_scene_->Init();

	return true;
}

bool Sample::Frame()
{	

	if (g_current_scene_)
		g_current_scene_->Frame();

	
	timer += g_SecondPerFrame;
	if (timer > 0.1f && !sound_flag)
	{
		PSoundMgr::GetInstance().Load(L"data/sound/map.mp3");
		PSoundMgr::GetInstance().GetPtr(0)->SetMode(2);
		PSound* bgm = PSoundMgr::GetInstance().GetPtr(0);
		bgm->Play();
		sound_flag = true;
	}
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

	if (g_current_scene_)
		g_current_scene_->Render();

	



	return true;
}

bool Sample::Release()
{

	if(g_current_scene_)
		g_current_scene_->Release();

	

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


	PObjectInfoManager::GetInstance().LoadDataFromScript(L"data/UI/UI_data.txt", ObjectLoadType::UI);
	PObjectInfoManager::GetInstance().LoadDataFromScript(L"data/character/character_data.txt", ObjectLoadType::CHARACTER);
	PObjectInfoManager::GetInstance().LoadDataFromScript(L"data/map/map_data.txt", ObjectLoadType::MAP);
	//실험용 초기화 -> 지연로드와 미리 로드의 속도차이 확인, 확장성있는 지연로드를 위하여
	
	PUIDataManager::GetInstance().LoadDataFromScript(L"data/UI/UI_composition_list.txt");
	PObjectDataManager::GetInstance().LoadDataFromScript(L"data/character/character_composition_list.txt");
	PScene *scene1 = new PScene();
	PUIComponent* uicomp_settingbar = PUIDataManager::GetInstance().get_ui_composition_list_from_map(L"MYSETTINGBTN");
	std::vector<PRectObject*> game_objects_ = PObjectDataManager::GetInstance().get_object_list_from_map(L"MUSHROOMLAND");
	scene1->InsertObject(uicomp_settingbar);
	scene1->InsertObject(game_objects_);
	scene1->set_scene_name_(L"MUSHROOMLAND");
	
	g_current_scene_ = scene1;

	
	//PSoundMgr::GetInstance().Play(PSoundMgr::GetInstance().Load(L"data/sound/extree.mp3"));
	//PSoundMgr::GetInstance().Play(PSoundMgr::GetInstance().Load(L"data/sound/extree_die.mp3"));



	return true;
}



PCORE_RUN(L"MapleStory", 0, 0, 1024, 768);

