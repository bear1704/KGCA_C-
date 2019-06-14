#include "PPlayerStatus.h"



PPlayerStatus::PPlayerStatus()
{
}


PPlayerStatus::~PPlayerStatus()
{
}

void PPlayerStatus::ModifyHP(int hp)
{
	int hp_revised = min(hp, max_hp_);
	hp_revised = max(hp_revised, 0);

	if (abs(past_hp_ - hp_) < 0.1f)
	{
		past_hp_ = hp_;
		hp_ = hp_revised;
	}
	else
	{
		hp_ = hp_revised;
	}
}

void PPlayerStatus::ModifyMP(int mp)
{
	int mp_revised = min(mp, max_mp_);
	mp_revised = max(mp_revised, 0);

	if (abs(past_mp_ - mp_) < 0.1f)
	{
		past_mp_ = mp_;
		mp_ = mp_revised;
	}
	else
	{
		mp_ = mp_revised;
	}
}
void PPlayerStatus::ModifyEXP(int exp)
{
	int exp_revised = min(exp, max_exp_);
	exp_revised = max(exp_revised, 0);

	if (abs(past_exp_ - exp_) < 0.01f)
	{
		past_exp_ = exp_;
		exp_ = exp_revised;
	}
	else
	{
		exp_ = exp_revised;
	}
}
bool PPlayerStatus::Init()
{
	hp_increase_speed_ = 500.0f;
	mp_increase_speed_ = 100.0f;
	exp_increase_speed_ = 500.0f;
	return true;
}

bool PPlayerStatus::Frame()
{
	player_ui_component->Frame();
	return true;
}

bool PPlayerStatus::Render()
{
	float past_hp_rate = past_hp_ / max_hp_;
	float current_hp_rate = hp_ / max_hp_;

	float past_mp_rate = past_mp_ / max_mp_;
	float current_mp_rate = mp_ / max_mp_;

	float past_exp_rate = past_exp_ / max_exp_;
	float current_exp_rate = exp_ / max_exp_;

 	if (past_hp_ > hp_ && abs(past_hp_ - hp_) > 0.1f) //HP
	{
		FLOAT_RECT& hp_rect = hp_image->get_max_rect_size();
		FLOAT_RECT current_guage_rect = { 0,0,0,0 };
		current_guage_rect.right = hp_rect.right * past_hp_rate;
		current_guage_rect.bottom = hp_rect.bottom;
		hp_image->SetRectListSize(current_guage_rect);
		past_hp_ -= hp_increase_speed_ * g_SecondPerFrame;
	}
	else if(past_hp_ < hp_ )
	{
		FLOAT_RECT& hp_rect = hp_image->get_max_rect_size();
		FLOAT_RECT current_guage_rect = { 0,0,0,0 };
		current_guage_rect.right = hp_rect.right * past_hp_rate;
		current_guage_rect.bottom = hp_rect.bottom;
		hp_image->SetRectListSize(current_guage_rect);
		past_hp_ += hp_increase_speed_ * g_SecondPerFrame;
	}
	
	if (past_mp_ > mp_ && abs(past_mp_ - mp_) > 0.1f) //MP
	{
		FLOAT_RECT& mp_rect = mp_image->get_max_rect_size();
		FLOAT_RECT current_guage_rect = { 0,0,0,0 };
		current_guage_rect.right = mp_rect.right * past_mp_rate;
		current_guage_rect.bottom = mp_rect.bottom;
		mp_image->SetRectListSize(current_guage_rect);
		past_mp_ -= mp_increase_speed_ * g_SecondPerFrame;
	}
	else if (past_mp_ < mp_)
	{
		FLOAT_RECT& mp_rect = mp_image->get_max_rect_size();
		FLOAT_RECT current_guage_rect = { 0,0,0,0 };
		current_guage_rect.right = mp_rect.right * past_mp_rate;
		current_guage_rect.bottom = mp_rect.bottom;
		mp_image->SetRectListSize(current_guage_rect);
		past_mp_ += mp_increase_speed_ * g_SecondPerFrame;
	}
	if (past_exp_ > exp_ && abs(past_exp_ - exp_) > 0.01f) //EXP
	{
		FLOAT_RECT& exp_rect = exp_image->get_max_rect_size();
		FLOAT_RECT current_guage_rect = { 0,0,0,0 };
		current_guage_rect.right = exp_rect.right * past_exp_rate;
		current_guage_rect.bottom = exp_rect.bottom;
		exp_image->SetRectListSize(current_guage_rect);
		past_exp_ -= exp_increase_speed_ * g_SecondPerFrame;
	}
	else if (past_exp_ < exp_) //EXP
	{
		FLOAT_RECT& exp_rect = exp_image->get_max_rect_size();
		FLOAT_RECT current_guage_rect = { 0,0,0,0 };
		current_guage_rect.right = exp_rect.right * past_exp_rate;
		current_guage_rect.bottom = exp_rect.bottom;
		exp_image->SetRectListSize(current_guage_rect);
		past_exp_ += exp_increase_speed_ * g_SecondPerFrame;
	}
	
	player_ui_component->Render();

	return true;
}

bool PPlayerStatus::Release()
{
	player_ui_component->Release();
	return true;
}

void PPlayerStatus::StatusSet(multibyte_string status_path, multibyte_string object_name)
{
	PObjectInfoManager::GetInstance().LoadStatusDataFromScript(status_path);
	ObjectStatus* status = PObjectInfoManager::GetInstance().get_object_status_from_map(object_name);

	level_ = status->level_;
	hp_ = status->current_hp_;
	mp_ = status->current_mp_;
	exp_ = status->current_exp_;
	max_hp_ = status->max_hp_;
	max_mp_ = status->max_mp_;
	max_exp_ = status->level_ * 1003;
	str_ = status->str_;
	dex_ = status->dex_;
	atk_ = str_ * 2 + dex_;
	past_hp_ = hp_;
	past_mp_ = mp_;
	past_exp_ = exp_;


	 player_ui_component = PUIDataManager::GetInstance().get_ui_composition_list_from_map(L"ENERGY_GUAGE");
	std::vector<PUIComponent*>& comp_vec = player_ui_component->get_component_list_();


	for (int i = 0; i < comp_vec.size(); i++)
	{
		if (comp_vec[i]->get_object_name().compare(L"hpbar") == 0)
		{
			hp_image = (PImageControl*)comp_vec[i];
			hp_image->set_max_rect_size(comp_vec[i]->get_sprite_()->get_original_size_list()[represent_sprite_number]);
		}
		
		else if (comp_vec[i]->get_object_name().compare(L"mpbar") == 0)
		{
			mp_image = (PImageControl*)comp_vec[i];
			mp_image->set_max_rect_size(comp_vec[i]->get_sprite_()->get_original_size_list()[represent_sprite_number]);
		}
		else if (comp_vec[i]->get_object_name().compare(L"expbar") == 0)
		{
			exp_image = (PImageControl*)comp_vec[i];
			exp_image->set_max_rect_size(comp_vec[i]->get_sprite_()->get_original_size_list()[represent_sprite_number]);
		}
	}

}

int PPlayerStatus::get_level_()
{
	return level_;
}

int PPlayerStatus::get_hp_()
{
	return hp_;
}

int PPlayerStatus::get_mp_()
{
	return mp_;
}

int PPlayerStatus::get_exp_()
{
	return exp_;
}

int PPlayerStatus::get_max_hp()
{
	return max_hp_;
}

int PPlayerStatus::get_max_exp()
{
	return max_exp_;
}

int PPlayerStatus::get_max_mp()
{
	return max_mp_;
}
