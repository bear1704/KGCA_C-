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
	StudentData();
	~StudentData();



};



#endif