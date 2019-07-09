#pragma once
#include "PBitmapManager.h"
#include "PStd.h"
#include <assert.h>

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
	vector<FLOAT_RECT> original_size_list;
	int number_of_max_spriteframe_;
	int current_played_spriteframe_;
	float lifetime_;
	float remain_lifetime_;
	float allocatetime_for_onesprite;
	float time_after_spriteopen_;
	bool isDead;
	float alpha_;
	float scale_;
	pPoint position_;
	ANIMATIONTYPE animation_type_;


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
	void Draw(bool is_reversal);
	void Clone(PSprite* sprite, float alpha, float scale);
	//void Draw(int x, int y);
	bool Alpha24BitsDraw(PSprite sprite, float alpha, float scale, HDC colorDC = NULL, HDC maskDC = NULL);
	void AlphaDrawNotCenter();
	PBitmap* get_bitmap_();
	PBitmap* get_bitmap_mask_();
	pPoint get_position_();
	vector<FLOAT_RECT> get_rect_list_copy();
	bool get_is_dead_();
	float get_scale();
	void set_alpha_(float alpha);
	void set_scale_(float scale);
	void set_current_played_spriteframe_(int current);
	void set_rect_list_size(FLOAT_RECT size);
	void set_animation_type_(ANIMATIONTYPE type);
	vector<FLOAT_RECT>& get_original_size_list();
	ANIMATIONTYPE get_animation_type_();
	float get_remain_lifetime_();
	float get_lifetime_();
	float get_alpha_();
	int get_max_sprite_number();
	int get_current_played_frame();
	float get_allocatetime_for_onesprite();
	
};

