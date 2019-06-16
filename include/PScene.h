#pragma once
#include "PUIComponent.h"
#include "PPlayerCharacter.h"
#include "PMonster.h"
#include "PCore.h"

class PScene
{
public:
	PScene();
	~PScene();
private:
	std::vector<PUIComponent*> ui_compositions_;
	std::vector<PRectObject*> game_objects_;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void InsertObject(PUIComponent* component);
	void InsertObject(std::vector<PRectObject*>& list_component);
	void draw_test_rect(FLOAT_RECT rect);
};
