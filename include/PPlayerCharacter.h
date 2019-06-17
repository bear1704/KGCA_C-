#pragma once
#include "PCharacter.h"
#include "PFsm.h"
#include "PPlayerState.h"

class PPlayerCharacter : public PCharacter
{
public:
	PPlayerCharacter();
	~PPlayerCharacter();
private:
	multibyte_string player_character_name_;
protected:

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void Movement();
	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
public:
	PFsm player_fsm_;
	PPlayerState* current_player_action_;
	std::map<FSM_State, PPlayerState*> action_list_;
	FSM_State current_player_state_;
	void SetTransition(FSM_Event event);
	void ProcessAction();



	
};

