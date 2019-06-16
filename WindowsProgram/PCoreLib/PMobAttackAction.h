#pragma once
#include "PMobState.h"

class PMobAttackAction : public PMobState
{
public:
	PMobAttackAction(PMonster* parent);
	~PMobAttackAction();
public:
	void process();
};

