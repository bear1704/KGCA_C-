#include "PScene.h"



PScene::PScene()
{

}


PScene::~PScene()
{
}

bool PScene::Init()
{
	target = nullptr;

	for (int i = 0; i < game_objects_.size(); i++)
	{
		if (game_objects_[i]->get_type_() == Type::PLAYER)
		{
			PPlayerCharacter* player = (PPlayerCharacter*)game_objects_[i];
			player->set_client_owner_character(true);
			target = player;
			player->Init();
		}
	}
	for (int i = 0; i < game_objects_.size(); i++)
	{
		if (game_objects_[i]->get_type_() == Type::OTHER_PLAYER)
		{
			PPlayerCharacter* ot_player = (PPlayerCharacter*)game_objects_[i];
			ot_player->Init();
		}
	}
	for (int i = 0; i < game_objects_.size(); i++)
	{
		if (game_objects_[i]->get_type_() == Type::MONSTER)
		{
			PMonster* monster = (PMonster*)game_objects_[i];
			monster->set_target_player_(target);
			monster->Init();
		}
		else if (game_objects_[i]->get_type_() == Type::NPC)
		{
			PRectObject* npc = (PRectObject*)game_objects_[i];
			npc->Init();
		}
		else if (game_objects_[i]->get_type_() == Type::MAP)
		{
			PRectObject* map = (PRectObject*)game_objects_[i];
			map->Init();
		}
		else if (game_objects_[i]->get_type_() == Type::BOSS_MONSTER)
		{
			PBossMonster* map = (PBossMonster*)game_objects_[i];
			map->Init();
		}
	}

	for (int i = 0; i < ui_compositions_.size(); i++)
	{
		ui_compositions_[i]->Init();
	}



	return true;
}

bool PScene::Frame()
{
	for (int i = 0; i < game_objects_.size(); i++)
	{
		if (game_objects_[i]->get_type_() == Type::PLAYER)
		{
			PPlayerCharacter* player = (PPlayerCharacter*)game_objects_[i];
			player->Frame();
			target = player;
			if (target->get_status().get_exp_() >= target->get_status().get_max_exp() && scene_number_ == 1)
			{
				SceneChange(2);
			}
			if (target->get_status().get_hp_() <= 0)
			{
				SceneChange(3);
			}
		}
	}


	for (int i = 0; i < game_objects_.size(); i++)
	{
		if (game_objects_[i]->get_type_() == Type::MONSTER)
		{
			PMonster* monster = (PMonster*)game_objects_[i];
			monster->set_target_player_(target);
			monster->Frame();
		}
		else if (game_objects_[i]->get_type_() == Type::NPC)
		{
			PRectObject* npc = (PRectObject*)game_objects_[i];
			npc->Frame();
		}
		else if (game_objects_[i]->get_type_() == Type::MAP)
		{
			PRectObject* map = (PRectObject*)game_objects_[i];
			map->Frame();
		}
		else if (game_objects_[i]->get_type_() == Type::OTHER_PLAYER)
		{
			PPlayerCharacter* player = (PPlayerCharacter*)game_objects_[i];
			player->Frame();
		}
		else if (game_objects_[i]->get_type_() == Type::BOSS_MONSTER)
		{
			PBossMonster* player = (PBossMonster*)game_objects_[i];
			player->Frame();
		}
	}
	for (int i = 0; i < ui_compositions_.size(); i++)
	{
		ui_compositions_[i]->Frame();
	}


	return true;
}

bool PScene::Render()
{
	
	for (int i = 0; i < game_objects_.size(); i++)
	{
		if (game_objects_[i]->get_type_() == Type::MAP)
		{
			PRectObject* map = (PRectObject*)game_objects_[i];
			map->Render();
		}
		else if (game_objects_[i]->get_type_() == Type::PLAYER)
		{
			PPlayerCharacter* player = (PPlayerCharacter*)game_objects_[i];
			player->Render();
			//draw_test_rect(player->get_foot_plane_box());
			//draw_test_rect(player->get_collision_rect_());
			//draw_test_rect(player->get_attack_collision_box_());
		}
		else if (game_objects_[i]->get_type_() == Type::MONSTER)
		{
			PMonster* monster = (PMonster*)game_objects_[i];
			monster->Render();
		}
		else if (game_objects_[i]->get_type_() == Type::NPC)
		{
			PRectObject* npc = (PRectObject*)game_objects_[i];
			npc->Render();
		}
		else if (game_objects_[i]->get_type_() == Type::OTHER_PLAYER)
		{
			PPlayerCharacter* player = (PPlayerCharacter*)game_objects_[i];
			player->Render();
		}
		else if (game_objects_[i]->get_type_() == Type::BOSS_MONSTER)
		{
			PBossMonster* player = (PBossMonster*)game_objects_[i];
			player->Render();
		}
	}
	for (int i = 0; i < ui_compositions_.size(); i++)
	{
		ui_compositions_[i]->Render();
	}


	FLOAT_RECT cam_center_pos_rect = P2DCamera::GetInstance().get_center_rect_();
	//draw_test_rect(cam_center_pos_rect);

	int platform_size = PWallAndPlatform::GetInstance().get_platform_list_().size();
	int monsterwall_size = PWallAndPlatform::GetInstance().get_monster_wall_list_().size();
	int wall_size = PWallAndPlatform::GetInstance().get_wall_list_().size();


	//for (int i = 0; i < platform_size; i++)
	//{
	//	draw_test_rect(PWallAndPlatform::GetInstance().get_platform_list_().at(i));
	//}
	//for (int i = 0; i < monsterwall_size; i++)
	//{
	//	draw_test_rect(PWallAndPlatform::GetInstance().get_monster_wall_list_().
	//		at(i));
	//}
	//for (int i = 0; i < wall_size; i++)
	//{
	//	draw_test_rect(PWallAndPlatform::GetInstance().get_wall_list_().at(i));
	//}



	return true;
}

