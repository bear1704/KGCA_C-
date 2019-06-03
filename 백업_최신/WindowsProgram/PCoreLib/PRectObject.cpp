#include "PRectObject.h"


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
	if (!sprite_.get_bitmap_())
	{
		sprite_.get_bitmap_()->Release();
		delete sprite_.get_bitmap_();
	}
	if (!sprite_.get_bitmap_mask_())
	{
		sprite_.get_bitmap_mask_()->Release();
		delete sprite_.get_bitmap_mask_();
	}
	
	return true;
}


void PRectObject::Set(multibyte_string data_path, multibyte_string object_name, pPoint position)
{
	PObjectDataManager::GetInstance().LoadDataFromScript(data_path);
	ObjectInfo info = *(PObjectDataManager::GetInstance().get_object_info_list_from_map(object_name));

	object_name_ = info.object_name_;
	position_ = position;
	collision_box_norm_ = info.collision_box_;
	alpha_ = info.alpha_;
	scale_ = info.scale_;

	PSpriteManager::GetInstance().LoadDataFromScript(info.sprite_path);
	sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(info.sprite_name), alpha_, scale_);
	sprite_.SetPosition(position_.x, position_.y);


	FLOAT_RECT scaled_collisionbox_norm = { collision_box_norm_.left*scale_, collision_box_norm_.top*scale_ ,
	collision_box_norm_.right*scale_, collision_box_norm_.bottom*scale_ };

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

pPoint PRectObject::get_position_()
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

void PRectObject::Spawn()
{
	pPoint scrpos = P2DCamera::GetInstance().WorldToGamescreen(sprite_.get_position_());
	pPoint origin_pos = sprite_.get_position_();
	sprite_.SetPosition(scrpos.x, scrpos.y);
	sprite_.Draw();
	sprite_.SetPosition(origin_pos.x, origin_pos.y);
}

