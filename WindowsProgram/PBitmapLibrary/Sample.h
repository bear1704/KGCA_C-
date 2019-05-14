#pragma once
#include "pCore.h"
#include "PBitmap.h"
#include "PRectObject.h"
#include "PPlayerController.h"




class Sample : public PCore
{
private:
	PRectObject character_npc_;
	PPlayerController hero_;
	PRectObject object_background_bitmap_;

public:
	Sample();
	~Sample();
public:
	bool Frame();
	bool Init();
	bool Render();
	bool Release();
};
