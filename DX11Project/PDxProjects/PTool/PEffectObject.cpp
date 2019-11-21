#include "pch.h"
#include "PEffectObject.h"

void PEffectObject::AddRandParticle()
{


}


bool PEffectObject::Init(ID3D11Device* device, ID3D11DeviceContext* context,
	std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
	std::wstring tex_name, std::wstring sprite_name)
{
	PModel::Init(device, context);

	be_using_sprite_ = true;
	Create(device_, immediate_context_, vs_file_path, vs_func_name, ps_file_path, ps_func_name, tex_name);
	PSprite* sprite = PSpriteManager::GetInstance().get_sprite_from_map_ex(sprite_name);

	original_particle_ = new PParticle();
	original_particle_->CopySprite(sprite);
	original_particle_->effect_info = stored_effect_info_;


	return true;
}

bool PEffectObject::Frame()
{
	int size = particle_list_.size();
	for (int ii = 0; ii < size; ii++)
	{
		particle_list_[ii].Frame();
	}

	return true;
}

bool PEffectObject::Render()
{
	PParticle ptcl = *original_particle_;
	particle_list_.push_back(ptcl);

	for (auto iter = particle_list_.begin(); iter != particle_list_.end(); )
	{

		PParticle* pt = &(*iter);
		
		pt->Render(device_, immediate_context_, vertex_list_, dx_helper_, false);

		DX::ApplyDepthStencilState(immediate_context_, DX::PDxState::depth_stencil_state_disable_);
		constant_data_.color[3] = pt->get_alpha_();
		PModel::Render();
		DX::ApplyDepthStencilState(immediate_context_, DX::PDxState::depth_stencil_state_enable_);

		if (pt->get_is_dead_() == true)
		{
			iter = particle_list_.erase(iter);
		}
		else
			iter++;

	}

	return true;
}

void PEffectObject::CreateEffect(ID3D11Device* device, ID3D11DeviceContext* context, float width, float height, std::wstring sprite_name, EffectInfo particle_effect)
{
	be_using_sprite_ = true;
	width_ = width;   height_ = height;
	name = sprite_name;
	stored_effect_info_ = particle_effect;
	this->Init(device, context, L"VertexShader.hlsl", "VS_ALPHA", L"PixelShader.hlsl", "PS_ALPHA", L"", sprite_name);
}

void PEffectObject::set_is_multitexture(bool b)
{
	stored_effect_info_.is_multi_texture = b;
}


void PEffectObject::set_fadein(float f)
{
	stored_effect_info_.fadein_time = f;
	stored_effect_info_.current_fadein_time = f;
}

void PEffectObject::set_fadeout(float f)
{
	stored_effect_info_.fadeout_time = f;
	stored_effect_info_.current_fadeout_time = f;
}

void PParticle::CopySprite(PSprite* sprite)
{
	tex_boundary_list_ = sprite->tex_boundary_list();
	tex_default_boundary_list_ = sprite->tex_default_boundary_list();
	remain_lifetime_ = sprite->get_remain_lifetime_();
	lifetime_ = sprite->get_lifetime_();
	position_.x = sprite->get_position_().x;
	position_.y = sprite->get_position_().y;
	number_of_max_spriteframe_ = sprite->get_max_sprite_number();
	allocatetime_for_onesprite = sprite->get_allocatetime_for_onesprite();
	alpha_ = sprite->get_alpha_();
	scale_ = sprite->get_scale();
	current_played_spriteframe_ = 0;
	sprite->CopyTextureList(&texture_list_);
	sprite_name_ = sprite->get_name();
}


bool PParticle::Frame()
{
	if (remain_lifetime_ <= 0)
	{
		if (effect_info.current_fadeout_time > 0)
		{
			effect_info.current_fadeout_time -= g_SecondPerFrame;
			alpha_ = effect_info.current_fadeout_time / effect_info.fadeout_time;
		}
		else
		{
			isDead = true;
		}
	}
	if (isDead == true) return true;

	remain_lifetime_ -= g_SecondPerFrame;

	time_after_spriteopen_ += g_SecondPerFrame;
	if (time_after_spriteopen_ > allocatetime_for_onesprite)
	{
		current_played_spriteframe_++;
		if (current_played_spriteframe_ >= number_of_max_spriteframe_)
		{
			current_played_spriteframe_ = 0;
		}
		time_after_spriteopen_ = 0;
	}


}
