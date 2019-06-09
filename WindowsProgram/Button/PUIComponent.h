#pragma once
#include "PSprite.h"

class PUIComponent : public PSprite
{
public:
	PUIComponent();
	~PUIComponent();
public:
	multibyte_string component_name;
	int				index_type;
	PSprite*		owner;
public:
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual PUIComponent* Clone();
	void Add(PUIComponent* component);
	//void Draw() override {};
	void Draw() {};

public:
	PVertex sixteen_vertices[16];
	void SetRect(int rect,
		PVertex start,
		PVertex rightside_vertex,
		PVertex bottomside_vertex,
		int bitmap_id, int mask_id);
	void Generate9PatchImage(FLOAT_RECT my_rect,
		FLOAT_RECT src_rect, int bitmap_id, int mask_id);



	
};

