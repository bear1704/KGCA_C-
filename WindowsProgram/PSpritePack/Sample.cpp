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
	sprites[0].Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtNormal"));
	sprites[0].SetPosition(100, 100);
	sprites[1].Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtAlpha"));
	sprites[1].SetPosition(400, 100);

	
	return true;
}

bool Sample::Frame()
{
	sprites[0].Frame();
	sprites[1].Frame();

	

	return true;
}

bool Sample::Render()
{
	sprites[0].Draw(SRCCOPY);
	sprites[1].Draw(SRCCOPY);
	//sprite2.Render();
	
	return true;
}