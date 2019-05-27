#include "PRectObject.h"
#include "PSpriteManager.h"
#include "PCharacterDataManager.h"

#pragma once

class PCharacter : public PRectObject
{
public:
	PCharacter();
	PCharacter(float x, float y);
	~PCharacter();

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
protected:
	PSprite sprite_character_;
	void Movement();
	float scale_;
private:
public:
	float get_scale_();


};

