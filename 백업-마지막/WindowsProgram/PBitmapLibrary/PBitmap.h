#pragma once
#include "PStd.h"

class PBitmap
{
public:
	PBitmap();
	virtual ~PBitmap();
public:
	HBITMAP  handle_bitmap_;
	HDC		 handle_memoryDC_;
	multibyte_string image_path_;
	multibyte_string image_name_;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(std::wstring filename);
	bool Draw(float x, float y, RECT rect, DWORD draw_mode);
	bool DrawColorKey(float x, float y, RECT rect, COLORREF key_color);
	
};

