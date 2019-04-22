#pragma once
#include <cstring>
#define TEST
#ifdef TEST
class StudentData
{

public:
	int index;
	char name[25];
	int age;
	int korScore;
	int mathScore;

public:
	StudentData(int index, char* name, int age, int korScore, int mathScore);
	StudentData();
	~StudentData();
};



#endif