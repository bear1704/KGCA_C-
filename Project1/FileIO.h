#pragma once
#include "HeaderManager.h"
#include "LinkedList.h"

class FileIO
{
private:
	FILE* fp;

public:
	FileIO();
	~FileIO();
	FILE* CreateLoadFile(FILESTATUS status);
	void SaveData(LinkedList* studentList);
	void LoadData(LinkedList** doublePtrList);

};

