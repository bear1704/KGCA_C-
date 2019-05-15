#pragma once
#include "PBitmap.h"

struct PRectObjectStat
{
	pPoint position;
	RECT rect;
	float moveSpeed;
	PRectObjectStat() {}
	PRectObjectStat(pPoint p, RECT rect_, float moveSpeed_ = 0.0f)
	{
		position = p;
		rect = rect_;
		moveSpeed = moveSpeed;
	}

};

class PRectObject
{
public:
	PRectObject();
	virtual ~PRectObject();
protected:
	PBitmap* bitmap_;
	PBitmap* bitmap_mask_;
	pPoint position_;
	float moveSpeed_;
	RECT rect_;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	virtual void Set(float x, float y, RECT rect, float fSpeed);
	virtual void Set(pPoint p, RECT rect, float fSpeed);
	virtual void Set(PRectObjectStat stat);
	bool Load(std::wstring filename);

};

