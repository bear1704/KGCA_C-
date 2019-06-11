#include "PButtonControl.h"
#include "PCollision.h"


PButtonControl::PButtonControl()
{
	state_normal = NORMAL;
	state_hover = HOVER;
	state_push = PUSH;
	state_disable = DISABLE;
	current_sprite_rect = NORMAL;
	is_collision = false;
}


PButtonControl::~PButtonControl()
{

}


void PButtonControl::Draw()
{
	sprite_.Draw();
}
bool PButtonControl::Frame()
{

		current_sprite_rect = NORMAL;
		is_select = false;
		if (PCollision::GetInstance().RectInPoint(collision_box_, g_MousePos))
		{
			if (g_InputActionMap.leftClick == KEYSTAT::KEY_HOLD)
			{
				current_sprite_rect = state_push;
				is_select = true;
			}
			else
			{
				current_sprite_rect = state_hover;
			}
		}



	sprite_.set_current_played_spriteframe_(current_sprite_rect); //현재 상태를 스프라이트 상태로 설정

	return false;
}
bool PButtonControl::Release()
{
	PRectObject::Release();
	
	return true;
}

PUIComponent * PButtonControl::Clone()
{
	return new PButtonControl(*this);
}
