#pragma once
#include "PCore.h"
#include "PSpriteManager.h"
#include "PSpriteObject.h"

class Sample : public PCore
{
public:
	Sample();
	~Sample();
private:
	PSpriteObject object_sprite;
public:
	bool Init() override;
};

PCORE_RUN(L"abcd", 0, 0, 800, 600);
