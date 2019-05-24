#pragma once
#include "Sample.h"
#include <time.h>



Sample::Sample()
{
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	background.Init();
	background.Load(L"../../data/bitmap/kgcabk.bmp");
	PRectObjectStat background_stat;
	background_stat.position = pPoint(0, 0);
	RECT background_rect = { 0, 0, rectangle_client.right, rectangle_client.bottom };
	background_stat.rect = background_rect;
	background_stat.moveSpeed = 0.0f;
	background.Set(background_stat);

	PSpriteManager::GetInstance().LoadDataFromScript(L"sprite_coord.txt"); //스프라이트 총 3개의 rect데이터를 지닌 스프라이트 로드
	sprites[0].Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtNormal"));
	sprites[0].SetPosition(100, 100);
	sprites[1].Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtAlpha"));
	sprites[1].SetPosition(400, 100);
	sprites[2].Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtClash"));
	sprites[2].SetPosition(300, 300);
	return true;
}

bool Sample::Frame()
{
	sprites[0].Frame();
	sprites[1].Frame();
	sprites[2].Frame();
	return true;
}

bool Sample::Render()
{
	background.Render();
	sprites[2].Draw(SRCCOPY);
	sprites[0].Draw(SRCCOPY);
	sprites[1].Draw(SRCCOPY);
	
	//sprite2.Render();
	
	return true;
}