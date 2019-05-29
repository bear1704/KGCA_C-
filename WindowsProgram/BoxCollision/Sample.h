#pragma once
#include "PCore.h"
#include "PCharacter.h"
#include "PMonster.h"
#include "PCollision.h"
#include "PObjectRotateUtil.h"

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
	PCharacter* player_character_;
	PMonster* monster_;
	PMonster* tester_;
	PMonster* tester2_;
	PMonster* other_side_tester_;
	float angle = 0.0f;

};

