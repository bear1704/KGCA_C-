#include "PMoveAction.h"
#include "PPlayerCharacter.h"



PMoveAction::PMoveAction(PPlayerCharacter * parent) : PPlayerState(parent)
{
}

PMoveAction::~PMoveAction()
{
}

void PMoveAction::Process()
{
	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::MOVE)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::MOVE));
	}

	if (g_InputActionMap.jumpKey == KEYSTAT::KEY_PUSH)
	{
		owner_->SetTransition(FSM_Event::INPUT_JUMP);
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
	}

	owner_->get_sprite_()->SetPosition(owner_->get_position_().x, owner_->get_position_().y);

	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_FREE && g_InputActionMap.rightArrowKey == KEYSTAT::KEY_FREE) //무브->IDLE
	{
		owner_->SetTransition(FSM_Event::INPUT_NONE);
	}

	if (g_InputActionMap.attackKey == KEYSTAT::KEY_PUSH) //공격으로 전환
	{
		owner_->SetTransition(FSM_Event::INPUT_ATTACK); //sprite setposition필요
	}

}
