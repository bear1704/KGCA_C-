#pragma once
#include "PRectObject.h"

class PDamage
{
public:
	PDamage();
	~PDamage();
public:
	//void ConvertAndInsertDamage(int damage);
	//void ShowDamage(pPoint position, float scale, float alpha);
	//void set_position_(pPoint pos);
	std::vector<PRectObject*>& get_damage_list_();

private:
	std::vector<PRectObject*> damage_list_;
	pPoint position_;
};

