#pragma once
#include <random>
#include <functional>
#include <ctime>

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

