#define TEST
#ifdef TEST
#define _CRT_SECURE_NO_WARNINGS
#include "StudentData.h"



StudentData::StudentData(int index, char* name, int age, int korScore, int mathScore)
{
	
	this->index = index;
	strcpy(this->name, name);
	this->age = age;
	this->korScore = korScore;
	this->mathScore = mathScore;
}

StudentData::StudentData()
{

}

StudentData::~StudentData()
{
	

}


#endif