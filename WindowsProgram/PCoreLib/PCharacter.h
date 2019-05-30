#include "PRectObject.h"
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
	float move_speed_;	
	float gravity_;
public:
	void Movement();
	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
	void SetGravity(float gravity);

};
