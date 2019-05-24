#pragma once
#include "PCore.h"
#include "PRectObject.h"
#include "PStd.h"

class Sample : public PCore
{
	PRectObject object_airplane;
	PRectObject object_background;
public:
	Sample();
	~Sample();
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

};

PCORE_RUN(L"uarrrrrr", 0, 0, 800, 600);