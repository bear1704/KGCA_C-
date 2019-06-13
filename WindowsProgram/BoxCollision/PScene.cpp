#include "PScene.h"



PScene::PScene()
{

}


PScene::~PScene()
{
}

bool PScene::Init()
{
	for (int i = 0; i < game_objects_.size(); i++)
	{
		if (game_objects_[i]->get_type_() == Type::PLAYER)
		{
			PPlayerCharacter* player = (PPlayerCharacter*)game_objects_[i];
			player->Init();
		}
		else if (game_objects_[i]->get_type_() == Type::MONSTER)
		{
			PMonster* monster = (PMonster*)game_objects_[i];
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
		}
		else if (game_objects_[i]->get_type_() == Type::MONSTER)
		{
			PMonster* monster = (PMonster*)game_objects_[i];
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
			draw_test_rect(player->get_foot_plane_box());
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
	}
	for (int i = 0; i < ui_compositions_.size(); i++)
	{
		ui_compositions_[i]->Render();
	}


	FLOAT_RECT cam_center_pos_rect = P2DCamera::GetInstance().get_center_rect_();
	draw_test_rect(cam_center_pos_rect);

	int platform_size = PWallAndPlatform::GetInstance().get_platform_list_().size();
	int monsterwall_size = PWallAndPlatform::GetInstance().get_monster_wall_list_().size();
	int wall_size = PWallAndPlatform::GetInstance().get_wall_list_().size();


	for (int i = 0; i < platform_size; i++)
	{
		draw_test_rect(PWallAndPlatform::GetInstance().get_platform_list_().at(i));
	}
	for (int i = 0; i < monsterwall_size; i++)
	{
		draw_test_rect(PWallAndPlatform::GetInstance().get_monster_wall_list_().
			at(i));
	}
	for (int i = 0; i < wall_size; i++)
	{
		draw_test_rect(PWallAndPlatform::GetInstance().get_wall_list_().at(i));
	}



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

void PScene::draw_test_rect(FLOAT_RECT rect)
{

	SetROP2(g_handle_off_screenDC, R2_NOTXORPEN);
	FLOAT_RECT arect = P2DCamera::GetInstance().WorldToGamescreenRECT(rect);
	int prevMode2 = Rectangle(g_handle_off_screenDC, arect.left, arect.top,
		arect.left + arect.right, arect.top + arect.bottom);
	SetROP2(g_handle_off_screenDC, prevMode2);
}