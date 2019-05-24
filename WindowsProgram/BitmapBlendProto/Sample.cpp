#include "Sample.h"

Sample::Sample()
{
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	object_airplane.Init();
	object_airplane.Load(L"../../data/bitmap/bitmap1.bmp");

	object_background.Init();
	object_background.Load(L"../../data/bitmap/kgcabk.bmp");

	PRectObjectStat background_stat;
	background_stat.position = pPoint(0, 0);
	RECT background_rect = { 0, 0, rectangle_client.right, rectangle_client.bottom }; 
	background_stat.rect = background_rect;
	background_stat.moveSpeed = 0.0f;
	object_background.Set(background_stat);

	PRectObjectStat plane_stat;
	plane_stat.position = pPoint(200, 300);
	RECT plane_rect = { 90,1,132,60 };
	plane_stat.rect = plane_rect;
	plane_stat.moveSpeed = 10.0f;
	object_airplane.Set(plane_stat);
	
	

	return true;

}

bool Sample::Frame()
{
	if (g_InputActionMap.wKey == KEYSTAT::KEY_HOLD)
	{
		*(object_airplane.get_position_xy(PXY::Y)) -= object_airplane.get_moveSpeed_() * g_SecondPerFrame * 10.0f;
	}
	if (g_InputActionMap.sKey == KEYSTAT::KEY_HOLD)
	{
		*(object_airplane.get_position_xy(PXY::Y)) += object_airplane.get_moveSpeed_() * g_SecondPerFrame * 10.0f;
	}
	if (g_InputActionMap.aKey == KEYSTAT::KEY_HOLD)
	{
		*(object_airplane.get_position_xy(PXY::X)) -= object_airplane.get_moveSpeed_() * g_SecondPerFrame * 10.0f;
	}
	if (g_InputActionMap.dKey == KEYSTAT::KEY_HOLD)
	{
		*(object_airplane.get_position_xy(PXY::X)) += object_airplane.get_moveSpeed_() * g_SecondPerFrame * 10.0f;
	}
	return true;
}

bool Sample::Render()
{
	//BitBlt(g_handle_off_screenDC, object_background.get_position_().x, object_background.get_position_().y
	//	, object_background.get_rect_().right, object_background.get_rect_().bottom, object_background.get_bitmap_()->handle_memoryDC_
	//	, 0, 0, SRCCOPY);

	//BitBlt(g_handle_off_screenDC, object_airplane.get_position_().x, object_airplane.get_position_().y,
	//	object_airplane.get_rect_().right, object_airplane.get_rect_().bottom, object_airplane.get_bitmap_()->handle_memoryDC_,
	//	object_airplane.get_rect_().left, object_airplane.get_rect_().top, SRCCOPY);

	object_background.Render();

	int plane_width = abs(object_airplane.get_rect_().right - object_airplane.get_rect_().left);
	int plane_height = abs(object_airplane.get_rect_().bottom - object_airplane.get_rect_().top);

	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = plane_width;
	bmi.bmiHeader.biHeight = plane_height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = plane_width * plane_height * 4;

	void* pivot_bitmap = 0;
	void* pivot_mask_bitmap = 0;
	void* pivot_offscreen_bitmap = 0;

	HBITMAP handle_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &pivot_bitmap, NULL, 0);
	HDC bitmap_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_dc, handle_bitmap);
	BitBlt(bitmap_dc, 0, 0, plane_width, plane_height, object_airplane.get_bitmap_()->handle_memoryDC_,
		object_airplane.get_rect_().left, object_airplane.get_rect_().top, SRCCOPY);
	DeleteDC(bitmap_dc);

	HBITMAP handle_mask_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &pivot_mask_bitmap, NULL, 0);
	HDC bitmap_mask_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_mask_dc, handle_mask_bitmap);
	BitBlt(bitmap_mask_dc, 0, 0, plane_width, plane_height, object_airplane.get_bitmap_mask_()->handle_memoryDC_,
		object_airplane.get_rect_().left, object_airplane.get_rect_().top, SRCCOPY);
	DeleteDC(bitmap_mask_dc);


	HBITMAP handle_offscreen_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &pivot_offscreen_bitmap, NULL, 0);
	HDC bitmap_offscreen_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_offscreen_dc, handle_offscreen_bitmap);
	BitBlt(bitmap_offscreen_dc, 0, 0, object_background.get_rect_().right,
		object_background.get_rect_().bottom, object_background.get_bitmap_()->handle_memoryDC_,
		object_airplane.get_position_().x, object_airplane.get_position_().y, SRCCOPY); //원본과 다름, 주의!
	DeleteDC(bitmap_offscreen_dc);

	float alpha = 0.8f;

	for (int y = 0; y < plane_height; y++)
	{
		byte* bitmap_RGB = (byte*)&((DWORD*)pivot_bitmap)[y * plane_width];
		byte* bitmap_mask_RGB = (byte*)&((DWORD*)pivot_mask_bitmap)[y* plane_width];
		byte* bitmap_offscreen_RGB = (byte*)&((DWORD*)pivot_offscreen_bitmap)[y* plane_width];

		for (int x = 0; x < plane_width; x++)
		{
			byte origin_A = bitmap_RGB[3];
			byte origin_R = bitmap_RGB[2];
			byte origin_G = bitmap_RGB[1];
			byte origin_B = bitmap_RGB[0];

			if (bitmap_mask_RGB[0] == 255 && bitmap_mask_RGB[1] == 255 && bitmap_mask_RGB[2] == 255)
			{    //마스크RGB가 WHITE일 경우, 배경으로 처리
				bitmap_RGB[3] = bitmap_offscreen_RGB[3];
				bitmap_RGB[2] = bitmap_offscreen_RGB[2];
				bitmap_RGB[1] = bitmap_offscreen_RGB[1];
				bitmap_RGB[0] = bitmap_offscreen_RGB[0];
			}
			else
			{
				bitmap_RGB[3] = 0xff;
				bitmap_RGB[2] = bitmap_offscreen_RGB[2] * (1.0f - alpha) + origin_R * alpha;
				bitmap_RGB[1] = bitmap_offscreen_RGB[1] * (1.0f - alpha) + origin_G * alpha;
				bitmap_RGB[0] = bitmap_offscreen_RGB[0] * (1.0f - alpha) + origin_B * alpha;
			}

			bitmap_RGB += 4;
			bitmap_mask_RGB += 4;
			bitmap_offscreen_RGB += 4;
		}
	}


	bitmap_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_dc, handle_bitmap);
	//BitBlt(g_handle_off_screenDC, object_airplane.get_position_().x, object_airplane.get_position_().y,
	//	object_airplane.get_rect_().right, object_airplane.get_rect_().bottom, bitmap_dc, 
	//	0, 0, SRCCOPY);

	SetStretchBltMode(g_handle_off_screenDC, HALFTONE);
	StretchBlt(g_handle_off_screenDC,
		object_airplane.get_position_().x , object_airplane.get_position_().y , plane_width, plane_height,
		bitmap_dc, 0,0, plane_width, plane_height,
		SRCCOPY);

	DeleteObject(handle_bitmap);
	DeleteObject(handle_mask_bitmap);
	DeleteObject(handle_offscreen_bitmap);
	DeleteObject(bitmap_dc);


	return true;
}

bool Sample::Release()
{
	return true;
}