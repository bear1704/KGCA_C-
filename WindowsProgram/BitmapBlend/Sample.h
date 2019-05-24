#pragma once
#include "PCore.h"
#include "PPlayer.h"
#include "PRectObject.h"
#include "PPlayerController.h"
#include "PBitmap.h"

class Sample : public PCore
{
public:
	Sample();
	~Sample();
protected:
	PRectObject background_object_;
	PPlayer mycharacter_object_;
	

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

};


PCORE_RUN(L"tttt", 0, 0, 800, 600);

