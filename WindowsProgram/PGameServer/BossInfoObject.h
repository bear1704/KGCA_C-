#include "TServerStd.h"
#include "PProtocol.h"
#include "PCharacter.h"

#pragma once
class BossInfoObject //서버가 보스를 제어할때 필요한 정보들 모음 
{
public:
	BossInfoObject(pPoint position);
	~BossInfoObject();
private:
	const std::wstring path = L"data/character_data.txt";
	const std::wstring map_path = L"data/map_data.txt";
	const std::wstring status_path = L"data/character_status_data.txt";
	const std::wstring animation_path = L"data/sprite/animation_list.txt";

public:
	void Set();
public:
	PPlayerStatus status_;
	multibyte_string boss_name_;
	FLOAT_RECT collision_box_norm_;
	FLOAT_RECT collision_box_;
	WORD id_;
	pPoint position_;
	float alpha_;
	float scale_;
	FSM_State current_state_;


};

