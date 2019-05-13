#include "PRectObject.h"



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
	pbitmap_bitmap_.Draw(position_.x, position_.y, rect_);
	return true;
}

bool PRectObject::Release()
{
	pbitmap_bitmap_.Release();
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
	pbitmap_bitmap_.Load(filename);
	return false;
}
