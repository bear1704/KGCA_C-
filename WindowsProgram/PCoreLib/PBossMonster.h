#pragma once
#include "PCharacter.h"
#include "PFsm.h"
#include "PBossMobState.h"



class PBossMonster :
	public PCharacter
{

public:
	PBossMonster();
	~PBossMonster();
public:

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

	PFsm boss_monster_fsm_;
	PBossMobState* current_boss_monster_action_;
	std::map<FSM_State, PBossMobState*> action_list_;
	FSM_State current_boss_monster_state_;

	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
	void SetTransition(FSM_Event event);
	void ProcessAction();
	bool check_hit(FLOAT_RECT player_attack_col);
	FSM_State get_current_monster_state_();
};
