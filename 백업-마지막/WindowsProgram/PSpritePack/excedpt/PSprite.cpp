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
	if (sprite_mask_ != nullptr)
	{
		sprite_mask_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCAND);
		sprite_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCINVERT);
		sprite_mask_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCINVERT);
	}
	else
	{
		sprite_->Draw(position_.x, position_.y, rect_list.at(current_played_spriteframe_), SRCCOPY);
	}
	return true;
}

bool PSprite::Load(std::wstring filename)
{
	int key = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAP);
	if (key != -1)
		sprite_ = PBitmapManager::GetInstance().get_bitmap_from_map(key);

	int key_mask = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAPMASK);
	if (key_mask != -1)
		sprite_mask_= PBitmapManager::GetInstance().get_bitmap_from_map(key_mask);

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


