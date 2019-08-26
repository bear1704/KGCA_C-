#pragma once
#include "PBitmapManager.h"
#include "PStd.h"
#include <assert.h>
#include "P2DCamera.h"
#include "PTexture.h"
#include "PDxHelper.h"


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


	PTexture* texture_;
	

	//renewel
	vector<DX::PTextureBufSet> tex_boundary_list_;
	vector<DX::PTextureBufSet> tex_default_boundary_list_;
	pPoint position_;
	int number_of_max_spriteframe_;
	int current_played_spriteframe_;
	float lifetime_;
	float remain_lifetime_;
	float allocatetime_for_onesprite;
	float time_after_spriteopen_;
	bool isDead;
	float alpha_;
	float scale_;
	ANIMATIONTYPE animation_type_;
	bool automata_;
	bool is_reversal_for_automata_;//reversal 상태인지 스프라이트가 원래는 알 필요 없지만, 특수 상황(1회용 스프라이트 제작 등..)에서 필요하므로 넣는다.
							//1회용 스프라이트를 제작할 땐 꼭 설정해야함
	bool is_dmg_; //데미지를 표시하는 스프라이트인지 체크



public:

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(std::wstring filename);
	bool Set(SpriteDataInfo info, float alpha, float scale);
	bool SetPosition(float x, float y);
	void Play();
	void Draw(ID3D11Device* device ,DX::PTextureBufSet& bufset ,DX::PVertex* vertices ,int vertices_count, DX::PDxHelper& helper, bool is_reversal);
	void Clone(PSprite* sprite, float alpha, float scale);
	void AutomataClone(PSprite* sprite, float alpha, float scale, bool is_reversal, pPoint position);
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
	void set_is_dmg(bool isdmg);
	vector<FLOAT_RECT>& get_original_size_list();
	ANIMATIONTYPE get_animation_type_();
	float get_remain_lifetime_();
	float get_lifetime_();
	float get_alpha_();
	int get_max_sprite_number();
	int get_current_played_frame();
	float get_allocatetime_for_onesprite();
	bool get_is_dmg();
	
};

