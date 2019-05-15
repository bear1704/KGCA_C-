#include "Sample.h"



Sample::Sample()
{
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	
	PSpriteManager::GetInstance().LoadRectData(L"sprite_coord.txt"); //스프라이트 총 3개의 rect데이터를 지닌 스프라이트 로드
	object_sprite.Load(L"../../bitmap/bitmap1.bmp"); //첫번째 스프라이트에(rt_explosion)  비트맵 로드 
	object_sprite.Set(100, 100, PSpriteManager::GetInstance().get_sprite_from_map(0)->sprite_rectlist_, 10, 1);
	//100,100좌표에 매니져가 가지고 있는 스프라이트 중 첫 번째 스프라이트의 렉트 데이터를 가져와서 세팅한다. 
	object_sprite.Render();
	

	return true;

}