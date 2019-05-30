#include "PRectObject.h"
#include "PBitmapManager.h"


PRectObject::PRectObject()
{
	move_speed_ = 0.0f;
	position_ = { 0,0 }; //ÃÊ±âÈ­
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
	/*if (sprite_.bitmap_mask_ != nullptr)
	{
		sprite_.bitmap_mask_->Draw(position_.x, position_.y, collision_box_, SRCAND);
		sprite_.bitmap_->Draw(position_.x, position_.y, collision_box_, SRCINVERT);
		sprite_.bitmap_mask_->Draw(position_.x, position_.y, collision_box_, SRCINVERT);
	}
	else
	{
		sprite_.bitmap_->Draw(position_.x, position_.y, collision_box_, SRCCOPY);
	}
*/
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


void PRectObject::Set(pPoint p, RECT collision_box, float move_speed, multibyte_string object_data_path, multibyte_string object_name,
	multibyte_string sprite_path, multibyte_string sprite_name, float alpha, float scale)
{
	PCharacterDataManager::GetInstance().LoadDataFromScript(object_data_path);
	CharacterStatus* status = PCharacterDataManager::GetInstance().get_character_status_list_from_map(L"player");
	scale_ = 1.0f;

	PSpriteManager::GetInstance().LoadDataFromScript(L"data/character/sprite/character_coord.txt");

	sprite_.Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"playerCharacter"), 1.0f, scale_);
	sprite_.SetPosition(position_.x, position_.y);
}

void PRectObject::Set(PRectObjectStat stat)
{
	position_ = stat.position_;
	move_speed_ = stat.move_speed_;
	collision_box_norm_ = stat.collision_box_;
	set_collision_box_(stat.collision_box_);
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

float * PRectObject::get_position_xy(PXY axis)
{
	if (axis == PXY::X)
		return &position_.x;
	else if (axis == PXY::Y)
		return &position_.y;

	return nullptr;
}


RECT PRectObject::get_collision_rect_()
{
	return collision_box_;
}

float PRectObject::get_moveSpeed_()
{
	return move_speed_;
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

inline void PRectObject::set_collision_box_(RECT norm_box)
{

	float half_width = norm_box.right / 2;
	float half_height = norm_box.bottom / 2;

	collision_box_.left = position_.x - half_width;
	collision_box_.top = position_.y - half_height;
	collision_box_.right = position_.x + half_width;
	collision_box_.bottom = position_.y + half_height;

}


float PRectObject::get_scale_()
{
	return scale_;
}

