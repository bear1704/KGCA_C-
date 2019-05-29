#pragma once
#include "PCharacter.h"

class PMonster : public PCharacter
{
public:
	PMonster(pPoint point, multibyte_string monster_name);
	~PMonster();
private:
	multibyte_string monster_name_;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

};

