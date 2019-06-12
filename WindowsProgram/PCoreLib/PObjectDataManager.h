#pragma once
#include "PStd.h"
#include "PWallAndPlatform.h"
#include "PRectObject.h"
#include <assert.h>
//
//struct ObjectInfo
//{
//	multibyte_string object_name_;
//	float move_speed_;
//	FLOAT_RECT collision_box_;
//	float alpha_;
//	float scale_;
//	multibyte_string sprite_path;
//	multibyte_string sprite_name;
//};


class PObjectDataManager : public PSingleton<PObjectDataManager>
{//name(key) movespeed collisionboxsize alpha scale 
public:
	PObjectDataManager();
	~PObjectDataManager();

private:
	friend class PSingleton<PObjectDataManager>;
	std::map<std::wstring, PRectObject*> rectobject_list;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

	PRectObject* get_rectobject_list_from_map(std::wstring key);
	void LoadDataFromScript(multibyte_string filepath);
};

