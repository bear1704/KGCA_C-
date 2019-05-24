#include "PSprite.h"



PSprite::PSprite()
{
	isDead = false;
}


PSprite::~PSprite()
{
}

bool PSprite::Init()
{
	return false;
}

bool PSprite::Frame()
{
	remain_lifetime_ -= g_SecondPerFrame;
	
	if (remain_lifetime_ <= 0) isDead = true;
	if (isDead == true) return true;

	time_after_spriteopen_ += g_SecondPerFrame;
	if (time_after_spriteopen_ > allocatetime_for_onesprite)
	{
		current_played_spriteframe_++;
		if (current_played_spriteframe_ >= number_of_max_spriteframe_)
		{
			current_played_spriteframe_ = 0;
		}
		time_after_spriteopen_ = 0;
	}

	return true;
}

bool PSprite::Render()
{
	if (bitmap_mask_ != nullptr)
	{
		bitmap_mask_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCAND);
		bitmap_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCINVERT);
		bitmap_mask_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCINVERT);
	}
	else
	{
		bitmap_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCCOPY);
	}
	return true;
}

bool PSprite::Release()
{
	return false;
}

bool PSprite::Load(std::wstring filename)
{
	int key = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAP);
	if (key != -1)
		bitmap_ = PBitmapManager::GetInstance().get_bitmap_from_map(key);

	int key_mask = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAPMASK);
	if (key_mask != -1)
		bitmap_mask_= PBitmapManager::GetInstance().get_bitmap_from_map(key_mask);

	return true;
}

bool PSprite::Set(SpriteDataInfo info)
{
	rect_list = info.rect_list;
	remain_lifetime_ = info.lifetime;
	lifetime_ = info.lifetime;
	position_.x = info.posX;
	position_.y = info.posY;
	number_of_max_spriteframe_ = info.max_frame;
	allocatetime_for_onesprite = info.once_playtime / info.max_frame;
	Load(info.bitmap_path);

	return true;
}

bool PSprite::SetPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	return false;
}

void PSprite::Play()
{
	isDead = false;
	remain_lifetime_ = lifetime_;
}

void PSprite::Draw(DWORD drawmode)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 0xff;
	if (bitmap_->bitmap_info.bmBitsPixel == 32) //ARGB �̹���
	{
		bf.AlphaFormat = AC_SRC_ALPHA;
		bitmap_->Draw(position_.x, position_.y,
			rect_list[current_played_spriteframe_], bf);
	}
	else // RGB �̹���
	{
		bf.AlphaFormat = AC_SRC_OVER;
		if (bitmap_mask_ != nullptr)
		{
		/*	bitmap_mask_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCAND);
			bitmap_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCINVERT);
			bitmap_mask_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCINVERT);*/
			Alpha24BitsDraw(*this, 0.7f);
		}
		else
		{
			bitmap_->Draw(position_.x, position_.y,
				rect_list[current_played_spriteframe_], drawmode);
		}
	}
}
void  PSprite::Draw(int x, int y, DWORD drawmode)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = alpha_;
	if (bitmap_->bitmap_info.bmBitsPixel == 32) //ARGB �̹���
	{
		bf.AlphaFormat = AC_SRC_ALPHA;
		bitmap_->Draw(x, y,
			rect_list[current_played_spriteframe_], bf);
	}
	else // RGB �̹���
	{
		bf.AlphaFormat = AC_SRC_OVER;
		if (bitmap_mask_ != nullptr)
		{
			bitmap_mask_->Draw(x, y, rect_list.at(current_played_spriteframe_), SRCAND);
			bitmap_->Draw(x, y, rect_list.at(current_played_spriteframe_), SRCINVERT);
			bitmap_mask_->Draw(x, y, rect_list.at(current_played_spriteframe_), SRCINVERT);
		}
		else
		{
			bitmap_->Draw(x, y,
				rect_list[current_played_spriteframe_], drawmode);
		}
	}
}


