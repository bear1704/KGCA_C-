#pragma once
#include "PShape.h"
#include "PSpriteManager.h"
#include <random>

const int kMaxParticle = 1000;


struct PInstance
{
	D3DXMATRIX mat_world;
	D3DXVECTOR4 color;
};

struct PEffectAnimation
{
	D3DXVECTOR3		rotate_axis;
	float			radius;
	bool			clockwise;
	float			current_angle;
	float			speed;
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
	D3DXVECTOR3					world_t_xyz; //�ݰ� ȸ���� ����� ��������� ��ġ��

	//animation
	PEffectAnimation			animation_info_;
	bool						is_animate;

	//particle etc..
	float						launch_time;
	D3DXMATRIX					mat_billboard_;
	D3DXMATRIX					plane_rot_matrix_;  //��ƼŬ���� rotation ����� ���� ����, �������
	D3DXVECTOR4					color_;
	D3D11_BLEND					src_blend_;
	D3D11_BLEND					dest_blend_;
	bool						is_use_billboard_;
	bool						is_use_fountain_;

	Microsoft::WRL::ComPtr<ID3D11Buffer> instance_buffer_;
	//Microsoft::WRL::ComPtr<ID3D11GeometryShader> gs_draw; //���� �׸� ����
	//Microsoft::WRL::ComPtr<ID3D11GeometryShader> gs_stream_out; //��µǴ� ��Ʈ���� �����ϴ� ���� (���� �����Ӹ��� ���ҵ�)
	//Microsoft::WRL::ComPtr<ID3D11VertexShader> vs_donothing;

	std::random_device rd;
	std::mt19937 mt;

private:
	float						spawn_time_counter_; //���� ��ƼŬ����, �����ϴ� �ð� ����
public:
	PEffectObject();
	~PEffectObject();


public:
	bool Init(ID3D11Device* device, ID3D11DeviceContext* context,
		std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
		std::wstring tex_name, std::wstring sprite_name) override;
	//HRESULT LoadShaderFromFile(ID3D11Device* device_, ShaderFileName filenames) override;
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
	void set_mat_bilboard(D3DXMATRIX bill);
	void SetWVPMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj) override;
};

