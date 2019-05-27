#pragma once
#include "PBitmap.h"

struct PRectObjectStat
{
	pPoint position_;
	RECT collision_box_;
	float move_speed_;
	PRectObjectStat() {}
	PRectObjectStat(pPoint position, RECT collision_box, float move_speed = 0.0f)
	{
		position_ = position;
		collision_box_ = collision_box;
		move_speed_ = move_speed;
	}

};

class PRectObject
{
public:
	PRectObject();
	virtual ~PRectObject();
protected:
	PBitmap* bitmap_;
	PBitmap* bitmap_mask_;
	pPoint position_;
	float move_speed_;
	RECT collision_box_;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	virtual void Set(float x, float y, RECT rect, float fSpeed);
	virtual void Set(pPoint p, RECT rect, float fSpeed);
	virtual void Set(PRectObjectStat stat);
	PBitmap* get_bitmap_();
	PBitmap* get_bitmap_mask_();
	pPoint get_position_();
	float* get_position_xy(PXY axis);
	RECT get_collision_rect_();
	float get_moveSpeed_();
	bool Load(std::wstring filename);

};

