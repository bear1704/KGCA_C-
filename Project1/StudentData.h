#pragma once
#include <cstring>
#include <cstdlib>
#include <iostream>
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
	void SetData(int index_, char* name_, int age_, int korScore_, int mathScore_);
	int getIntInfo(const char* text);
	char* getStringInfo(const char* text);
	void SetIndex(int index);

};



#endif