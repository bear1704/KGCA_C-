#include "Sample.h"

Sample::Sample()
{
	//player_character_ = new PCharacter(300,300, L"player");
	//monster_ = new PMonster(pPoint(340,500), L"player2");
	//tester_ = new PMonster(pPoint(500, 100), L"orange_mushroom_normal");
	//tester2_ = new PMonster(pPoint(600, 100), L"orange_mushroom_normal");
	//other_side_tester_ = new PMonster(pPoint(700, 100), L"orange_mushroom_other");
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	
	player_character_ = new PPlayerCharacter();
	player_character_->Set(L"data/character/character_data.txt", L"player", pPoint(500, 600));
	player_character_->SetGravity(450.f);
	monster_[0] = new PMonster();
	monster_[0]->Set(L"data/character/character_data.txt", L"orange_mushroom_normal", pPoint(1400, 500));
	monster_[0]->SetGravity(450.f);
	monster_[1] = new PMonster();
	monster_[1]->Set(L"data/character/character_data.txt", L"orange_mushroom_other", pPoint(1000, 300));
	monster_[1]->SetGravity(450.f);
	map_ = new PRectObject();
	map_->Set(L"data/map/map_data.txt", L"map1", pPoint(P2DCamera::GetInstance().get_world_size_().x / 2, P2DCamera::GetInstance().get_world_size_().y / 2));
	

	//버튼 테스트
	PButtonControl* button2 = new PButtonControl();
	button2->Set(L"D:/SC/C_C++/Git/WindowsProgram/Button/data/UI/UI_data.txt", L"optionbutton", pPoint(500, 500));
	PUIComponent* button = (PButtonControl*)button2->Clone();

	button1 = (PButtonControl*)button;

	comp_.component_list.push_back(button1);


	
	return true;
}

bool Sample::Frame()
{
	
	player_character_->Frame();
	monster_[0]->Frame();
	monster_[1]->Frame();
	map_->Frame();
	
	//버튼 테스트
	comp_.Frame();

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
	comp_.Draw();
	draw_test_rect(comp_.get_collision_rect_());

	return true;
}

bool Sample::Release()
{
	player_character_->Release();
	monster_[0]->Release();
	monster_[1]->Release();
	map_->Release();
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

PCORE_RUN(L"BoxCollision", 0, 0, 1024,768);