void PSprite::DrawCenter(DWORD drawmode)
{
	RECT rt = rect_list[current_played_spriteframe_];
	rt.left = position_.x - (rt.right / 2);
	rt.top = position_.y - (rt.bottom / 2);
	bitmap_->Draw(rt.left, rt.top,
		rect_list[current_played_spriteframe_],drawmode);
}

bool PSprite::Alpha24BitsDraw(PSprite sprite, float alpha)
{
	//����! ��ǥ(sprite_coord.txt����)���� ���� ����� left, top, right, bottom�� �ƴ϶�  left, right-left, top, bottom-top ��! abs
	int sprite_width =sprite.rect_list[current_played_spriteframe_].right;
	int sprite_height = sprite.rect_list[current_played_spriteframe_].bottom;
	RECT rectangle_client;
	GetClientRect(g_hWnd, &rectangle_client);

	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = sprite_width;
	bmi.bmiHeader.biHeight = sprite_height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = sprite_width * sprite_height * 4;

	void* pivot_bitmap = 0;
	void* pivot_mask_bitmap = 0;
	void* pivot_offscreen_bitmap = 0;

	HBITMAP handle_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &pivot_bitmap, NULL, 0);
	HDC bitmap_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_dc, handle_bitmap);
	BitBlt(bitmap_dc, 0, 0, sprite_width, sprite_height, sprite.get_bitmap_()->handle_memoryDC_,
		sprite.rect_list[current_played_spriteframe_].left, sprite.rect_list[current_played_spriteframe_].top, SRCCOPY);
	DeleteDC(bitmap_dc);

	HBITMAP handle_mask_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &pivot_mask_bitmap, NULL, 0);
	HDC bitmap_mask_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_mask_dc, handle_mask_bitmap);
	BitBlt(bitmap_mask_dc, 0, 0, sprite_width, sprite_height, sprite.get_bitmap_mask_()->handle_memoryDC_,
		sprite.rect_list[current_played_spriteframe_].left, sprite.rect_list[current_played_spriteframe_].top, SRCCOPY);
	DeleteDC(bitmap_mask_dc);

	HBITMAP handle_offscreen_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &pivot_offscreen_bitmap, NULL, 0);
	HDC bitmap_offscreen_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_offscreen_dc, handle_offscreen_bitmap);
	BitBlt(bitmap_offscreen_dc, 0, 0, sprite_width, sprite_height, g_handle_off_screenDC,
		sprite.position_.x, sprite.position_.y, SRCCOPY); //������ �ٸ�, ����!
	DeleteDC(bitmap_offscreen_dc);

	for (int y = 0; y < sprite_height; y++)
	{
		byte* bitmap_RGB = (byte*)&((DWORD*)pivot_bitmap)[y * sprite_width];
		byte* bitmap_mask_RGB = (byte*)&((DWORD*)pivot_mask_bitmap)[y* sprite_width];
		byte* bitmap_offscreen_RGB = (byte*)&((DWORD*)pivot_offscreen_bitmap)[y* sprite_width];

		for (int x = 0; x < sprite_width; x++)
		{
			byte origin_A = bitmap_RGB[3];
			byte origin_R = bitmap_RGB[2];
			byte origin_G = bitmap_RGB[1];
			byte origin_B = bitmap_RGB[0];

			if (bitmap_mask_RGB[0] == 255 && bitmap_mask_RGB[1] == 255 && bitmap_mask_RGB[2] == 255)
			{    //����ũRGB�� WHITE�� ���, ������� ó��
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

	SetStretchBltMode(g_handle_off_screenDC, HALFTONE);
	StretchBlt(g_handle_off_screenDC,
		sprite.position_.x, sprite.position_.y, sprite_width, sprite_height,
		bitmap_dc, 0, 0, sprite_width, sprite_height,
		SRCCOPY);

	DeleteObject(handle_bitmap);
	DeleteObject(handle_mask_bitmap);
	DeleteObject(handle_offscreen_bitmap);
	DeleteObject(bitmap_dc);

	return true;
}