bool PScene::Release()
{


	for (int i = 0; i < game_objects_.size(); i++)
	{
		if (game_objects_[i]->get_type_() == Type::PLAYER)
		{
			PPlayerCharacter* player = (PPlayerCharacter*)game_objects_[i];
			player->Release();
		}
		else if (game_objects_[i]->get_type_() == Type::MONSTER)
		{
			PMonster* monster = (PMonster*)game_objects_[i];
			monster->Release();
		}
		else if (game_objects_[i]->get_type_() == Type::NPC)
		{
			PRectObject* npc = (PRectObject*)game_objects_[i];
			npc->Release();
		}
		else if (game_objects_[i]->get_type_() == Type::MAP)
		{
			PRectObject* map = (PRectObject*)game_objects_[i];
			map->Release();
		}
		else if (game_objects_[i]->get_type_() == Type::OTHER_PLAYER)
		{
			PPlayerCharacter* player = (PPlayerCharacter*)game_objects_[i];
			player->Release();
		}
		else if (game_objects_[i]->get_type_() == Type::BOSS_MONSTER)
		{
			PBossMonster* player = (PBossMonster*)game_objects_[i];
			player->Release();
		}
	}

	for (int i = 0; i < ui_compositions_.size(); i++)
	{
		ui_compositions_[i]->Release();
	}

	return true;
}

void PScene::InsertObject(PUIComponent * component)
{
	ui_compositions_.push_back(component);
}

void PScene::InsertObject(std::vector<PRectObject*>& list_component)
{
	game_objects_ = list_component;
}

void PScene::set_scene_name_(std::wstring name)
{
	scene_name_ = name;
}

std::wstring PScene::get_scene_name_()
{
	return scene_name_;
}

void PScene::draw_test_rect(FLOAT_RECT rect)
{

	SetROP2(g_handle_off_screenDC, R2_NOTXORPEN);
	FLOAT_RECT arect = P2DCamera::GetInstance().WorldToGamescreenRECT(rect);
	int prevMode2 = Rectangle(g_handle_off_screenDC, arect.left, arect.top,
		arect.left + arect.right, arect.top + arect.bottom);
	SetROP2(g_handle_off_screenDC, prevMode2);
}

void PScene::SceneChange(int scene_number)
{
	if (scene_number == 2)
	{
		PScene* scene2 = new PScene();
		PUIDataManager::GetInstance().LoadDataFromScript(L"data/UI/UI_composition_list.txt");
		PUIComponent* uicomp_settingbar = PUIDataManager::GetInstance().get_ui_composition_list_from_map(L"END");
		scene2->InsertObject(uicomp_settingbar);
		g_current_scene_ = scene2;
		scene_number_ = 2;
		PSound* bgm = PSoundMgr::GetInstance().GetPtr(0);
		bgm->Stop();
		PSoundMgr::GetInstance().Play(PSoundMgr::GetInstance().Load(L"data/sound/end.mp3"));
	}
	else if (scene_number == 3)
	{
		PScene* scene3 = new PScene();
		PUIDataManager::GetInstance().LoadDataFromScript(L"data/UI/UI_composition_list.txt");
		PUIComponent* uicomp_settingbar = PUIDataManager::GetInstance().get_ui_composition_list_from_map(L"GAMEOVER");
		scene3->InsertObject(uicomp_settingbar);
		g_current_scene_ = scene3;
		scene_number_ = 3;
		PSound* bgm = PSoundMgr::GetInstance().GetPtr(0);
		bgm->Stop();
		PSoundMgr::GetInstance().Play(PSoundMgr::GetInstance().Load(L"data/sound/gameover.mp3"));
	}




}

std::vector<PUIComponent*>* PScene::get_ui_compositions_()
{
	return &ui_compositions_;
}

std::vector<PRectObject*>* PScene::get_game_objects()
{
	return &game_objects_;
}

void PScene::AddGameObjects(PRectObject* obj)
{
	if(obj != nullptr)
		game_objects_.push_back(obj);
}

void PScene::AddUiComponents(PUIComponent* ui)
{
	if(ui != nullptr)
		ui_compositions_.push_back(ui);
}

PRectObject* PScene::FindObjectByCid(WORD id)
{
	auto iter = std::find_if(game_objects_.begin(), game_objects_.end(),
		[&id](PRectObject* obj) ->bool {return obj->get_id() == id; });

	if (iter == game_objects_.end())
		return nullptr;

	return *iter;
}



void PScene::set_target(PPlayerCharacter* character)
{
	target = character;
}
