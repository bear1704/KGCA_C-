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
	

	//std::cout << "소멸됨" << std::endl;
}

void StudentData::SetData(int index_, char * name_, int age_, int korScore_, int mathScore_)
{
	this->index = index_;
	strcpy(name, name_);
	this->age = age_;
	this->korScore = korScore_;
	this->mathScore = mathScore_;
}

int StudentData::getIntInfo(const char * text)
{
	if (strcmp(text, "index") == 0)
		return index;
	else if (strcmp(text, "age") == 0)
		return age;
	else if (strcmp(text, "korScore") == 0)
		return korScore;
	else if (strcmp(text, "mathScore") == 0)
		return mathScore;
	else
	{
		std::cout << "StudentData.h 데이터 스트링 문제" << std::endl;
		abort();
	}
}

char* StudentData::getStringInfo(const char * text)
{
	if (strcmp(text, "name") == 0)
		return name;
	else
	{
		std::cout << "StudentData.h 데이터 스트링 문제" << std::endl;
		abort();
	}
}

void StudentData::SetIndex(int index)
{
	this->index = index;

}


#endif