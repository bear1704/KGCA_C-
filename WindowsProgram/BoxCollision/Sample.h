#pragma once
#include "PCore.h"
#include "PMonster.h"
#include "PPlayerCharacter.h"
#include "PCollision.h"
#include "PObjectRotateUtil.h"
#include "PWallAndPlatform.h"

class Sample : public PCore
{
public:
	Sample();
	~Sample();

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	PPlayerCharacter* player_character_;
	PMonster* monster_[3];
	PRectObject* map_;
	void draw_test_rect(FLOAT_RECT rect);
	
	
	float angle = 0;


};

