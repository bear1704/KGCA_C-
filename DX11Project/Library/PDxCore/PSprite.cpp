#include "PSprite.h"



PSprite::PSprite()
{
	isDead = false;
	alpha_ = 1.0f;
	is_dmg_ = false;
}


PSprite::~PSprite()
{
}

bool PSprite::Init()
{
	return false;
}

bool PSprite::Frame()
{
	if (remain_lifetime_ <= 0)
	{
		isDead = true;
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

	return true;
}

bool PSprite::Render(ID3D11Device* device, std::vector<DX::PVertex>& vertices,
	DX::PDxHelper& helper, bool is_reversal)
{/*
	pPoint scrpos = P2DCamera::GetInstance().WorldToGamescreen(position_);
	pPoint origin_pos = (position_);
	SetPosition(scrpos.x, scrpos.y);*/
	DrawPlane(device, vertices, helper, is_reversal);
	//SetPosition(origin_pos.x, origin_pos.y);
	return true;
}

bool PSprite::Release()
{
	return false;
}

bool PSprite::Set(SpriteDataInfo info, float alpha, float scale = 1.0f)
{
	tex_boundary_list_ = info.tex_boundary_list;
	tex_default_boundary_list_ = tex_boundary_list_;
	if (info.lifetime == 777)
	{
		remain_lifetime_ = 999999999.5f;
		lifetime_ = 999999999.5f;
	}
	else
	{
		remain_lifetime_ = info.lifetime;
		lifetime_ = info.lifetime;
	}
	
	position_.x = info.posX;
	position_.y = info.posY;
	number_of_max_spriteframe_ = info.max_frame;
	allocatetime_for_onesprite = info.once_playtime / info.max_frame;
	alpha_ = alpha;
	scale_ = scale;
	current_played_spriteframe_ = 0;

	texture_ = PTextureManager::GetInstance().GetTextureFromMap(info.texture_name);
	
	return true;
}

bool PSprite::SetPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	return false;
}

void PSprite::Play()
{
	isDead = false;
	remain_lifetime_ = lifetime_;
}

void PSprite::DrawPlane(ID3D11Device* device, std::vector<DX::PVertex>& vertices,
	DX::PDxHelper& helper, bool is_reversal)
{
	if (isDead)
		return;

	DX::PTex_uv4 tex_coord = tex_boundary_list_[current_played_spriteframe_];

	std::vector<DX::PVertexAndUV> vt_uv = DX::AssemblyVertAndTex(vertices, tex_coord);
	
	int vertices_count = kPlaneVertexNumber; //Plane전용이므로 4개
	
	helper.vertex_size_ = sizeof(DX::PVertexAndUV);
	helper.vertex_count_ = vertices_count;
	helper.vertex_buffer_.Attach(DX::CreateVertexBuffer(device, &vt_uv[0], vertices_count , sizeof(DX::PVertexAndUV), false));
	helper.shader_res_view_ = texture_->shader_res_view();

	//if(helper.shader_res_view_ != nullptr)
	//	helper.shader_res_view_.Attach(texture_->shader_res_view());
	////이거왜오류뜨냐(물어보기)


}

void PSprite::Clone(PSprite* sprite, float alpha, float scale)
{
	tex_boundary_list_ = sprite->tex_boundary_list();
	tex_default_boundary_list_ = tex_default_boundary_list();
	remain_lifetime_ = sprite->get_remain_lifetime_();
	lifetime_ = sprite->get_lifetime_();
	position_.x = sprite->get_position_().x;
	position_.y = sprite->get_position_().y;
	number_of_max_spriteframe_ = sprite->get_max_sprite_number();
	allocatetime_for_onesprite = sprite->get_allocatetime_for_onesprite();
	alpha_ = alpha;
	scale_ = scale;
	current_played_spriteframe_ = 0;
	
	if (sprite->texture() != nullptr)
	{
		texture_ = sprite->texture();
	}
	else
		assert(false);

	automata_ = false;
}

void PSprite::AutomataClone(PSprite* sprite, float alpha, float scale, bool is_reversal, pPoint position)
{
	tex_boundary_list_ = sprite->tex_boundary_list();
	tex_default_boundary_list_ = tex_default_boundary_list();
	remain_lifetime_ = sprite->get_remain_lifetime_();
	lifetime_ = sprite->get_lifetime_();
	position_ = position;
	number_of_max_spriteframe_ = sprite->get_max_sprite_number();
	allocatetime_for_onesprite = sprite->get_allocatetime_for_onesprite();
	alpha_ = alpha;
	scale_ = scale;
	current_played_spriteframe_ = 0;

	if (sprite->texture() != nullptr)
	{
		texture_ = sprite->texture();
	}
	else
		assert(false);

	automata_ = true;
	is_reversal_for_automata_ = is_reversal;
}




void PSprite::set_alpha_(float alpha)
{
	alpha_ = alpha;
}

void PSprite::set_scale_(float scale)
{
	scale_ = scale;
}



bool PSprite::get_is_dead_()
{
	return isDead;
}

float PSprite::get_scale()
{
	return scale_;
}

pPoint PSprite::get_position_()
{
	return position_;
}

void PSprite::set_current_played_spriteframe_(int current)
{
	current_played_spriteframe_ = current;
}




void PSprite::set_animation_type_(ANIMATIONTYPE type)
{
	animation_type_ = type;
}

void PSprite::set_is_dmg(bool isdmg)
{
	is_dmg_ = isdmg;
}

ANIMATIONTYPE PSprite::get_animation_type_()
{
	return animation_type_;
}

float PSprite::get_remain_lifetime_()
{
	return remain_lifetime_;
}

float PSprite::get_lifetime_()
{
	return lifetime_;
}

float PSprite::get_alpha_()
{
	return alpha_;
}

int PSprite::get_max_sprite_number()
{
	return number_of_max_spriteframe_;
}

int PSprite::get_current_played_frame()
{
	return current_played_spriteframe_;
}

float PSprite::get_allocatetime_for_onesprite()
{
	return allocatetime_for_onesprite;
}

bool PSprite::get_is_dmg()
{
	return is_dmg_;
}

vector<DX::PTex_uv4> PSprite::tex_boundary_list()
{
	return tex_boundary_list_;
}

vector<DX::PTex_uv4> PSprite::tex_default_boundary_list()
{
	return tex_default_boundary_list_;
}

PTexture* PSprite::texture()
{
	return texture_;
}
