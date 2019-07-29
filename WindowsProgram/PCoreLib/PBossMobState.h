#pragma once
#include <random>
#include <functional>
#include <ctime>
#include "TServerStd.h"
#include "PProtocol.h"

class PBossMonster;

class PBossMobState
{
protected:
	PBossMonster* owner_;
public:
	PBossMobState(PBossMonster* parent) : owner_(parent) {}
	PBossMobState() = delete;
	virtual ~PBossMobState();
public:
	virtual void Process() = 0;
};

