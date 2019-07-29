#include "PBossMobIdleAction.h"
#include "PBossMonster.h"

PBossMobIdleAction::PBossMobIdleAction(PBossMonster * parent) : PBossMobState(parent)
{
}


PBossMobIdleAction::~PBossMobIdleAction()
{
}

void PBossMobIdleAction::Process()
{
	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::IDLE)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::IDLE));
	}



}
