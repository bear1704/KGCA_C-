#pragma once
#include "PCharacter.h"
class PPlayerCharacter : public PCharacter
{
public:
	PPlayerCharacter();
	~PPlayerCharacter();
private:
	multibyte_string player_character_name_;

protected:

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void Movement();
	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);

	
};

