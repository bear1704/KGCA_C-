#pragma once
#include "PCore.h"
#include "PSpriteManager.h"
#include "PRectObject.h"

class Sample : public PCore
{
public:
	Sample();
	~Sample();
private:
	//PSprite sprite1;
	PSprite sprites[30];
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
	
};

 PCORE_RUN(L"abcd", 0, 0, 800, 600);
