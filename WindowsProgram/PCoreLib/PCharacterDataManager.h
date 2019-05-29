#pragma once
#include "PStd.h"
#include <assert.h>

struct CharacterStatus
{
	float move_speed;
	RECT collision_box;
	pPoint position_;

};


class PCharacterDataManager : public PSingleton<PCharacterDataManager>
{//name movespeed collisionboxsize 
public:
	PCharacterDataManager();
	~PCharacterDataManager();

private:
	friend class PSingleton<PCharacterDataManager>;
	std::map<std::wstring, CharacterStatus*> character_status_list;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

	CharacterStatus* get_character_status_list_from_map(std::wstring key);
	void LoadDataFromScript(multibyte_string filepath);
};

