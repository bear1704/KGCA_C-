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

	if (g_InputActionMap.attackKey == KEYSTAT::KEY_HOLD && owner_->get_sprite_()->get_is_dead_()) //공격버튼을 꾹 누르고 있을 경우
	{
		AttackProcess();
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::ATTACK)); //다른 공격모션으로 체인지 
		owner_->get_sprite_()->Play(); //죽은 스프라이트 다시 재생 
	}


	owner_->get_sprite_()->SetPosition(owner_->get_position_().x, owner_->get_position_().y);

	if (owner_->get_sprite_()->get_is_dead_())
	{
		AttackProcess();
		owner_->SetTransition(FSM_Event::ATTACK_END);
	}

}

void PAttackAction::AttackProcess()
{
	int damage = owner_->get_status().get_damage();

	if (g_current_scene_)
	{
		std::vector<PRectObject*> game_objects = 
			PObjectDataManager::GetInstance().get_object_list_from_map(g_current_scene_->get_scene_name_()); //MUSHROOMRAND

		//몬스터별 충돌체크(RECT가지고)
		for (int i = 0; i < game_objects.size(); i++)
		{
			if (game_objects[i]->get_type_() == Type::MONSTER)
			{
				PMonster* monster = (PMonster*) game_objects[i];
				if (monster->check_hit(owner_->get_attack_collision_box_()))
				{
					int hp = monster->get_status().get_hp_();
					monster->get_status().DecreaseHP(damage);  //제일 처음 히트된 몬스터 타격
					monster->set_ishit_(true); //몬스터 한대 맞았다고 알려주기 

					SIDE mob_to_player_side = 
						(owner_->get_collision_rect_().left - monster->get_collision_rect_().left) > 0 ? SIDE::RIGHT : SIDE::LEFT;

					monster->set_enemy_to_direction_side_(mob_to_player_side);

					break;
				}
			}
		}



	
	}
}
