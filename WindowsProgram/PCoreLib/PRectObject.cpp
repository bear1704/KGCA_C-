#include "PRectObject.h"
#include <random>
#include <ctime>
#include <functional>


PRectObject::PRectObject()
{
	
}


PRectObject::~PRectObject()
{
}

bool PRectObject::Init()
{

	return true;
}

bool PRectObject::Frame()
{
	return true;
}

bool PRectObject::Render()
{
	Spawn();
	return true;
}

bool PRectObject::Release()
{
	if (sprite_.get_bitmap_mask_() != nullptr)
	{
		sprite_.get_bitmap_()->Release();
		delete sprite_.get_bitmap_();
	}
	if (sprite_.get_bitmap_mask_() != nullptr)
	{
		sprite_.get_bitmap_mask_()->Release();
		delete sprite_.get_bitmap_mask_();
	}
	
	return true;
}

void PRectObject::StatusSet(multibyte_string status_path, multibyte_string object_name)
{
}

void PRectObject::StatusSetForServer(multibyte_string status_path, multibyte_string object_name)
{
}


void PRectObject::Set(multibyte_string data_path, multibyte_string object_name, pPoint position)
{
	PObjectInfoManager::GetInstance().LoadDataFromScript(data_path, ObjectLoadType::MAP);
	//지금은 MAP이지만 다른 오브젝트의 확장성을 만족하기 위해 맵 등의 오브젝트를 모아놓은 통합txt를 만들어야 한다.
	ObjectInfo info = *(PObjectInfoManager::GetInstance().get_object_info_list_from_map(object_name));

	object_name_ = info.object_name_;
	position_ = position;
	collision_box_norm_ = info.collision_box_;
	alpha_ = info.alpha_;
	scale_ = info.scale_;

	//PSpriteManager::GetInstance().LoadDataFromScript(info.sprite_path);
	//sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(info.sprite_name), alpha_, scale_);
	PSpriteManager::GetInstance().LoadSpriteDataFromScript(info.sprite_path, ObjectLoadType::MAP);
	sprite_.Clone(PSpriteManager::GetInstance().get_sprite_from_map_ex(info.sprite_name), alpha_, scale_);
	sprite_.SetPosition(position_.x, position_.y);


	FLOAT_RECT scaled_collisionbox_norm = { collision_box_norm_.left*scale_, collision_box_norm_.top*scale_ ,
	collision_box_norm_.right*scale_, collision_box_norm_.bottom*scale_ };

	spawn_position_ = position;

	collision_box_norm_ = scaled_collisionbox_norm;

}

PBitmap * PRectObject::get_bitmap_()
{
	return sprite_.bitmap_;
}

PBitmap * PRectObject::get_bitmap_mask_()
{
	return sprite_.bitmap_mask_;
}

PSprite * PRectObject::get_sprite_()
{
	return &sprite_;
}

void PRectObject::set_sprite_(PSprite & sprite)
{
	sprite_ = sprite;
}


pPoint& PRectObject::get_position_()
{
	return position_;
}

void PRectObject::set_position_(pPoint xy)
{
	position_.x = xy.x;
	position_.y = xy.y;
}


FLOAT_RECT PRectObject::get_collision_rect_()
{
	return collision_box_;
}

FLOAT_RECT PRectObject::get_collision_rect_norm_()
{
	return collision_box_norm_;
}

//
//
//bool PRectObject::Load(std::wstring filename)
//{
//	int key = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAP);
//	if (key != -1)
//		sprite_.bitmap_ = PBitmapManager::GetInstance().get_bitmap_from_map(key);
//
//	int key_mask = PBitmapManager::GetInstance().BitmapLoad(filename, PLoadMode::BITMAPMASK);
//	if (key_mask != -1)
//		sprite_.bitmap_mask_ = PBitmapManager::GetInstance().get_bitmap_from_map(key_mask);
//
//	return true;
//}

void PRectObject::set_collision_box_(FLOAT_RECT norm_box)
{

	float half_width = norm_box.right / 2;
	float half_height = norm_box.bottom / 2;

	collision_box_.left = position_.x - half_width;
	collision_box_.top = position_.y - half_height;
	collision_box_.right = norm_box.right;
	collision_box_.bottom = norm_box.bottom;
}



float PRectObject::get_scale_()
{
	return scale_;
}

float PRectObject::get_alpha_()
{
	return alpha_;
}

bool PRectObject::get_invisible_()
{
	return invisible_;
}

void PRectObject::set_invisible_(bool invisible)
{
	invisible_ = invisible;
}

void PRectObject::Spawn()
{
	pPoint scrpos = P2DCamera::GetInstance().WorldToGamescreen(sprite_.get_position_());
	pPoint origin_pos = sprite_.get_position_();
	sprite_.SetPosition(scrpos.x, scrpos.y);
	sprite_.Draw(is_reversal_);
	sprite_.SetPosition(origin_pos.x, origin_pos.y);
}

void PRectObject::set_gravity_(float gravity)
{
	gravity_ = gravity;
}

void PRectObject::set_type_(Type type)
{
	type_ = type;
}

Type PRectObject::get_type_()
{
	return type_;
}

multibyte_string PRectObject::get_object_name()
{
	return object_name_;
}

void PRectObject::set_animation_list_(std::vector<PSprite*> list)
{
	animation_list_ = list;
}



///스프라이트를 Type값으로 찾아준다. 첫번째 시도에서 type가 없으면, 그냥 IDLE 리턴
PSprite * PRectObject::find_sprite_by_type(ANIMATIONTYPE type)
{
	/*auto iter = std::find_if(animation_list_.begin(), animation_list_.end(), 
		[type](PSprite* element) {
		return element->get_animation_type_() == type;
	});
	return *iter;*/

	std::random_device r;
	std::mt19937 engine(r());
	std::uniform_int_distribution<int> distribution(0, 2);
	auto generator = std::bind(distribution, engine);

	int number = generator();

	if (type == ANIMATIONTYPE::ATTACK) // ATTACK일 때 3가지 중 하나 고르는 부분
	{
		for (auto& iter : animation_list_)
		{
			if (iter->get_animation_type_() == type)
			{
				if (number > 0)
				{
					number--;
					continue;
				}
				else
					return iter;
			}
		}
	}
	else
	{
		for (auto& iter : animation_list_)
		{
			if (iter->get_animation_type_() == type)
				return iter;
		}
	}


	for (auto& iter : animation_list_) 
	{
		if (iter->get_animation_type_() == ANIMATIONTYPE::IDLE)
			return iter;
	}

}

bool& PRectObject::get_is_reversal_()
{
	return is_reversal_;
}

PPhysicsModule & PRectObject::get_physics_()
{
	return physics_;
}

const WORD PRectObject::get_id()
{
	return id_;
}

void PRectObject::set_alpha_and_scale_(float alpha, float scale)
{
	for (PSprite* sprite : animation_list_)
	{
		sprite->set_alpha_(alpha);
		sprite->set_scale_(scale);
	}
	sprite_.set_alpha_(alpha);
	sprite_.set_scale_(scale);
}

void PRectObject::set_id(WORD id)
{
	id_ = id;
}

void PRectObject::set_is_reversal(bool isreversal)
{
	is_reversal_ = isreversal;
}

void PRectObject::set_collision_box_norm(FLOAT_RECT fl)
{
	collision_box_norm_ = fl;
}

pPoint PRectObject::get_spawn_position_()
{
	return spawn_position_;
}
