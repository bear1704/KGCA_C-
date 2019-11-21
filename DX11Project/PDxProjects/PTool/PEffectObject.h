#pragma once
#include "PShape.h"
#include "PSpriteManager.h"

const int kMaxParticle = 1000;


class PParticle : public PSprite
{
public:
	EffectInfo effect_info;

	void CopySprite(PSprite* sprite);

public:
	bool Frame() override;
};



class PEffectObject : public PPlaneObject
{
public:
	EffectInfo					stored_effect_info_;
	std::vector<PEffectObject*> eff_list_; //component
	PParticle*					original_particle_; //원형판 파티클
	std::vector<PParticle>		particle_list_;   //실제 렌더되는 파티클 리스트


	bool Init(ID3D11Device* device, ID3D11DeviceContext* context,
		std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
		std::wstring tex_name, std::wstring sprite_name) override;
	bool Frame() override;
	bool Render() override;

public:
	void AddRandParticle();

	void CreateEffect(ID3D11Device* device, ID3D11DeviceContext* context, float width, float height, std::wstring sprite_name, EffectInfo particle_effect);
	void set_is_multitexture(bool b);
	void set_fadein(float f);
	void set_fadeout(float f);
};

