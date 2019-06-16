#pragma once

class PMonster;

class PMobState
{
protected:
	PMonster* owner_;
public:
	PMobState(PMonster* parent) : owner_(parent) {}
	virtual ~PMobState();
public:
	virtual void Process() = 0;
};

