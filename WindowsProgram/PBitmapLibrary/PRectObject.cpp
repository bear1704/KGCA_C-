#include "PRectObject.h"
#include "PBitmapManager.h"


PRectObject::PRectObject()
{
}


PRectObject::~PRectObject()
{
}

bool PRectObject::Init()
{
	return true;
}

bool PRectObject::Frame()
{
	return true;
}

bool PRectObject::Render()
{
	if (bitmap_mask_ != nullptr)
	{
		bitmap_mask_->Draw(position_.x, position_.y, rect_, SRCAND);
		bitmap_->Draw(position_.x, position_.y, rect_, SRCINVERT);
		bitmap_mask_->Draw(position_.x, position_.y, rect_, SRCINVERT);
	}
	else
	{
		bitmap_->Draw(position_.x, position_.y, rect_, SRCCOPY);
	}
	return true;
}

bool PRectObject::Release()
{
	bitmap_->Release();
	bitmap_mask_->Release();
	return true;
}

void PRectObject::Set(float x, float y, RECT rect, float fSpeed)
{
	position_.x = x;
	position_.y = y;
	rect_ = rect;
	moveSpeed_ = fSpeed;
}

void PRectObject::Set(pPoint p, RECT rect, float fSpeed)
{
	position_ = p;
	rect_ = rect;
	moveSpeed_ = fSpeed;
}

void PRectObject::Set(PRectObjectStat stat)
{
	position_ = stat.position;
	moveSpeed_ = stat.moveSpeed;
	rect_ = stat.rect;
}

bool PRectObject::Load(std::wstring filename)
{
	int key = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAP);
	if (key != -1)
		bitmap_ = PBitmapManager::GetInstance().get_bitmap_from_map(key);
	
	int key_mask = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAPMASK);
	if (key_mask != -1)
		bitmap_mask_ = PBitmapManager::GetInstance().get_bitmap_from_map(key_mask);

	return true;
}
