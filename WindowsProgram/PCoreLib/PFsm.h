#pragma once
#include "PFiniteState.h"

class PFsm : public PSingleton<PFsm>
{
public:
	PFsm();
	~PFsm();
private:
	friend class PSingleton<PFsm>;
	std::map<State, shared_ptr<PFiniteState>> state_space_;

public:
	void Add(State key_inputstate, Event event, State key_outputstate);
	PFiniteState* get_state(State key);


};

