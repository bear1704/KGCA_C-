#pragma once
#include "PImageControl.h"
#include "PUIDataManager.h"


class PPlayerStatus
{
public:
	PPlayerStatus();
	virtual ~PPlayerStatus();
	const float represent_sprite_number = 0;
protected:

	int level_;
	int hp_;
	int mp_;
	int exp_;

	int max_hp_;
	int max_mp_;
	int max_exp_; //level * 1000

	int str_;
	int dex_;
	int atk_;

private:
	float past_hp_;
	float past_mp_;
	float past_exp_;

	float hp_increase_speed_;
	float mp_increase_speed_;
	float exp_increase_speed_;
	PUIComponent* player_ui_component;
	PImageControl* hp_image;
	PImageControl* mp_image;
	PImageControl* exp_image;
	PUIComponent* ui_component;
	FLOAT_RECT max_hp_rect;
	FLOAT_RECT max_mp_rect;
	FLOAT_RECT max_exp_rect;

public:
	void ModifyHP(int hp);
	void ModifyMP(int mp);
	void ModifyEXP(int exp);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	void StatusSet(multibyte_string status_path, multibyte_string object_name);




public:
	int get_level_();
	int get_hp_();
	int get_mp_();
	int get_exp_();
	int get_max_hp();
	int get_max_exp();
	int get_max_mp();
};

