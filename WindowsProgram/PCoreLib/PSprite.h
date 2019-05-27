#pragma once
#include "PBitmapManager.h"
#include "PRectObject.h"

struct SpriteDataInfo
{
	std::vector<RECT> rect_list;
	std::wstring bitmap_path;
	int max_frame;
	float lifetime;
	float once_playtime;
	float posX;
	float posY;
	float scale;

	SpriteDataInfo()
	{
		posX = 100.0f;
		posY = 100.0f;
		scale = 1.0f;
	}
};

class PSprite : public PRectObject
{
public:
	PSprite();
	~PSprite();

private:
	vector<RECT> rect_list;
	int number_of_max_spriteframe_;
	int current_played_spriteframe_;
	float lifetime_;
	float remain_lifetime_;
	float allocatetime_for_onesprite;
	int sprite_id_;
	float time_after_spriteopen_;
	bool isDead;
	float alpha_;
	float scale_;


public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(std::wstring filename);
	bool Set(SpriteDataInfo info, float alpha, float scale);
	bool SetPosition(float x, float y);
	void Play();
	void Draw();
	void Draw(int x, int y);
	bool Alpha24BitsDraw(PSprite sprite, float alpha, float scale);
	void set_alpha_(float alpha);


};

