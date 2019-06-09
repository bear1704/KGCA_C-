#include "PButtonControl.h"



PButtonControl::PButtonControl()
{
}


PButtonControl::~PButtonControl()
{
}

void PButtonControl::SetStateButton(int normal, int hover, int push, int disable, bool coll)
{
	state_normal = normal;
	state_hover = hover;
	state_disabled = disable;
	is_select = false;
	state_bitmap[NORMAL] = PBitmapManager::GetInstance().get_bitmap_from_map(normal);
	state_bitmap[HOVER] = PBitmapManager::GetInstance().get_bitmap_from_map(hover);
	state_bitmap[PUSH] = PBitmapManager::GetInstance().get_bitmap_from_map(push);
	state_bitmap[DISABLE] = PBitmapManager::GetInstance().get_bitmap_from_map(disable);
	is_collision = coll;
	current_bitmap = state_bitmap[NORMAL];

}
bool PButtonControl::Release()
{
	PSprite::Release(); //?
	return true;
}