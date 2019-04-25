#pragma once
#include "HeaderManager.h"
#include "LinkedList.h"
#include "FileIO.h"




class ScoreManagementManager
{
	

public:
	ScoreManagementManager();
	~ScoreManagementManager();
	LinkedList<StudentData>* CreateInitialList();
	bool isListEmpty(LinkedList<StudentData>* LL);

	void Init();
};

