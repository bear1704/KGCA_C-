#pragma once
#include "PBitmapManager.h"

class PSprite
{
public:
	PSprite();
	~PSprite();

public:
	PBitmap* sprite_;
	vector<RECT> sprite_rectlist_;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	// bool Draw(); //(¿¹Á¤)


};

