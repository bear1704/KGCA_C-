#pragma once
#include "PBitmapManager.h"

struct SpriteDataInfo
{
	std::vector<RECT> rect_list;
	std::wstring bitmap_path;
	int max_frame;
	float lifetime;
	float once_playtime;
	float posX;
	float posY;

	SpriteDataInfo()
	{
		posX = 100.0f;
		posY = 100.0f;
	}
};

class PSprite
{
public:
	PSprite();
	~PSprite();

private:
	PBitmap* sprite_;
	PBitmap* sprite_mask_;
	vector<RECT> rect_list;
	int number_of_max_spriteframe_;
	int current_played_spriteframe_;
	float lifetime_;
	float remain_lifetime_;
	float allocatetime_for_onesprite;
	int sprite_id_;
	float time_after_spriteopen_;
	pPoint position_;
	bool isDead;


public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(std::wstring filename);
	bool Set(SpriteDataInfo info);
	bool SetPosition(float x, float y);
	void Play();
	

	// bool Draw(); //(¿¹Á¤)


};

