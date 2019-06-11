#pragma once
#include "PBitmapManager.h"
#include "PStd.h"

struct SpriteDataInfo
{
	std::vector<FLOAT_RECT> rect_list;
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

class PSprite
{
public:
	PSprite();
	~PSprite();

private:

	vector<FLOAT_RECT> rect_list;
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
	pPoint position_;

public:
	PBitmap* bitmap_;
	PBitmap* bitmap_mask_;
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(std::wstring filename);
	bool Set(SpriteDataInfo info, float alpha, float scale);
	bool SetPosition(float x, float y);
	void Play();
	void Draw();
	//void Draw(int x, int y);
	bool Alpha24BitsDraw(PSprite sprite, float alpha, float scale, HDC colorDC = NULL, HDC maskDC = NULL);
	void set_alpha_(float alpha);
	PBitmap* get_bitmap_();
	PBitmap* get_bitmap_mask_();
	vector<FLOAT_RECT> get_rect_list_copy();
	pPoint get_position_();
	void set_current_played_spriteframe_(int current);

};

