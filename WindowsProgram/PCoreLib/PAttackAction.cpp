#include "PAttackAction.h"
#include "PPlayerCharacter.h"

HANDLE handle_attack_timer_queue_;
HANDLE handle_attack_timer_;
bool hit_time;
#define ATTACK_SPEED 0.5

VOID CALLBACK TimerCallBack(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	hit_time = true;
	Sleep(100);
	DeleteTimerQueueTimer(handle_attack_timer_queue_, handle_attack_timer_, nullptr);
}


PAttackAction::PAttackAction(PPlayerCharacter* parent) : PPlayerState(parent)
{
	handle_attack_timer_ = NULL;
	handle_attack_timer_queue_ = NULL;
	hit_time = false;
}


PAttackAction::~PAttackAction()
{

}

void PAttackAction::Process()
{
	bool is_owner = (owner_->get_client_owner_character());

	handle_attack_timer_queue_ = CreateTimerQueue();
	CreateTimerQueueTimer(handle_attack_timer_, handle_attack_timer_queue_, (WAITORTIMERCALLBACK)TimerCallBack,
		nullptr, 0, ATTACK_SPEED, WT_EXECUTEDEFAULT);

	if (owner_->get_sprite_()->get_animation_type_() != ANIMATIONTYPE::ATTACK)
	{
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::ATTACK));
		PSoundMgr::GetInstance().Play(PSoundMgr::GetInstance().Load(L"data/sound/sword.mp3"));
		
	}

	
	if (g_InputActionMap.attackKey == KEYSTAT::KEY_HOLD && owner_->get_sprite_()->get_is_dead_()) //공격버튼을 꾹 누르고 있을 경우
	{
		if (is_owner)
		{
			AttackProcess();
			owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::ATTACK)); //다른 공격모션으로 체인지 
			owner_->get_sprite_()->Play(); //죽은 스프라이트 다시 재생 
		}
	}



	owner_->get_sprite_()->SetPosition(owner_->get_position_().x, owner_->get_position_().y);

	if (owner_->get_sprite_()->get_is_dead_())
	{
			owner_->SetTransition(FSM_Event::ATTACK_END);
			AttackProcess();

	}
	if (owner_->get_hit_() && owner_->get_invisible_() == false)
	{
		if (is_owner)
		{
			if (owner_->get_sprite_()->get_is_dead_() == true)
			{
				owner_->SetTransition(FSM_Event::HIT);
			}
		}
	}

}

void PAttackAction::AttackProcess()
{
	int damage = owner_->get_status().get_damage();


	if (g_current_scene_)
	{
		//std::vector<PRectObject*> game_objects = 
		//	PObjectDataManager::GetInstance().get_object_list_from_map(g_current_scene_->get_scene_name_()); //MUSHROOMRAND

		std::vector<PRectObject*>* game_objects = g_current_scene_->get_game_objects();

		//몬스터별 충돌체크(RECT가지고)
		for (int i = 0; i < game_objects->size(); i++)
		{
			if ((*game_objects)[i]->get_type_() == Type::MONSTER)
			{
				PMonster* monster = (PMonster*)(*game_objects)[i];
				
				if (monster->get_current_monster_state_() == FSM_State::DEAD)
					continue;   //죽은 몬스터는 히트판정 X

				if (monster->check_hit(owner_->get_attack_collision_box_()))
				{
					int hp = monster->get_status().get_hp_();
					monster->get_status().DecreaseHP(damage);  //제일 처음 히트된 몬스터 타격
					monster->set_ishit_(true); //몬스터 한대 맞았다고 알려주기 
					monster->set_be_received_damage_(damage);

					SIDE mob_to_player_side = 
						(owner_->get_collision_rect_().left - monster->get_collision_rect_().left) > 0 ? SIDE::RIGHT : SIDE::LEFT;

					monster->set_enemy_to_direction_side_(mob_to_player_side);

					break;
				}
			}
			else if ((*game_objects)[i]->get_type_() == Type::BOSS_MONSTER)
			{
				PBossMonster* bmonster = (PBossMonster*)(*game_objects)[i];

				if (bmonster->get_current_monster_state_() == FSM_State::DEAD)
					continue;

				if (bmonster->check_hit(owner_->get_attack_collision_box_()))
				{
					bmonster->get_status().DecreaseHP(damage); //보스 체력 감소 
					HitData data;
					data.boss_id = bmonster->get_id();
					data.damage = damage;
					data.player_id = owner_->get_id();
					
					PNetworkDataStorage::GetInstance().AddData(data); //네트워크립을 위한 데이터 저장

					bmonster->set_ishit_(true); //몬스터 한대 맞았다고 알려주기 
					bmonster->set_be_received_damage_(damage);
					//hit판정과 타격패킷전송필요
				}
				break;
			}
		}

	
	}
}
