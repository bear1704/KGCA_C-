#include "PBossMobHitAction.h"
#include "PBossMonster.h"
#include "PSoundMgr.h"

PBossMobHitAction::PBossMobHitAction(PBossMonster* parent) : PBossMobState(parent)
{
}

PBossMobHitAction::~PBossMobHitAction()
{
}

void PBossMobHitAction::Process()
{




	//if (PCollision::GetInstance().RectInRect(target->get_collision_rect_(), owner_->get_collision_rect_()))
	//{  //플레이어와의 충돌 체크 
	//	if (target->get_hit_() == false)
	//		target->set_hit_(true);
	//}


	//if (owner_->get_status().get_hp_() <= 0)
	//{
	//	owner_->SetTransition(FSM_Event::HPEMPTY);
	//}
	owner_->SetTransition(FSM_Event::INPUT_NONE);

}
