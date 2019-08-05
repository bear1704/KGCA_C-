#pragma once
#include "PObjectDataManager.h"
#include "PPlayerCharacter.h"
#include "PMonster.h"
#include "PBossMonster.h"
#include "PCore.h"



class PScene
{
public:
	PScene();
	~PScene();
private:
	std::vector<PRectObject*> game_objects_;
	std::wstring scene_name_;
	PPlayerCharacter* target;
	int scene_number_ = 1;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void InsertObject(std::vector<PRectObject*>& list_component);
	void set_scene_name_(std::wstring name);
	std::wstring get_scene_name_();
	void draw_test_rect(FLOAT_RECT rect);
	void SceneChange(int scene_number);
	std::vector<PRectObject*>* get_game_objects();
	void AddGameObjects(PRectObject* obj);
	void DeleteGameObjectsByCid(WORD cid);
	PRectObject* FindObjectByCid(WORD id);
	void set_target(PPlayerCharacter* character);

};

