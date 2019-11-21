#include "pch.h"
#include "PEffectObject.h"

void PEffectObject::AddRandParticle()
{


}


PEffectObject::PEffectObject()
{
	color_.x = 1.0f;
	color_.y = 1.0f;
	color_.z = 1.0f;
	color_.w = 1.0f;
	spawn_time_counter_ = 0.0f;
	launch_time = 1.0f;
}

PEffectObject::~PEffectObject()
{

}

bool PEffectObject::Init(ID3D11Device* device, ID3D11DeviceContext* context,
	std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
	std::wstring tex_name, std::wstring sprite_name)
{

	device_ = device;
	immediate_context_ = context;
	D3DXMatrixIdentity(&matView_);
	D3DXMatrixIdentity(&matProj_);


	be_using_sprite_ = true;
	Create(device_, immediate_context_, vs_file_path, vs_func_name, ps_file_path, ps_func_name, tex_name);
	PSprite* sprite = PSpriteManager::GetInstance().get_sprite_from_map_ex(sprite_name);

	D3DXVECTOR3 v_plane_trans, v_plane_scale;
	D3DXQUATERNION quat_rot;
	D3DXMatrixDecompose(&v_plane_scale, &quat_rot, &v_plane_trans, &matWorld_);

	original_particle_ = new PParticle();
	original_particle_->CopySprite(sprite);
	original_particle_->effect_info = stored_effect_info_;
	original_particle_->position = v_plane_trans;
	original_particle_->scale = v_plane_scale;


	return true;
}

bool PEffectObject::Frame()
{
	D3DXMATRIX mat_scale;
	D3DXMATRIX mat_rotation;
	D3DXMatrixIdentity(&mat_scale);
	D3DXMatrixIdentity(&mat_rotation);

	PParticle ptcl = *original_particle_;
	spawn_time_counter_ += g_SecondPerFrame;

	if (spawn_time_counter_ > launch_time)
	{
		if (particle_list_.size() < kMaxParticle)
		{
			particle_list_.push_back(ptcl);
			spawn_time_counter_ -= launch_time;
		}
	}

	int size = particle_list_.size();
	for (int ii = 0; ii < size; ii++)
	{
		particle_list_[ii].Frame();

		mat_scale._11 = particle_list_[ii].scale.x;
		mat_scale._22 = particle_list_[ii].scale.y;
		mat_scale._33 = particle_list_[ii].scale.z;
		mat_rotation = mat_scale * plane_rot_matrix_;
		mat_rotation._41 = particle_list_[ii].position.x;
		mat_rotation._42 = particle_list_[ii].position.y;
		mat_rotation._43 = particle_list_[ii].position.z;
		D3DXMatrixTranspose(&instance_list_[ii].mat_world, &mat_rotation);
		instance_list_[ii].color.w = particle_list_[ii].get_alpha_();
	}

	D3D11_MAPPED_SUBRESOURCE ms;
	if (SUCCEEDED(immediate_context_->Map(
		instance_buffer_.Get(), 0,
		D3D11_MAP_WRITE_DISCARD, 0,
		&ms)))
	{
		PInstance* data = (PInstance*)ms.pData;
		memcpy(data, (void*)& instance_list_.at(0), sizeof(PInstance) * particle_list_.size());
		immediate_context_->Unmap(instance_buffer_.Get(), 0);
	}

	return true;
}

bool PEffectObject::Render()
{

	for (auto iter = particle_list_.begin(); iter != particle_list_.end(); )
	{

		PParticle* pt = &(*iter);
		
		DX::ApplyDepthStencilState(immediate_context_, DX::PDxState::depth_stencil_state_disable_);
		PreRender();
		pt->Render(device_, immediate_context_, vertex_list_, dx_helper_, false);
		PostRender();
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

HRESULT PEffectObject::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0  },

		{"InstanceWorld", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"InstanceWorld", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"InstanceWorld", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"InstanceWorld", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"POSCOLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D11_INPUT_PER_INSTANCE_DATA, 1},
	};

	int numberof_element = sizeof(layout) / sizeof(layout[0]);
	dx_helper_.input_layout_.Attach(DX::CreateInputLayout(device_,
		dx_helper_.vertex_blob_->GetBufferSize(),
		dx_helper_.vertex_blob_->GetBufferPointer(),
		layout, numberof_element));


	return S_OK;
}

