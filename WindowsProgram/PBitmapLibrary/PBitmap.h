#pragma once

#include "PStd.h"

class PBitmap
{
public:
	PBitmap();
	virtual ~PBitmap();
public:
	HBITMAP handle_bitmap;
	HDC handle_memory_DC;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(std::wstring filename);
	bool Draw(float x, float y, RECT rect);

};

