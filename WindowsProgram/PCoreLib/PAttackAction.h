#pragma once
#include "PPlayerState.h"

class PAttackAction : public PPlayerState
{
public:
	PAttackAction(PPlayerCharacter* parent);
	~PAttackAction();
public:
	void Process();
};

