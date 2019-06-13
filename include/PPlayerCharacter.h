#pragma once
#include "PCharacter.h"
#include "PPlayerStatus.h"

class PPlayerCharacter : public PCharacter
{
public:
	PPlayerCharacter();
	~PPlayerCharacter();
private:
	multibyte_string player_character_name_;
	PPlayerStatus status;
protected:

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void Movement();
	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
	PPlayerStatus& get_status();
	virtual void StatusSet(multibyte_string status_path, multibyte_string object_name);

	
};

