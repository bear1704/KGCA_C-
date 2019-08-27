#pragma once
#include "PTextureManager.h"
#include "PStd.h"
#include <assert.h>
#include "P2DCamera.h"
#include "PTexture.h"
#include "PDxHelper.h"

const int kPlaneVertexNumber = 4;

struct SpriteDataInfo
{
	vector<DX::PTex_uv4> tex_boundary_list;
	std::wstring texture_name;
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
	bool is_reversal_for_automata_;//reversal �������� ��������Ʈ�� ������ �� �ʿ� ������, Ư�� ��Ȳ(1ȸ�� ��������Ʈ ���� ��..)���� �ʿ��ϹǷ� �ִ´�.
							//1ȸ�� ��������Ʈ�� ������ �� �� �����ؾ���
	bool is_dmg_; //�������� ǥ���ϴ� ��������Ʈ���� üũ



public:

	bool Init();
	bool Frame();
	bool Render(ID3D11Device* device, std::vector<DX::PVertex>& vertices,
		DX::PDxHelper& helper, bool is_reversal);
	bool Release();
	bool Set(SpriteDataInfo info, float alpha, float scale);
	bool SetPosition(float x, float y);
	void Play();

	/*bufset : uv��ǥ ��Ʈ(4��) :: vertices : ���ؽ� ��ǥ ��Ʈ(4��) ::
	Plane Object�� ���̴��� �Ѱ��ش�.(���� �׸��� x) */
	void DrawPlane(ID3D11Device* device , std::vector<DX::PVertex>& vertices, 
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
	vector<DX::PTex_uv4> tex_boundary_list();
	vector<DX::PTex_uv4> tex_default_boundary_list();
	PTexture* texture();

	//setter
	void set_alpha_(float alpha);
	void set_scale_(float scale);
	void set_current_played_spriteframe_(int current);
	void set_animation_type_(ANIMATIONTYPE type);
	void set_is_dmg(bool isdmg);
	ANIMATIONTYPE get_animation_type_();
	
};

