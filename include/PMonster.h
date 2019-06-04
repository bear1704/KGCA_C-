#pragma once
#include "PCharacter.h"

class PMonster : public PCharacter
{
public:
	PMonster();
	~PMonster();
private:
	multibyte_string monster_name_;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
	void MonsterWallCollision();

};

