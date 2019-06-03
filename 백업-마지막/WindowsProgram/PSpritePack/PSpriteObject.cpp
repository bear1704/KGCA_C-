#include "PSpriteObject.h"


//
//PSpriteObject::PSpriteObject()
//{
//}
//
//
//PSpriteObject::~PSpriteObject()
//{
//}
//
//bool PSpriteObject::Render()
//{
//	if (sprite_mask_ != nullptr)
//	{
//		sprite_mask_->Draw(position_.x, position_.y, rectlist[current_played_spriteframe_], SRCAND);
//		sprite_->Draw(position_.x, position_.y, rectlist[current_played_spriteframe_], SRCINVERT);
//		sprite_mask_->Draw(position_.x, position_.y, rectlist[current_played_spriteframe_], SRCINVERT);
//	}
//	else
//	{
//		sprite_->Draw(position_.x, position_.y, rectlist[current_played_spriteframe_], SRCCOPY);
//	}
//	return true;
//}
//
//bool PSpriteObject::Load(std::wstring filename)
//{
//	int key = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAP);
//	if (key != -1)
//		sprite_->sprite_ = PBitmapManager::GetInstance().get_bitmap_from_map(key);
//
//	int key_mask = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAPMASK);
//	if (key_mask != -1)
//		sprite_mask_->sprite_ = PBitmapManager::GetInstance().get_bitmap_from_map(key_mask);
//
//	return true;
//}
