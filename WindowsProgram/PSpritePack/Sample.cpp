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


	PSpriteManager::GetInstance().LoadDataFromScript(L"sprite_coord.txt"); //스프라이트 총 3개의 rect데이터를 지닌 스프라이트 로드
	sprites[0].Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtNormal"), 0.5f, 1.0f);
	sprites[0].SetPosition(222, 222);
	sprites[1].Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtAlpha"), 0.7f, 1.2f);
	sprites[1].SetPosition(116.4, 72.2);
	sprites[2].Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtExplosion"), 1.0f,4.0f);
	sprites[2].SetPosition(300, 400);
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
	sprites[2].Draw();
	sprites[0].Draw();
	sprites[1].Draw();
	
	//sprite2.Render();
	
	return true;
}

bool Sample::Release()
{
	return true;
}