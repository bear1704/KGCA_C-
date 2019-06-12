#pragma once
#include "PCore.h"
#include "PMonster.h"
#include "PPlayerCharacter.h"
#include "PCollision.h"
#include "PObjectRotateUtil.h"
#include "PWallAndPlatform.h"
#include "PUIDataManager.h"

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
	bool InitDataLoad();
public:
	PPlayerCharacter* player_character_;
	PMonster* monster_[3];
	PRectObject* map_;
	PUIComponent* uicomp_settingbar;
	void draw_test_rect(FLOAT_RECT rect);
	
	
	//버튼테스트
	PButtonControl* button1;
	
	float angle = 0;


};

