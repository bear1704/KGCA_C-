#include "Sample.h"

static int aaa = 0;

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
	
	player_character_ = new PCharacter();
	player_character_->Set(L"data/character/character_data.txt", L"player", pPoint(500,600));
	//player_character_->SetGravity(350.f);
	monster_[0] = new PMonster();
	monster_[0]->Set(L"data/character/character_data.txt", L"orange_mushroom_normal", pPoint(1400, 500));
	monster_[1] = new PMonster();
	monster_[1]->Set(L"data/character/character_data.txt", L"orange_mushroom_other", pPoint(1000, 300));
	map_ = new PRectObject();
	map_->Set(L"data/map/map_data.txt", L"map1", pPoint(P2DCamera::GetInstance().get_world_size_().x / 2, P2DCamera::GetInstance().get_world_size_().y / 2));

	
	return true;
}

bool Sample::Frame()
{
	
	player_character_->Frame();
	monster_[0]->Frame();
	monster_[1]->Frame();
	map_->Frame();
	/*monster_->Frame();
	tester_->Frame();
	tester2_->Frame();
	other_side_tester_->Frame();

	if (PCollision::RectInRect(player_character_->get_collision_rect_(), monster_->get_collision_rect_()))
	{
		OutputDebugString(L"collision!!\n");
	}*/
	

	return true;
}

bool  Sample::Render()
{



	map_->Render();
	player_character_->Render();
	monster_[0]->Render();
	monster_[1]->Render();

	//충돌 테스트 코드(콜리전박스 확인용) 
	FLOAT_RECT player_collision_rect = player_character_->get_collision_rect_();
	FLOAT_RECT pc1 = P2DCamera::GetInstance().WorldToGamescreenRECT(player_collision_rect);
	SetROP2(g_handle_off_screenDC, R2_NOTXORPEN);
	int prevMode = Rectangle(g_handle_off_screenDC, pc1.left, pc1.top, pc1.left + pc1.right, pc1.top + pc1.bottom);
	SetROP2(handle_off_screenDC, prevMode);

	FLOAT_RECT cam_center_pos_rect = P2DCamera::GetInstance().get_center_rect_();
	SetROP2(g_handle_off_screenDC, R2_NOTXORPEN);
	FLOAT_RECT colrect = P2DCamera::GetInstance().WorldToGamescreenRECT(cam_center_pos_rect);
	int prevMode1 = Rectangle(g_handle_off_screenDC, colrect.left, colrect.top,
		colrect.left+colrect.right, colrect.top+colrect.bottom);
	SetROP2(handle_off_screenDC, prevMode1);



	//PObjectRotateUtil::RotateAndDraw(monster_[1]->get_sprite_(), 0, 300, 200, angle, 1.0f, 4.0f, true);
	//PObjectRotateUtil::RotateAndDraw(player_character_->get_sprite_(), 0,600, 200, angle, 0.3f, 2.0f,  false);
	angle += 0.1f  * g_SecondPerFrame * 600.f;

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

PCORE_RUN(L"BoxCollision", 0, 0, 1024,768);

