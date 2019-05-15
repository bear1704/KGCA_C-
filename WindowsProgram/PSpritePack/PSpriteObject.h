#pragma once
#include "PSprite.h"

class PSpriteObject
{
public:
	PSpriteObject();
	virtual ~PSpriteObject();
protected:
	PSprite* sprite_;
	PSprite* sprite_mask_;
	vector<RECT> rectlist;
	int number_of_max_spriteframe_;
	int current_played_spriteframe_;
	float remain_lifetime_;
	int sprite_id_;
	float time_after_birth_;
	pPoint position_;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	bool Load(std::wstring filename);

	virtual void Set(float x, float y, vector<RECT> rectlist, float remain_lifetime, int sprite_id);


	//bool Load(std::wstring filename);
};

