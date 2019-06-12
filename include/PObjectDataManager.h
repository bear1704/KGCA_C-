#pragma once
#include "PStd.h"
#include "PWallAndPlatform.h"
#include <assert.h>

struct ObjectInfo
{
	multibyte_string object_name_;
	float move_speed_;
	FLOAT_RECT collision_box_;
	float alpha_;
	float scale_;
	multibyte_string sprite_path;
	multibyte_string sprite_name;
};


class PObjectInfoManager : public PSingleton<PObjectInfoManager>
{//name(key) movespeed collisionboxsize alpha scale 
public:
	PObjectInfoManager();
	~PObjectInfoManager();

private:
	friend class PSingleton<PObjectInfoManager>;
	std::map<std::wstring, ObjectInfo*> object_info_list;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

	ObjectInfo* get_object_info_list_from_map(std::wstring key);
	void LoadDataFromScript(multibyte_string filepath);
};

