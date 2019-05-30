#pragma once
#include "PBitmap.h"
#include "PCollision.h"
#include "PSprite.h"

struct PRectObjectStat
{
	pPoint position;
	RECT collision_box;
	float alpha;
	float scale;

	PRectObjectStat() {}
	PRectObjectStat(pPoint position, RECT collision_box, float alpha, float scale)
	{
		this->position = position;
		this->collision_box = collision_box;
		this->alpha = alpha;
		this->scale = scale;
	}

};

class PRectObject
{
public:
	PRectObject();
	virtual ~PRectObject();
protected:
	PSprite sprite_;
	pPoint position_;
	RECT collision_box_;
	RECT collision_box_norm_;
	float rotate_speed_;
	float alpha_;
	float scale_;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	virtual void Set(pPoint positoin, RECT collision_box, float alpha, float scale);
	virtual void Set(PRectObjectStat stat);
	PBitmap* get_bitmap_();
	PBitmap* get_bitmap_mask_();
	PSprite* get_sprite_();
	pPoint get_position_();
	float* get_position_xy(PXY axis);
	RECT get_collision_rect_();
	float get_moveSpeed_();
	//bool Load(std::wstring filename);
	void set_collision_box_(RECT input_box);
	float get_scale_();


};

