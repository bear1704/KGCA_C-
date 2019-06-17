#include "PJumpAction.h"
#include "PPlayerCharacter.h"


PJumpAction::PJumpAction(PPlayerCharacter* parent) : PPlayerState(parent)
{
}


PJumpAction::~PJumpAction()
{
}

void PJumpAction::Process()
{
	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::JUMP)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::JUMP));

	}

	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
	{
		owner_->get_is_reversal_() = false;
		owner_->set_position_(pPoint(owner_->get_position_().x - owner_->get_move_speed_() * g_SecondPerFrame, owner_->get_position_().y));
	}
	else if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
	{
		owner_->get_is_reversal_() = true;
		owner_->set_position_(pPoint(owner_->get_position_().x + owner_->get_move_speed_() * g_SecondPerFrame, owner_->get_position_().y));
	} //������ �����Ʈ�� �־�δ°� �ſ� ��û�� ����. �Ŀ� �����ÿ� ����Ű ���⿡ ���� �����Ǵ� ���������� �̵��ϰ� �ؾ� ��.



	if (!(owner_->get_physics_().get_isjump()))
	{
		//if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_FREE && g_InputActionMap.rightArrowKey == KEYSTAT::KEY_FREE)//���� ��
		//{
		//	owner_->SetTransition(FSM_Event::INPUT_NONE);
		//}
		//else
		//{
		//	owner_->SetTransition(FSM_Event::INPUT_MOVE);
		//}
		owner_->SetTransition(FSM_Event::JUMP_END);
	}
	if (g_InputActionMap.attackKey== KEYSTAT::KEY_PUSH)
	{
		owner_->SetTransition(FSM_Event::INPUT_ATTACK);
	}


	owner_->get_sprite_()->SetPosition(owner_->get_position_().x, owner_->get_position_().y);
}
