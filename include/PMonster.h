#pragma once
#include "PCharacter.h"
#include "PMobState.h"
#include "PFsm.h"

class PMonster : public PCharacter
{
public:
	PMonster();
	~PMonster();
private:
	multibyte_string monster_name_;
	SIDE direction_side_;
	bool ishit_;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
	void MonsterWallCollision();
	void Movement();
	SIDE get_direction_side_();
	void set_direction_side_(SIDE side);


	PFsm monster_fsm_;
	PMobState* current_monster_action_;
	std::map<FSM_State, PMobState*> action_list_;
	FSM_State current_monster_state_;
	void SetTransition(FSM_Event event);
	void ProcessAction();
	bool check_hit(FLOAT_RECT player_attack_col);
	void set_ishit_(bool hit);

};

