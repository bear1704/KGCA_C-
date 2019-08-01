#pragma once
#include "PSkill.h"
#include "PSprite.h"
#include <random>
#include <functional>
#include "PSpriteManager.h"
#include "PNetworkDataStorage.h"

class Stone
{
public:
	Stone();
	~Stone();

public:
	PSprite stone_sprite_;
	FLOAT_RECT stone_rect_;
	float drop_speed_;
	pPoint position_;

};


class PMeteor : public PSkill
{

public:
	PMeteor(int initypos, int randdownspeed);
	~PMeteor();
public:
	std::vector<Stone> stone_list_;
private:
	int rand_init_ypos_;
	int rand_downspeed_;

public:
	void Init() override;
	void Frame() override;
	void Render() override;
	void Release() override;
	void Start();

};

