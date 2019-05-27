#include "Sample.h"



Sample::Sample()
{
	player_character_ = new PCharacter(300,300);
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	player_character_->Init();
	return true;
}

bool Sample::Frame()
{
	player_character_->Frame();
	return true;
}

bool  Sample::Render()
{
	
	float posX = player_character_->get_position_().x;
	float posY = player_character_->get_position_().y;
	float half_width = (player_character_->get_collision_rect_().right) / 2;
	float half_height = (player_character_->get_collision_rect_().bottom) / 2;
	
	
	//충돌 테스트 코드(콜리전박스 확인용) 
	SetROP2(g_handle_off_screenDC, R2_NOTXORPEN);
	int prevMode = Rectangle(g_handle_off_screenDC, posX - half_width, posY - half_height, 
		posX + player_character_->get_collision_rect_().right - half_width, 
		posY + player_character_->get_collision_rect_().bottom - half_height);
	SetROP2(handle_off_screenDC, prevMode);


	player_character_->Render();



	return true;
}

bool Sample::Release()
{
	player_character_->Release();
	return true;
}

PCORE_RUN(L"BoxCollision", 0, 0, 800, 600);
