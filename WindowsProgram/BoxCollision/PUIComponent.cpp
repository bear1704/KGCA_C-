#include "PUIComponent.h"



PUIComponent::PUIComponent()
{
}


PUIComponent::~PUIComponent()
{
}
bool PUIComponent::Init()
{
	for (auto &iter : component_list_)
	{
		iter->Init();
	}
	return true;
}
bool PUIComponent::Frame()
{
	for (auto &iter : component_list_)
	{
		iter->Frame();
	}
	return true;
}

bool PUIComponent::Render()
{
	for (auto &iter : component_list_)
	{
		iter->Render();
	}
	return true;
}

bool PUIComponent::Release()
{
	for (auto &iter : component_list_)
	{
		iter->Release();
	}
	return true;
}

void PUIComponent::Add(PUIComponent* component)
{
	
	component_list_.push_back(component);

}

void PUIComponent::Set(multibyte_string data_path, multibyte_string object_name, pPoint position)
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

