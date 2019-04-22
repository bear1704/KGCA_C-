#pragma once
#include "HeaderManager.h"
#include "LinkedList.h"
#include "FileIO.h"




class ScoreManagementManager
{
	

public:
	ScoreManagementManager();
	~ScoreManagementManager();
	LinkedList* CreateInitialList();
	bool isListEmpty(LinkedList* LL);

	void Init();
};

