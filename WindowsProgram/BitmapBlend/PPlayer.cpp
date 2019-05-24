#include "PPlayer.h"



PPlayer::PPlayer()
{
}


PPlayer::~PPlayer()
{
}

bool PPlayer::AlphaBlendRender(int width, int height, HDC handle_offscreenDC, HDC handle_colorDC, HDC handle_maskDC, float alpha)
{
	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = width * height * 4;
	
	void* bitmap_pivots = 0;
	HBITMAP handle_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &bitmap_pivots, NULL, 0);

	HDC dc = CreateCompatibleDC(NULL);
	SelectObject(dc, handle_bitmap);
	BitBlt(dc, 0, 0, width, height, handle_colorDC, 0, 0, SRCCOPY);
	//BitBlt(g_handle_off_screenDC, 0, 0, width, height, dc, 0, 0, SRCCOPY);
	DeleteDC(dc);

	//마스크
	void* mask_bitmap_pivots;
	HBITMAP handle_mask_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &mask_bitmap_pivots, NULL, 0);

	HDC maskDC = CreateCompatibleDC(NULL);
	SelectObject(maskDC, handle_mask_bitmap);
	BitBlt(maskDC, 0, 0, width, height, handle_maskDC, 0, 0, SRCCOPY);
	//BitBlt(g_handle_off_screenDC, 0, 0, width, height, maskDC, 0, 0, SRCCOPY);
	DeleteDC(maskDC); //maskDC = nullptr
	
	//오프스크린
	void* offscreen_bitmap_pivots = 0;
	HBITMAP handle_offscreen_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &offscreen_bitmap_pivots, NULL, 0);
	HDC offDC = CreateCompatibleDC(NULL);
	SelectObject(offDC, handle_offscreen_bitmap);
	BitBlt(offDC, 0, 0, width, height, g_handle_off_screenDC, position_.x, position_.y, SRCCOPY);
	DeleteDC(offDC);


	for (int y = 0; y < height; y++) 
	{
		byte* bitmap_image_color_coord= (byte*)&((DWORD*)bitmap_pivots)[y * width]; //각 이미지들의 좌표값, 초기값 0,0위치
		byte* mask_image_color_coord= (byte*)&((DWORD*)mask_bitmap_pivots)[y * width];
		byte* offscreen_image_color_coord= (byte*)&((DWORD*)offscreen_bitmap_pivots)[y * width];
	
		for (int x = 0; x < width; x++)
		{
			byte A = bitmap_image_color_coord[3];
			byte R = bitmap_image_color_coord[2];
			byte G = bitmap_image_color_coord[1];
			byte B = bitmap_image_color_coord[0];
			//mask가 줄곧 0?
			OutputDebugString(L"" + mask_image_color_coord[2]);
			OutputDebugString(L"abba\n");
			if (mask_image_color_coord[2] == 255 && mask_image_color_coord[1] == 255 && mask_image_color_coord[0] == 255)
			{
				bitmap_image_color_coord[3] = offscreen_image_color_coord[3];
				bitmap_image_color_coord[2] = offscreen_image_color_coord[2];
				bitmap_image_color_coord[1] = offscreen_image_color_coord[1];
				bitmap_image_color_coord[0] = offscreen_image_color_coord[0];
			}
			else //검은 부분
			{
				bitmap_image_color_coord[3] = 0xff;
				//bitmap_image_color_coord[2] = offscreen_image_color_coord[2] * (1.0f - alpha) + R * alpha;
				//bitmap_image_color_coord[1] = offscreen_image_color_coord[1] * (1.0f - alpha) + G * alpha;
				//bitmap_image_color_coord[0] = offscreen_image_color_coord[0] * (1.0f - alpha) + B * alpha;
				bitmap_image_color_coord[0] = 0x66;
				bitmap_image_color_coord[1] = 0x66;
				bitmap_image_color_coord[2] = 0x66;
			}
			bitmap_image_color_coord += 4; //다음 픽셀로
			mask_image_color_coord += 4;
			offscreen_image_color_coord += 4;

		}

	}

	dc = CreateCompatibleDC(NULL);
	SelectObject(dc, handle_bitmap); 

	//SetStretchBltMode(g_handle_off_screenDC, HALFTONE);
	//StretchBlt(g_handle_off_screenDC, position_.x, position_.y, width+100, height+100,
	//	dc, 0, 0, width, height, SRCCOPY);
	BitBlt(g_handle_off_screenDC, 400, 300, width, height,dc, 0, 0, SRCCOPY);
	//BitBlt(g_handle_off_screenDC, 0, 0, rect_.right, rect_.bottom, handle_maskDC, rect_.left, rect_.top, SRCCOPY);

	DeleteObject(handle_mask_bitmap);
	DeleteObject(handle_offscreen_bitmap);
	DeleteObject(handle_bitmap);
	DeleteDC(dc);

	//여기까지



	return true;
}

bool PPlayer::Init()
{
	PRectObject::Init();//이거왜하는거지; 캐릭터 초기화?
	handle_maskDC_ = CreateCompatibleDC(NULL);
	handle_colorDC_ = CreateCompatibleDC(NULL);

	return true;
}

bool PPlayer::Frame()
{
	return true;
}

bool PPlayer::Render()
{

	//PRectObject::Render(); 
	
	HBITMAP bitmap = CreateCompatibleBitmap(g_handle_screenDC, rect_.right, rect_.bottom);
	if (bitmap == NULL)
		return false;
	SelectObject(handle_colorDC_, bitmap);

	HBITMAP bitmap2 = CreateCompatibleBitmap(g_handle_screenDC, rect_.right, rect_.bottom);
	if (bitmap == NULL)
		return false;

	SelectObject(handle_maskDC_, bitmap);

	HBRUSH handle_white_brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(handle_colorDC_, handle_white_brush);
	HBRUSH handle_white_brush2 = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(handle_maskDC_, handle_white_brush2);
	PatBlt(handle_colorDC_, 0, 0, rect_.right, rect_.bottom, PATCOPY);
	PatBlt(handle_maskDC_, 0, 0, rect_.right, rect_.bottom, PATCOPY);
	DeleteObject(handle_white_brush);
	DeleteObject(handle_white_brush2);

	BitBlt(handle_colorDC_, 0, 0, rect_.right, rect_.bottom, bitmap_->handle_memoryDC_, rect_.left, rect_.top, SRCCOPY);
	BitBlt(handle_maskDC_, 0, 0, rect_.right, rect_.bottom,
		bitmap_mask_->handle_memoryDC_, rect_.left, rect_.top, SRCCOPY);

	/*BitBlt(g_handle_off_screenDC, 0, 0, rect_.right, rect_.bottom,
		bitmap_mask_->handle_memoryDC_, rect_.left, rect_.top, SRCCOPY);*/
	//AlphaBlendRender(rect_.right, rect_.bottom, g_handle_off_screenDC, handle_colorDC_, handle_maskDC_, 1.0f);
	
	return true;
}

bool PPlayer::Release()
{
	PRectObject::Release();
	DeleteDC(handle_maskDC_);
	DeleteDC(handle_colorDC_);
	return false;
}
