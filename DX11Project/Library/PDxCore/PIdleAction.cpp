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
	bool is_owner = (owner_->get_client_owner_character());
	


	if (owner_->get_hit_() && owner_->get_invisible_() == false)
	{
		if(is_owner)
			owner_->SetTransition(FSM_Event::HIT);
	}

	if (g_InputActionMap.jumpKey == KEYSTAT::KEY_PUSH)
	{
		if (is_owner)
			owner_->SetTransition(FSM_Event::INPUT_JUMP);
	}


	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD || g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
	{
		if (is_owner)
			owner_->SetTransition(FSM_Event::INPUT_MOVE); 
	}


	if (g_InputActionMap.attackKey == KEYSTAT::KEY_PUSH) //���� 
	{
		if (is_owner)
			owner_->SetTransition(FSM_Event::INPUT_ATTACK); //sprite setposition�ʿ�
	}

}