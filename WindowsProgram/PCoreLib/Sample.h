#pragma once
#include "PCore.h"
class Sample :
	public PCore
{
public:
	Sample();
	~Sample();
public:
	bool Init();
	bool Frame();
};
PCORE_RUN(L"aaaaaa", 0, 0, 800, 600);
