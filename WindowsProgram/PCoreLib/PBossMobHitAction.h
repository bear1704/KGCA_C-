#pragma once
#include "PBossMobState.h"


class PBossMobHitAction : public PBossMobState
{
public:
	PBossMobHitAction(PBossMonster* parent);
	~PBossMobHitAction();
	float progress_time_ = 0.0f;
	float knockback_distance_ = 35.0f;
	float knockback_speed_ = 150.0f;

	pPoint damage_pos;
	int damage_length;

public:
	void Process();
};

