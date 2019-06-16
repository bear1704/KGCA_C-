#include "PIdleAction.h"
#include "PPlayerCharacter.h"


PIdleAction::PIdleAction(PPlayerCharacter * parent) : PPlayerState(parent)
{

}

PIdleAction::~PIdleAction()
{
}

void PIdleAction::Process()
{
	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::IDLE)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::IDLE));
	}

	if (g_InputActionMap.jumpKey == KEYSTAT::KEY_PUSH)
	{
		owner_->SetTransition(FSM_Event::INPUT_JUMP);
	}


	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD || g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
	{
		owner_->SetTransition(FSM_Event::INPUT_MOVE); //sprite setposition필요
	}


	if (g_InputActionMap.attackKey == KEYSTAT::KEY_PUSH) //공격 
	{
		owner_->SetTransition(FSM_Event::INPUT_ATTACK); //sprite setposition필요
	}

	owner_->get_sprite_()->SetPosition(owner_->get_position_().x, owner_->get_position_().y);
}
