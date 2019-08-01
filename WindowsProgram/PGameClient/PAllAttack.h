#pragma once
#include "PUserManager.h"
#include "PSkill.h"
#include "PSpriteManager.h"
#include "PNetworkDataStorage.h"

class PAllAttack :
	public PSkill
{
private:
	std::vector<pPoint> spawn_position_vec_;
	FLOAT_RECT barrier_area_;
	PSprite goddess_;
	pPoint selected_position;
public:
	PAllAttack();
	~PAllAttack();
	void Init() override;
	void Frame() override;
	void Render() override;
	void Release() override;
	void Start(int randnum) override;

};

