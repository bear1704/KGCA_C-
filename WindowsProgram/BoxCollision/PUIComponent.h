#pragma once
#include "PRectObject.h"

class PUIComponent : public PRectObject
{
public:
	PUIComponent();
	virtual ~PUIComponent();
public:
	multibyte_string component_name;
	int				index_type;
	PRectObject* owner;
	std::vector<PUIComponent*> component_list;
public:
	virtual PUIComponent* Clone() { return nullptr; }
	virtual void Draw() {};

public:
	//PVertex sixteen_vertices[16];
	//void SetRect(int rect,
	//	PVertex start,
	//	PVertex rightside_vertex,
	//	PVertex bottomside_vertex,
	//	int bitmap_id, int mask_id);
	//void Generate9PatchImage(FLOAT_RECT my_rect,
	//	FLOAT_RECT src_rect, int bitmap_id, int mask_id);



	
};

