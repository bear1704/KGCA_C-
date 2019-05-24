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
	//handle_bitmap_ = (HBITMAP)LoadImage(g_hInstance,
	//	filename.c_str(), IMAGE_BITMAP,
	//	0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	//if (handle_bitmap_ == NULL) return false;

	HANDLE hFile = CreateFile(filename.c_str(),
		GENERIC_READ, 0,
		NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	BITMAPFILEHEADER m_bitFileHeader;
	DWORD dwRead;
	ReadFile(hFile, &m_bitFileHeader,
		sizeof(BITMAPFILEHEADER), &dwRead, NULL);

	DWORD dwDataSize;
	dwDataSize = m_bitFileHeader.bfOffBits -
		sizeof(BITMAPFILEHEADER);
	BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(dwDataSize);
	ReadFile(hFile, bitInfo,
		dwDataSize, &dwRead, NULL);

	PVOID pRaster = nullptr;
	handle_bitmap_ = CreateDIBSection(
		g_handle_screenDC, bitInfo, DIB_RGB_COLORS, &pRaster, NULL, 0);
	ReadFile(hFile, pRaster,
		m_bitFileHeader.bfSize - m_bitFileHeader.bfOffBits,
		&dwRead, NULL);
	free(bitInfo);
	CloseHandle(hFile);

	// BITMAPFILEHEADER 
	// BITMAPINFO
	//    BITMAPFILEHEADER
	//    RGB...
	// PIXELDATA

	/*m_hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		filename.c_str(),
		IMAGE_BITMAP,
		0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (m_hBitmap == NULL) return false;*/


	handle_memoryDC_ = CreateCompatibleDC(g_handle_screenDC);
	SelectObject(handle_memoryDC_, handle_bitmap_);

	GetObject(handle_bitmap_, sizeof(BITMAP), &bitmap_info);

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

bool PBitmap::Draw(float x, float y, RECT rect, BLENDFUNCTION bf)
{
	AlphaBlend(g_handle_off_screenDC, x, y,
		rect.right, rect.bottom, handle_memoryDC_, rect.left, rect.top, rect.right, rect.bottom,
		bf);
	return true;
}

bool PBitmap::DrawColorKey(float x, float y, RECT rect, COLORREF key_color)
{
	TransparentBlt(
		g_handle_off_screenDC, x, y, rect.right, rect.bottom, handle_memoryDC_, rect.left, rect.top,
		rect.right, rect.bottom, key_color);

	return true;
}

