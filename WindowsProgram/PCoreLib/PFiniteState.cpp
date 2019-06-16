#include "PFiniteState.h"
#include "assert.h"


FSM_State PFiniteState::get_next_state(FSM_Event key)
{
	auto iter = next_state_list_.find(key);
	assert(iter != next_state_list_.end());
	return iter->second;
}

PFiniteState::PFiniteState()
{
}


PFiniteState::~PFiniteState()
{
}
