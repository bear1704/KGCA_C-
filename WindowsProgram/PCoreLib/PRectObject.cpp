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
		bitmap_mask_->Draw(position_.x, position_.y, collision_box_, SRCAND);
		bitmap_->Draw(position_.x, position_.y, collision_box_, SRCINVERT);
		bitmap_mask_->Draw(position_.x, position_.y, collision_box_, SRCINVERT);
	}
	else
	{
		bitmap_->Draw(position_.x, position_.y, collision_box_, SRCCOPY);
	}

	return true;
}

bool PRectObject::Release()
{
	if (!bitmap_)
	{
		bitmap_->Release();
		delete bitmap_;
	}
	if (!bitmap_mask_)
	{
		bitmap_mask_->Release();
		delete bitmap_mask_;
	}
	
	return true;
}

void PRectObject::Set(float x, float y, RECT rect, float fSpeed)
{
	position_.x = x;
	position_.y = y;
	collision_box_ = rect;
	move_speed_ = fSpeed;
}

void PRectObject::Set(pPoint p, RECT rect, float fSpeed)
{
	position_ = p;
	collision_box_ = rect;
	move_speed_ = fSpeed;
}

void PRectObject::Set(PRectObjectStat stat)
{
	position_ = stat.position_;
	move_speed_ = stat.move_speed_;
	collision_box_ = stat.collision_box_;
}

PBitmap * PRectObject::get_bitmap_()
{
	return bitmap_;
}

PBitmap * PRectObject::get_bitmap_mask_()
{
	return bitmap_mask_;
}

pPoint PRectObject::get_position_()
{
	return position_;
}

float * PRectObject::get_position_xy(PXY axis)
{
	if (axis == PXY::X)
		return &position_.x;
	else if (axis == PXY::Y)
		return &position_.y;

	return nullptr;
}


RECT PRectObject::get_collision_rect_()
{
	return collision_box_;
}

float PRectObject::get_moveSpeed_()
{
	return move_speed_;
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
