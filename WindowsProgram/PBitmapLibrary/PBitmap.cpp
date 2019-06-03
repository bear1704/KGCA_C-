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
	DeleteObject(handle_bitmap_);
	return true;
}

bool PBitmap::Load(std::wstring filename)
{
	handle_bitmap_ = (HBITMAP)LoadImage(g_hInstance, 
		filename.c_str(), IMAGE_BITMAP,
		0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	if (handle_bitmap_ == NULL) return false;


	handle_memoryDC_ = CreateCompatibleDC(g_handle_screenDC);
	SelectObject(handle_memoryDC_, handle_bitmap_);
	return true;
}

bool PBitmap::Draw(float x, float y, RECT rect, DWORD draw_mode)
{
	BitBlt(g_handle_off_screenDC, x, y,
		rect.right, rect.bottom,
		handle_memoryDC_,
		rect.left, rect.top,
		draw_mode);

	return true;
}

bool PBitmap::DrawColorKey(float x, float y, RECT rect, COLORREF key_color)
{
	TransparentBlt(
		g_handle_off_screenDC, x, y, rect.right, rect.bottom, handle_memoryDC_, rect.left, rect.top,
		rect.right, rect.bottom, key_color);

	return true;
}

