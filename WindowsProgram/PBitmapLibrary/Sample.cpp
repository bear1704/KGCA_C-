#include "Sample.h"



Sample::Sample()
{
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	object_background_bitmap_.Init();
	object_background_bitmap_.Load(L"../../data/bitmap/Loading800x600.bmp");
	PRectObjectStat stat;
	stat.position = pPoint(0, 0);
	RECT rect = { 0, 0, rectangle_client.right, rectangle_client.bottom };
	stat.rect = rect;
	object_background_bitmap_.Set(stat);

	hero_.Init();
	hero_.Load(L"../../data/bitmap/bitmap1.bmp");
	PRectObjectStat stat1;
	stat1.position = pPoint(100, 100);
	RECT rect1 = { 90, 1 , 40, 60 };
	stat1.rect = rect1;
	stat1.moveSpeed = 100.0f;
	hero_.Set(stat1);

	character_npc_.Init();
	character_npc_.Load(L"../../data/bitmap/bitmap1.bmp");
	PRectObjectStat stat2;
	stat2.position = pPoint(200, 200);
	RECT rect2 = { 46, 62, 67, 79 };
	stat2.rect = rect2;
	character_npc_.Set(stat2);

	//PSoundMgr::GetInstance().Play(PSoundMgr::GetInstance().Load(L"../../data/sound/onlyLove.mp3"));

	return true;
}

bool Sample::Frame()
{
	object_background_bitmap_.Frame();
	hero_.Frame();
	character_npc_.Frame();
	
	return true;
}

bool Sample::Render()
{
	object_background_bitmap_.Render();
	hero_.Render();
	character_npc_.Render();
	return true;
}

bool Sample::Release()
{
	object_background_bitmap_.Release();
	hero_.Release();
	character_npc_.Release();
	return true;
}

PCORE_RUN(L"abcd", 0, 0, 800, 600);

