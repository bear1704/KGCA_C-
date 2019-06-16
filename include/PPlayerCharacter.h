#pragma once
#include "PCharacter.h"
#include "PPlayerStatus.h"
#include "PPlayerState.h"
#include "PFsm.h"

class PPlayerCharacter : public PCharacter
{
public:
	PPlayerCharacter();
	~PPlayerCharacter();
private:
	multibyte_string player_character_name_;
	PPlayerStatus status;
protected:

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void Movement();
	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
	PPlayerStatus& get_status();
	virtual void StatusSet(multibyte_string status_path, multibyte_string object_name);
public:
	PFsm player_fsm_;
	PPlayerState* current_player_action_;
	std::map<FSM_State, PPlayerState*> action_list_;
	FSM_State current_player_state_;
	void SetTransition(FSM_Event event);
	void ProcessAction();



	
};

