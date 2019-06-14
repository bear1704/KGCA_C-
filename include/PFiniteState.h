#pragma once
#include "PStd.h"

enum class State { IDLE, MOVE, ATTACK, JUMP, HIT};
enum class Event {INPUT_NONE, INPUT_MOVE, INPUT_ATTACK, INPUT_JUMP, HIT};

class PFsm;

class PFiniteState
{
	friend class PFsm;

private:
	std::map<Event, State> next_state_list_;
public:
	 State get_next_state(Event key);

public:
	PFiniteState();
	virtual ~PFiniteState();
};