HRESULT PEffectObject::CreateVertexData()
{
	HRESULT hr = S_OK;
	if (FAILED(hr = PPlaneObject::CreateVertexData())) return hr;

	instance_list_.resize(kMaxParticle);

	for (int ii = 0; ii < kMaxParticle; ii++)
	{
		D3DXMatrixIdentity(&instance_list_[ii].mat_world);
		instance_list_[ii].color = D3DXVECTOR4(1, 1, 1, 1);
	}
	return hr;
}

HRESULT PEffectObject::CreateVertexBuffer()
{
	HRESULT hr = S_OK;

	if (FAILED(hr = PModel::CreateVertexBuffer()))
	{
		return hr;
	}

	instance_buffer_.Attach(DX::CreateVertexBuffer(device_,
		&instance_list_.at(0),
		kMaxParticle,
		sizeof(PInstance), true));

	return hr;
}

bool PEffectObject::PostRender()
{
	//VB, InstanceB
	ID3D11Buffer* buf_array[2] = {
		dx_helper_.vertex_buffer_.Get(),
		instance_buffer_.Get()};

	UINT stride[2] = { sizeof(Vertex_PNCT), sizeof(PInstance) };
	UINT offset[2] = { 0, 0 };

	immediate_context_->IASetVertexBuffers(0, 2, buf_array, stride, offset);

	constant_data_.color[0] = color_.x;
	constant_data_.color[1] = color_.y;
	constant_data_.color[2] = color_.z;
	constant_data_.color[3] = color_.w;
	constant_data_.etc[0] = g_fGameTimer;

	immediate_context_->UpdateSubresource(
		dx_helper_.constant_buffer_.Get(),
		0, NULL, &constant_data_, 0, 0);

	immediate_context_->PSSetConstantBuffers(0, 1, dx_helper_.constant_buffer_.GetAddressOf());

	immediate_context_->DrawIndexedInstanced(dx_helper_.index_count_, particle_list_.size(), 0, 0, 0);

	return true;
}

void PEffectObject::CreateEffect(ID3D11Device* device, ID3D11DeviceContext* context, float width, float height, std::wstring sprite_name, EffectInfo particle_effect)
{
	be_using_sprite_ = true;
	width_ = width;   height_ = height;
	name = sprite_name;
	stored_effect_info_ = particle_effect;
	this->Init(device, context, L"Instance.hlsl", "VS_ALPHA", L"Instance.hlsl", "PS_ALPHA", L"", sprite_name);
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

PParticle::PParticle()
{
	velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	gravity = D3DXVECTOR3(0.0f, -9.8f, 0.0f);
	external_force = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale	 = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

PParticle::~PParticle()
{

}

void PParticle::CopySprite(PSprite* sprite)
{
	tex_boundary_list_ = sprite->tex_boundary_list();
	tex_default_boundary_list_ = sprite->tex_default_boundary_list();
	remain_lifetime_ = sprite->get_remain_lifetime_();
	lifetime_ = sprite->get_lifetime_();
	//position_.x = sprite->get_position_().x;
	//position_.y = sprite->get_position_().y;
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
	if (effect_info.current_fadein_time > 0.0f)
	{
		effect_info.current_fadein_time -= g_SecondPerFrame;
		alpha_ = 1.0f - (effect_info.current_fadein_time / effect_info.fadein_time);
	}
	else
	{
		remain_lifetime_ -= g_SecondPerFrame;
	}


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

	D3DXVECTOR3 move = velocity + gravity + external_force;
	position += move * g_SecondPerFrame;

}
