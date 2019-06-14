#include "PRectObject.h"
#pragma once


class PCharacter : public PRectObject
{
public:
	PCharacter();
	~PCharacter();

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual void StatusSet(multibyte_string status_path, multibyte_string object_name);
protected:
	multibyte_string character_name_;
	FLOAT_RECT foot_plane_;
	float move_speed_;	
	pPoint prev_position_;
	bool is_ground;

public:
	void Movement();
	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
	void set_collision_box_(FLOAT_RECT norm_box);
	FLOAT_RECT get_foot_plane_box();
	void PlatformWallCollision();
	void SavePrevPosition();

};
