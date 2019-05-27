#include "PSprite.h"



PSprite::PSprite()
{
	isDead = false;
	alpha_ = 1.0f;
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

bool PSprite::Set(SpriteDataInfo info, float alpha, float scale = 1.0f)
{
	rect_list = info.rect_list;
	remain_lifetime_ = info.lifetime;
	lifetime_ = info.lifetime;
	position_.x = info.posX;
	position_.y = info.posY;
	number_of_max_spriteframe_ = info.max_frame;
	allocatetime_for_onesprite = info.once_playtime / info.max_frame;
	alpha_ = alpha;
	scale_ = scale;

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

void PSprite::Draw()
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = alpha_ * 255.f;
	if (bitmap_->bitmap_info.bmBitsPixel == 32) //ARGB 이미지
	{
		bf.AlphaFormat = AC_SRC_ALPHA;
		bitmap_->Draw(position_.x, position_.y,
			rect_list[current_played_spriteframe_], bf, scale_);
	}
	else // RGB 이미지
	{
		bf.AlphaFormat = AC_SRC_OVER;
		if (bitmap_mask_ != nullptr)
		{
			Alpha24BitsDraw(*this, alpha_, scale_);
		}
		else
		{
			bitmap_->Draw(position_.x, position_.y,
				rect_list[current_played_spriteframe_], SRCCOPY, scale_);
		}
	}
}
void  PSprite::Draw(int x, int y)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = alpha_;
	if (bitmap_->bitmap_info.bmBitsPixel == 32) //ARGB 이미지
	{
		bf.AlphaFormat = AC_SRC_ALPHA;
		bitmap_->Draw(x, y,
			rect_list[current_played_spriteframe_], bf);
	}
	else // RGB 이미지
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
				rect_list[current_played_spriteframe_], SRCCOPY);
		}
	}
}


void PSprite::DrawCenter()
{
	RECT rt = rect_list[current_played_spriteframe_];
	rt.left = position_.x - (rt.right / 2);
	rt.top = position_.y - (rt.bottom / 2);
	bitmap_->Draw(rt.left, rt.top,
		rect_list[current_played_spriteframe_], SRCCOPY);
}

bool PSprite::Alpha24BitsDraw(PSprite sprite, float alpha, float scale)
{
	//주의! 좌표(sprite_coord.txt같은)에서 쓰는 방법은 left, top, right, bottom이 아니라  left, right-left, top, bottom-top 임! abs
	int sprite_width = sprite.rect_list[current_played_spriteframe_].right;
	int sprite_height = sprite.rect_list[current_played_spriteframe_].bottom;
	int stretched_width = sprite.rect_list[current_played_spriteframe_].right * scale; 
	int stretched_height = sprite.rect_list[current_played_spriteframe_].bottom * scale;
	float half_width = stretched_width / 2;
	float half_height = stretched_height / 2;

	RECT rectangle_client;
	GetClientRect(g_hWnd, &rectangle_client);

	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = stretched_width;
	bmi.bmiHeader.biHeight = stretched_height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = stretched_width * stretched_height * 4;

	void* pivot_bitmap = 0;
	void* pivot_mask_bitmap = 0;
	void* pivot_offscreen_bitmap = 0;

	HBITMAP handle_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &pivot_bitmap, NULL, 0);
	HDC bitmap_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_dc, handle_bitmap);
	/*BitBlt(bitmap_dc, 0, 0, sprite_width, sprite_height, sprite.get_bitmap_()->handle_memoryDC_,
		sprite.rect_list[current_played_spriteframe_].left, sprite.rect_list[current_played_spriteframe_].top, SRCCOPY);*/
	StretchBlt(bitmap_dc, 0, 0, stretched_width, stretched_height, sprite.get_bitmap_()->handle_memoryDC_,
		sprite.rect_list[current_played_spriteframe_].left, sprite.rect_list[current_played_spriteframe_].top,
		sprite_width, sprite_height, SRCCOPY);
	DeleteDC(bitmap_dc);

	HBITMAP handle_mask_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &pivot_mask_bitmap, NULL, 0);
	HDC bitmap_mask_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_mask_dc, handle_mask_bitmap);
	/*BitBlt(bitmap_mask_dc, 0, 0, sprite_width, sprite_height, sprite.get_bitmap_mask_()->handle_memoryDC_,
		sprite.rect_list[current_played_spriteframe_].left, sprite.rect_list[current_played_spriteframe_].top, SRCCOPY);*/
	StretchBlt(bitmap_mask_dc, 0, 0, stretched_width, stretched_height, sprite.get_bitmap_mask_()->handle_memoryDC_,
		sprite.rect_list[current_played_spriteframe_].left, sprite.rect_list[current_played_spriteframe_].top,
		sprite_width, sprite_height, SRCCOPY);
	DeleteDC(bitmap_mask_dc);

	HBITMAP handle_offscreen_bitmap = CreateDIBSection(g_handle_screenDC, &bmi, DIB_RGB_COLORS, &pivot_offscreen_bitmap, NULL, 0);
	HDC bitmap_offscreen_dc = CreateCompatibleDC(NULL);
	SelectObject(bitmap_offscreen_dc, handle_offscreen_bitmap);
	//BitBlt(bitmap_offscreen_dc, 0, 0, sprite_width, sprite_height, g_handle_off_screenDC,
	//	sprite.position_.x, sprite.position_.y, SRCCOPY); //원본과 다름, 주의!
	StretchBlt(bitmap_offscreen_dc, 0, 0, stretched_width, stretched_height, g_handle_off_screenDC,
		sprite.position_.x - half_width, sprite.position_.y - half_height, stretched_width, stretched_height, SRCCOPY);
	//배경은 늘어난 크기만큼 잘라와 줘야 한다. 또한 센터 출력이므로 센터 - RECT/2만큼의 위치부터 가져와야 한다. 
	DeleteDC(bitmap_offscreen_dc);

	for (int y = 0; y < stretched_height; y++)
	{
		byte* bitmap_RGB = (byte*)&((DWORD*)pivot_bitmap)[y * stretched_width];
		byte* bitmap_mask_RGB = (byte*)&((DWORD*)pivot_mask_bitmap)[y* stretched_width];
		byte* bitmap_offscreen_RGB = (byte*)&((DWORD*)pivot_offscreen_bitmap)[y* stretched_width];

		for (int x = 0; x < stretched_width; x++)
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

	SetStretchBltMode(g_handle_off_screenDC, HALFTONE);
	StretchBlt(g_handle_off_screenDC,
		sprite.position_.x - half_width, sprite.position_.y - half_height , stretched_width, stretched_height,
		bitmap_dc, 0, 0, stretched_width, stretched_height,
		SRCCOPY);

	DeleteObject(handle_bitmap);
	DeleteObject(handle_mask_bitmap);
	DeleteObject(handle_offscreen_bitmap);
	DeleteObject(bitmap_dc);

	return true;
}

void PSprite::set_alpha_(float alpha)
{
	alpha_ = alpha;
}

