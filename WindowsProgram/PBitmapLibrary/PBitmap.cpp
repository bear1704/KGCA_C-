#include "PBitmap.h"



PBitmap::PBitmap()
{
}


PBitmap::~PBitmap()
{
}

bool PBitmap::Init()
{
	return true;
}

bool PBitmap::Frame()
{
	return true;
}

bool PBitmap::Render()
{
	return true;
}

bool PBitmap::Release()
{
	DeleteObject(handle_bitmap);
	return true;
}

bool PBitmap::Load(std::wstring filename)
{
	handle_bitmap = (HBITMAP)LoadImage(g_hInstance, 
		filename.c_str(), IMAGE_BITMAP,
		0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	handle_memory_DC = CreateCompatibleDC(g_handle_screenDC);
	SelectObject(handle_memory_DC, handle_bitmap);


	return true;
}

bool PBitmap::Draw(float x, float y, RECT rect)
{
	BitBlt(g_handle_off_screenDC, x, y,
		rect.right, rect.bottom,
		handle_memory_DC,
		rect.left, rect.top,
		SRCCOPY);

	return true;
}