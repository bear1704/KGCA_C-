#include "Sample.h"



Sample::Sample()
{
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	background_object_.Init();
	background_object_.Load(L"../../data/bitmap/Loading800x600.bmp");
	PRectObjectStat stat;
	stat.position = pPoint_(0, 0);
	RECT rect = { 0, 0, rectangle_client.right, rectangle_client.bottom };   
	stat.rect = rect;
	stat.moveSpeed = 0.0f;
	background_object_.Set(stat);


	mycharacter_object_.Init();
	mycharacter_object_.Load(L"../../data/bitmap/bitmap1.bmp");
	stat.position = pPoint_(400, 300);
	RECT rect1 = { 90, 1, 40, 60};   stat.rect = rect1;
	stat.moveSpeed = 0.0f;
	mycharacter_object_.Set(stat);

	return true;
}
bool Sample::Frame()
{
	background_object_.Frame();
	mycharacter_object_.Frame();

	return true;
}

bool Sample::Render()
{
	background_object_.Render();
	mycharacter_object_.Render();

	
	return true;
}

bool Sample::Release()
{
	background_object_.Release();
	mycharacter_object_.Release();
	return true;
}
