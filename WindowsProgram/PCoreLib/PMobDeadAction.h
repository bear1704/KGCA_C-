#pragma once
#include "PMobState.h"
class PMobDeadAction :
	public PMobState
{
public:
	PMobDeadAction(PMonster* parent);
	~PMobDeadAction();
};

