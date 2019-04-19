#pragma once
#include <cstring>



class StudentData
{

private:
	int index;
	char name[25];
	int age;
	int korScore;
	int mathScore;

public:
	StudentData(int index, char* name, int age, int korScore, int mathScore);
	~StudentData();

	void DataModify(int index, char* name, int age, int koreScore, int mathScore);
	int getIndex();
	char* getName();
	int getAge();
	int getKorScore();
	int getMathScore();

};

