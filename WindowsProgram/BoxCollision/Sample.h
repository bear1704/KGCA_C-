#pragma once
#include "PCore.h"
#include "PMonster.h"
#include "PPlayerCharacter.h"
#include "PCollision.h"
#include "PObjectRotateUtil.h"
#include "PWallAndPlatform.h"
#include "PUIDataManager.h"
#include "PObjectDataManager.h"
#include "PScene.h"

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
	void draw_test_rect(FLOAT_RECT rect);
private:
	PScene* current_scene_;
	
	float angle = 0;


};

