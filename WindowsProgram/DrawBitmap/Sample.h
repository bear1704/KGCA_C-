#pragma once
#include "PCore.h"

class Sample :
	public PCore
{
private:
	HBITMAP handle_bitmap;
	HDC memory_DC;
	float x;
	float y;
	RECT rect_object;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Sample();
	~Sample();
};

