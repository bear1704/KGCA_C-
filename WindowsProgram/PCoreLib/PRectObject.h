#pragma once
#include "PBitmap.h"
#include "PCollision.h"
#include "PSpriteManager.h"
#include "PObjectDataManager.h"
#include "PPhysicsModule.h"
#include "P2DCamera.h"

class PRectObject
{
public:
	PRectObject();
	virtual ~PRectObject();
protected:
	PSprite sprite_;
	pPoint position_;
	DOUBLE_RECT collision_box_;
	DOUBLE_RECT collision_box_norm_;
	float alpha_;
	float scale_;
	multibyte_string object_name_;
	PPhysicsModule physics_;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	virtual void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
	PBitmap* get_bitmap_();
	PBitmap* get_bitmap_mask_();
	PSprite* get_sprite_();
	pPoint get_position_();
	void set_position_(pPoint XY);
	DOUBLE_RECT get_collision_rect_();
	DOUBLE_RECT get_collision_rect_norm_();
	//bool Load(std::wstring filename);
	void set_collision_box_(DOUBLE_RECT norm_box);
	float get_scale_();
	void Spawn();


};