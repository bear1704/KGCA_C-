#pragma once
#include <assert.h>
#include "PTextureManager.h"
#include "PStd.h"
#include "PTexture.h"
#include "PDxHelper.h"
#include "PModel.h"
//#include "P2DCamera.h"

const int kPlaneVertexNumber = 4;

struct EffectInfo
{
	int x_count;
	int y_count;
	float x_offset;
	float y_offset;
	float x_init;
	float y_init;
	float tex_width = 0.0f;
	float tex_height = 0.0f;
	bool is_multi_texture; //멀티텍스쳐를 사용하는 스프라이트인지
	bool is_effect_sprite; //이펙트 툴에 사용되는 스프라이트인지, 일반 스프라이트인지?

	EffectInfo()
	{
		x_count = 0;
		y_count = 0;
		x_offset = 0.0f;
		y_offset = 0.0f;
		x_init = 0.0f;
		y_init = 0.0f;
		tex_width = 0.0f;
		tex_height = 0.0f;
		is_multi_texture = false;
		is_effect_sprite = false;
	}
};


struct SpriteDataInfo
{
	vector<DX::PTex_uv4> tex_boundary_list;
	std::vector<PTexture*> texture_list;
	std::wstring texture_name;
	int max_frame;
	float lifetime;
	float once_playtime;
	float posX;
	float posY;
	float scale;
	EffectInfo effect_info;
	std::string sprite_name;


	SpriteDataInfo()
	{
		posX = 100.0f;
		posY = 100.0f;
		scale = 1.0f;
		lifetime = 0.0f;
		once_playtime = 0.0f;
		max_frame = 0;
	}
};


class PSprite
{
public:
	PSprite();
	~PSprite();

private:

	PTexture* texture_;
	std::vector<PTexture*> texture_list_;

	//renewel
	vector<DX::PTex_uv4> tex_boundary_list_;
	vector<DX::PTex_uv4> tex_default_boundary_list_;
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
	EffectInfo effect_info;

public:

	bool Init();
	bool Frame();
	bool Render(ID3D11Device* device, ID3D11DeviceContext* context, std::vector<Vertex_PNCT>& vertices,
		DX::PDxHelper& helper, bool is_reversal);
	bool Release();
	bool Set(SpriteDataInfo info, float alpha, float scale);
	bool SetPosition(float x, float y);
	void Play();

	/*bufset : uv좌표 세트(4개) :: vertices : 버텍스 좌표 세트(4개) ::
	Plane Object를 셰이더에 넘겨준다.(직접 그리기 x) */
	void DrawPlane(ID3D11Device* device , ID3D11DeviceContext* context ,std::vector<Vertex_PNCT>& vertices,
		DX::PDxHelper& helper, bool is_reversal);
	void Clone(PSprite* sprite, float alpha, float scale);
	void AutomataClone(PSprite* sprite, float alpha, float scale, bool is_reversal, pPoint position);

	//getter
	pPoint get_position_();
	bool get_is_dead_();
	float get_scale();
	float get_remain_lifetime_();
	float get_lifetime_();
	float get_alpha_();
	int get_max_sprite_number();
	int get_current_played_frame();
	float get_allocatetime_for_onesprite();
	bool get_is_dmg();
	bool get_is_multitexture();
	bool get_is_effect();
	vector<DX::PTex_uv4> tex_boundary_list();
	vector<DX::PTex_uv4> tex_default_boundary_list();
	vector<DX::PTex_uv4>& tex_boundary_list_ref();
	PTexture* texture();
	std::vector<PTexture*>* get_texture_list_ptr();
	EffectInfo get_effect_info();

	//setter
	void set_alpha_(float alpha);
	void set_scale_(float scale);
	void set_current_played_spriteframe_(int current);
	void set_animation_type_(ANIMATIONTYPE type);
	void set_is_dmg(bool isdmg);
	void set_texture_list(std::vector<PTexture*>& texture_list);
	void set_is_multitexture(bool b);
	void set_is_effect(bool b);
	
	ANIMATIONTYPE get_animation_type_();
	
};

