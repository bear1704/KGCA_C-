#pragma once
#include "PMobState.h"
class PMobJumpAction :
	public PMobState
{
public:
	PMobJumpAction(PMonster* parent);
	~PMobJumpAction();
};
