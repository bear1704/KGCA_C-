#include "PRectObject.h"
#include "PSpriteManager.h"
#include "PCharacterDataManager.h"
#pragma once

//struct PRectObjectStat
//{
//	pPoint position_;
//	RECT collision_box_;
//	float move_speed_;
//	multibyte_string object_data_path_;
//	multibyte_string object_name_;
//	multibyte_string sprite_path_;
//	multibyte_string sprite_name_;
//	float alpha_;
//	float scale_;
//
//	PRectObjectStat() {}
//	PRectObjectStat(pPoint position, RECT collision_box, float move_speed, multibyte_string object_data_path, multibyte_string object_name,
//		multibyte_string sprite_path, multibyte_string sprite_name, float alpha, float scale)
//	{
//		position_ = position;
//		collision_box_ = collision_box;
//		move_speed_ = move_speed;
//		object_data_path_ = object_data_path;
//		object_name_ = object_name;
//		sprite_path_ = sprite_path;
//		sprite_name_ = sprite_name;
//		alpha_ = alpha;
//		scale_ = scale;
//	}
//
//};
//


class PCharacter : public PRectObject
{
public:
	PCharacter();
	PCharacter(float x, float y, multibyte_string character_name);
	~PCharacter();

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
protected:
	multibyte_string character_name_;
	float move_speed_;
public:
	void Movement();
	void Set(pPoint position, multibyte_string data_path, multibyte_string character_name, 
		multibyte_string sprite_path, multibyte_string sprite_name, float alpha, float scale);

};

/*
PBitmap* bitmap_;
	PBitmap* bitmap_mask_;
	pPoint position_;
	float move_speed_;
	RECT collision_box_;
*/

