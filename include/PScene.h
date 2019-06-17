#pragma once
#include "PUIComponent.h"
#include "PObjectDataManager.h"
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
	std::wstring scene_name_;
	PPlayerCharacter* target;
	int scene_number_ = 1;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void InsertObject(PUIComponent* component);
	void InsertObject(std::vector<PRectObject*>& list_component);
	void set_scene_name_(std::wstring name);
	std::wstring get_scene_name_();
	void draw_test_rect(FLOAT_RECT rect);
	void SceneChange();
};

