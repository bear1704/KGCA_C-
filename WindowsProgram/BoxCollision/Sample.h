#pragma once
#include "PCore.h"
#include "PCharacter.h"

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

};

