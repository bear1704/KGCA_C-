#include "PRectObject.h"
#include "PSpriteManager.h"
#include "PCharacterDataManager.h"

#pragma once

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
public:
	void Movement();

};

/*
PBitmap* bitmap_;
	PBitmap* bitmap_mask_;
	pPoint position_;
	float move_speed_;
	RECT collision_box_;
*/

