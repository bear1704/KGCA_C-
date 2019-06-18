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
		PSoundMgr::GetInstance().Play(PSoundMgr::GetInstance().Load(L"data/sound/sword.mp3"));
	}

	if (owner_->get_hit_() && owner_->get_invisible_() == false)
	{
		owner_->SetTransition(FSM_Event::HIT);
	}

	if (g_InputActionMap.attackKey == KEYSTAT::KEY_HOLD && owner_->get_sprite_()->get_is_dead_()) //���ݹ�ư�� �� ������ ���� ���
	{
		AttackProcess();
		owner_->set_sprite_(*owner_->find_sprite_by_type(ANIMATIONTYPE::ATTACK)); //�ٸ� ���ݸ������ ü���� 
		owner_->get_sprite_()->Play(); //���� ��������Ʈ �ٽ� ��� 
	}

	
	owner_->get_sprite_()->SetPosition(owner_->get_position_().x, owner_->get_position_().y);

	if (owner_->get_sprite_()->get_is_dead_())
	{
		owner_->SetTransition(FSM_Event::ATTACK_END);
		AttackProcess();

	}

}

void PAttackAction::AttackProcess()
{
	int damage = owner_->get_status().get_damage();


	if (g_current_scene_)
	{
		std::vector<PRectObject*> game_objects = 
			PObjectDataManager::GetInstance().get_object_list_from_map(g_current_scene_->get_scene_name_()); //MUSHROOMRAND

		//���ͺ� �浹üũ(RECT������)
		for (int i = 0; i < game_objects.size(); i++)
		{
			if (game_objects[i]->get_type_() == Type::MONSTER)
			{
				PMonster* monster = (PMonster*) game_objects[i];
				
				if (monster->get_current_monster_state_() == FSM_State::DEAD)
					continue;   //���� ���ʹ� ��Ʈ���� X

				if (monster->check_hit(owner_->get_attack_collision_box_()))
				{
					int hp = monster->get_status().get_hp_();
					monster->get_status().DecreaseHP(damage);  //���� ó�� ��Ʈ�� ���� Ÿ��
					monster->set_ishit_(true); //���� �Ѵ� �¾Ҵٰ� �˷��ֱ� 
					monster->set_be_received_damage_(damage);

					SIDE mob_to_player_side = 
						(owner_->get_collision_rect_().left - monster->get_collision_rect_().left) > 0 ? SIDE::RIGHT : SIDE::LEFT;

					monster->set_enemy_to_direction_side_(mob_to_player_side);

					break;
				}
			}
		}

	
	}
}
