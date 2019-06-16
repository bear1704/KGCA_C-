#pragma once
#include "PPlayerState.h"
class PHitAction :
	public PPlayerState
{
public:
	PHitAction(PPlayerCharacter* parent);
	~PHitAction();
public:
	void Process();
};

