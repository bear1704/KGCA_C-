#include "Sample.h"



Sample::Sample()
{
	x = 100;
	y = 100;
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	handle_bitmap = (HBITMAP)LoadImage(
		hInstance, _T("../../data/bitmap/bitmap1.bmp"),
		IMAGE_BITMAP,
		0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);

	memory_DC = CreateCompatibleDC(handle_ScreenDC);
	SelectObject(memory_DC, handle_bitmap);

	rect_object.left = 90;
	rect_object.top = 1;
	rect_object.right = 40;
	rect_object.bottom = 60;

	return true;

}

bool Sample::Render()
{
	BitBlt(handle_ScreenDC, x, y, rect_object.right, rect_object.bottom, memory_DC, rect_object.left, rect_object.top, SRCCOPY);
	return true;
}

bool Sample::Frame()
{
	

	if (g_InputActionMap.wKey == KEYSTAT::KEY_HOLD)
	{
		y -= 100 * g_SecondPerFrame;
	}
	
	return true;
}

bool Sample::Release()
{
	DeleteObject(handle_bitmap);
	return true;
}

PCORE_RUN(L"Bitmap",0, 0, 800, 600);