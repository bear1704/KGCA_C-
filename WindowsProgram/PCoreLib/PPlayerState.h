#pragma once

class PPlayerCharacter;

class PPlayerState
{

protected:
	PPlayerCharacter* owner_;
public:
	virtual void Process() = 0;
public:
	PPlayerState(PPlayerCharacter* parent) : owner_(parent) {}
	virtual ~PPlayerState();

};

