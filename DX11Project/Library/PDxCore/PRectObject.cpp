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
	return true;
}

bool PRectObject::Release()
{
	
	
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
	//������ MAP������ �ٸ� ������Ʈ�� Ȯ�强�� �����ϱ� ���� �� ���� ������Ʈ�� ��Ƴ��� ����txt�� ������ �Ѵ�.
	ObjectInfo info = *(PObjectInfoManager::GetInstance().get_object_info_list_from_map(object_name));

	object_name_ = info.object_name_;
	position_ = position;
	collision_box_norm_ = info.collision_box_;
	alpha_ = info.alpha_;
	scale_ = info.scale_;


	FLOAT_RECT scaled_collisionbox_norm = { collision_box_norm_.left*scale_, collision_box_norm_.top*scale_ ,
	collision_box_norm_.right*scale_, collision_box_norm_.bottom*scale_ };

	spawn_position_ = position;

	collision_box_norm_ = scaled_collisionbox_norm;

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



///��������Ʈ�� Type������ ã���ش�. ù��° �õ����� type�� ������, �׳� IDLE ����

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