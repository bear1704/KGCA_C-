#include "PSprite.h"



PSprite::PSprite()
{
	isDead = false;
	alpha_ = 1.0f;
	is_dmg_ = false;
	effect_info.is_effect_sprite = false;
	effect_info.is_multi_texture = false;
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

bool PSprite::Render(ID3D11Device* device, ID3D11DeviceContext* context ,std::vector<Vertex_PNCT>& vertices,
	DX::PDxHelper& helper, bool is_reversal)
{
	DrawPlane(device, context,vertices, helper, is_reversal);
	return true;
}

bool PSprite::Release()
{
	return false;
}

bool PSprite::Set(SpriteDataInfo info, float alpha, float scale = 1.0f)
{
	if(texture_list_.size() <= 0)
		texture_list_ = info.texture_list;
	
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
	effect_info.is_multi_texture = info.effect_info.is_multi_texture;
	effect_info.is_effect_sprite = info.effect_info.is_effect_sprite;


	if (effect_info.is_multi_texture == false)
	{
		effect_info.x_count = info.effect_info.x_count;
		effect_info.y_count = info.effect_info.y_count;
		effect_info.x_offset = info.effect_info.x_offset;
		effect_info.y_offset = info.effect_info.y_offset;
		effect_info.x_init = info.effect_info.x_init;
		effect_info.y_init = info.effect_info.y_init;
		effect_info.tex_width = info.effect_info.tex_width;
		effect_info.tex_height = info.effect_info.tex_height;
	}

	if (texture_list_.size() == 0)
		texture_ = PTextureManager::GetInstance().GetTextureFromMap(info.texture_name);
	else
		texture_ = texture_list_[0];
	
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

void PSprite::DrawPlane(ID3D11Device* device, ID3D11DeviceContext* context ,std::vector<Vertex_PNCT>& vertices,
	DX::PDxHelper& helper, bool is_reversal)
{
	if (isDead)
		return;

	if (tex_boundary_list().size() > 0)
	{

		DX::PTex_uv4 tex_coord = tex_boundary_list_[current_played_spriteframe_];

		PModel::ChangeTexValue(vertices, tex_coord);

		int vertices_count = vertices.size();

		helper.vertex_size_ = sizeof(Vertex_PNCT);
		helper.vertex_count_ = vertices_count;
		context->UpdateSubresource(helper.vertex_buffer_.Get(),
			0, NULL, &vertices.at(0), 0, 0);
		helper.shader_res_view_ = texture_->shader_res_view();
	}
	else
	{
		texture_ = texture_list_[current_played_spriteframe_];
		helper.shader_res_view_ = texture_->shader_res_view();
	}

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
	texture_list_ = sprite->texture_list_;
	
	effect_info.is_effect_sprite = sprite->effect_info.is_effect_sprite;
	effect_info.is_multi_texture= sprite->effect_info.is_multi_texture;
	effect_info.tex_width = sprite->effect_info.tex_width;
	effect_info.tex_height = sprite->effect_info.tex_height;

	effect_info.x_count = sprite->effect_info.x_count;
	effect_info.y_count = sprite->effect_info.y_count;
	effect_info.x_init= sprite->effect_info.x_init;
	effect_info.y_init = sprite->effect_info.y_init;
	effect_info.x_offset = sprite->effect_info.x_offset;
	effect_info.y_offset = sprite->effect_info.y_offset;


	if (sprite->texture() != nullptr)
	{
		texture_ = sprite->texture();
	}
	else if(texture_list_.size() > 0) {}
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

void PSprite::set_texture_list(std::vector<PTexture*>& texture_list)
{
	texture_list_ = std::move(texture_list);
}

void PSprite::set_is_multitexture(bool b)
{
	effect_info.is_multi_texture = b;
}

void PSprite::set_is_effect(bool b)
{
	effect_info.is_effect_sprite = b;
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

bool PSprite::get_is_multitexture()
{
	return effect_info.is_multi_texture;
}

bool PSprite::get_is_effect()
{
	return effect_info.is_effect_sprite;
}

vector<DX::PTex_uv4> PSprite::tex_boundary_list()
{
	return tex_boundary_list_;
}

vector<DX::PTex_uv4> PSprite::tex_default_boundary_list()
{
	return tex_default_boundary_list_;
}

vector<DX::PTex_uv4>& PSprite::tex_boundary_list_ref()
{
	return tex_boundary_list_;
}

PTexture* PSprite::texture()
{
	return texture_;
}

std::vector<PTexture*>* PSprite::get_texture_list_ptr()
{
	return &texture_list_;
}

EffectInfo PSprite::get_effect_info()
{
	return effect_info;
}
