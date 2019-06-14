#include "PFiniteState.h"
#include "assert.h"


State PFiniteState::get_next_state(Event key)
{
	auto iter = next_state_list_.find(key);
	assert(iter == next_state_list_.end());
	return iter->second;
}

PFiniteState::PFiniteState()
{
}


PFiniteState::~PFiniteState()
{
}
