#pragma once
#include "PShape.h"
#include "PSpriteManager.h"

const int kMaxParticle = 1000;


struct PInstance
{
	D3DXMATRIX mat_world;
	D3DXVECTOR4 color;
};

class PParticle : public PSprite
{
public:
	PParticle();
	~PParticle();
public:
	EffectInfo effect_info;
	D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 gravity;
	D3DXVECTOR3 external_force;

	void CopySprite(PSprite* sprite);

public:
	bool Frame() override;
};

class PEffectObject : public PPlaneObject
{
public:
	EffectInfo					stored_effect_info_; //ó�� ��ƼŬ�� effinfo�� ���� �� ����ϸ�, �� ���ķδ� ����Ǿ �� ��
	std::vector<PEffectObject*> eff_list_; //component
	PParticle*					original_particle_; //������ ��ƼŬ
	std::vector<PParticle>		particle_list_;   //���� �����Ǵ� ��ƼŬ ����Ʈ
	std::vector<PInstance>		instance_list_;
	D3DXMATRIX					plane_rot_matrix_;  //��ƼŬ���� rotation ����� ���� ����
	D3DXVECTOR4					color_;
	float launch_time;
	D3D11_BLEND	src_blend_;
	D3D11_BLEND	dest_blend_;
	Microsoft::WRL::ComPtr<ID3D11Buffer> instance_buffer_;
private:
	float						spawn_time_counter_; //���� ��ƼŬ����, �����ϴ� �ð� ����
public:
	PEffectObject();
	~PEffectObject();


public:
	bool Init(ID3D11Device* device, ID3D11DeviceContext* context,
		std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
		std::wstring tex_name, std::wstring sprite_name) override;
	bool Frame() override;
	bool Render() override;

	virtual HRESULT CreateInputLayout() override;
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateVertexBuffer() override;
	bool PostRender() override;



public:
	void AddRandParticle();

	void CreateEffect(ID3D11Device* device, ID3D11DeviceContext* context, float width, float height, std::wstring sprite_name, EffectInfo particle_effect);
	void set_is_multitexture(bool b);
	void set_fadein(float f);
	void set_fadeout(float f);
};

