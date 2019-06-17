#include "PAttackAction.h"
#include "PPlayerCharacter.h"


PAttackAction::PAttackAction(PPlayerCharacter* parent) : PPlayerState(parent)
{
}


PAttackAction::~PAttackAction()
{
}

void PAttackAction::Process()
{
	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::ATTACK)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::ATTACK));
	}

	if (g_InputActionMap.attackKey == KEYSTAT::KEY_HOLD && owner_->get_sprite_()->get_is_dead_()) //���ݹ�ư�� �� ������ ���� ���
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::ATTACK)); //�ٸ� ���ݸ������ ü���� 
		owner_->get_sprite_()->Play(); //���� ��������Ʈ �ٽ� ��� 
	}


	owner_->get_sprite_()->SetPosition(owner_->get_position_().x, owner_->get_position_().y);

	if (owner_->get_sprite_()->get_is_dead_())
	{
		owner_->SetTransition(FSM_Event::ATTACK_END);
	}

}
