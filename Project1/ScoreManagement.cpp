#define _CRT_SECURE_NO_WARNINGS
//#define TEST
#ifdef TEST


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>



#define OUT_ int*

typedef struct STUDENT_ {

	char name[25];
	int age;
	int korScore;
	int mathScore;

} STUDENT;



enum FILESTATUS {
	SAVE_,
	LOAD_,
};

enum SELECT {
	EXIT,
	CREATE,
	INSERT,
	DELETE,
	SEARCH_AND_MODIFY,
	SAVE,
	LOAD,
	PRINT,
	SAMPLEDATA,
	//수정
	//샘플 데이터 추가 
	NONE


};

void Init();
STUDENT* CreateStruct(int studentNumber);
STUDENT* CreateInitialData(STUDENT* student, const int* studentNumber);
FILE* CreateLoadFile(FILESTATUS status);
STUDENT* InsertStudent(STUDENT* student, int* studentCapacityCount, int* studentNumber);
void DeleteStudent();
void SaveData(STUDENT* student,const int studentNumber , const int currentCapacity);
STUDENT* LoadData(OUT_ studentNumber, OUT_ studentCapacityCount);
void PrintData(const STUDENT* student, const int studentNumber);
void SearchModify(STUDENT* student, const int studentNumber);
void WriteSampleData(STUDENT* student, const int studentNumber, OUT_ studentCapacityCount);



int main()
{
	Init();

	return 0;
}
void Init()
{
	char temp = NULL;
	SELECT inputData = NONE;

	STUDENT* student = NULL;
	int studentNumber = NULL;
	int studentCapacityCount = 0;

	while (inputData != EXIT)
	{
		system("cls");
		printf("\n1.생성\n2.데이터 삽입\n3.데이터 삭제\n4.데이터 검색 및 수정\n5.데이터 저장\n6.데이터 로드\n7.데이터 열람\n8.샘플 데이터 생성\n0.종료\n");
		

		scanf("%c", &temp);

		if (isdigit(temp))
			inputData = (SELECT)(temp - '0');
		else
		{
			continue;
		}

		//getchar(); // scanf과정에서의 \n을 제거하기 위함

		switch(inputData)
		{
		case SELECT::CREATE:
			printf("\n 학생 수 입력\n");
			scanf("%d", &studentNumber);
			studentCapacityCount = 0;
			
			if (student)
				free(student);

			student = CreateInitialData(student, &studentNumber);
			break;
		case SELECT::INSERT:
			student = InsertStudent(student, &studentCapacityCount, &studentNumber);
			break;
		case SELECT::SEARCH_AND_MODIFY:
			SearchModify(student, studentNumber);
			break;
		case SELECT::SAVE:
			SaveData(student, studentNumber, studentCapacityCount);
			break;
		case SELECT::LOAD:
			student = LoadData(&studentNumber, &studentCapacityCount);
			break;
		case SELECT::PRINT:
			PrintData(student, studentCapacityCount);
			break;
		case SELECT::SAMPLEDATA:
			WriteSampleData(student, studentNumber, &studentCapacityCount);
			break;
		case SELECT::EXIT:
			free(student);
			return;
		default:
			inputData = NONE;
			continue;
			break;
		}

		inputData = NONE;

	}
	 

	if (student)
	{
		free(student);
		student = NULL;
	}

	
}

STUDENT* CreateInitialData(STUDENT* student, const int* studentNumber)
{
	
	student = CreateStruct(*studentNumber);
	printf("\n테이블이 생성되었습니다\n");
	
	_getche();
	return student;
}

STUDENT* CreateStruct(int studentNumber)
{
	STUDENT* student = (STUDENT*)malloc(sizeof(STUDENT) * studentNumber);
	return student;
}

STUDENT* InsertStudent(STUDENT* student, int* studentCapacityCount, int* studentNumber)//student는 지역변수 parameter로 들어왔다. func(int a)가 함수가 끝나면 값이 없어지듯이, student도 마찬가지
{
	if (!student)
	{
		printf("학생 테이블을 만드시오\n");
		_getche();
	}
	else
	{
		char name[25];
		//student capacity 확인
		if (*studentCapacityCount >= *studentNumber)
		{
			printf("저장 공간 확장을 위해 저장/로드를 수행합니다\n");
			SaveData(student, *studentCapacityCount + 5, *studentCapacityCount);
			
			if (student)
			{
				free(student);
				student = NULL;
			}
			
			student = LoadData(studentNumber, studentCapacityCount); //student 변수(지역)은 LoadData로 인해 만들어진 malloc값의 주소를 가지고 있으나, 지역이므로 사라짐
		}
		else
		{
			printf("입력\n이름 나이 국어 수학\n");
			scanf("%s %d %d %d", name, &student[*studentCapacityCount].age, &student[*studentCapacityCount].korScore, &student[*studentCapacityCount].mathScore);
			strcpy(student[*studentCapacityCount].name, name);
			(*studentCapacityCount)++;
		}
	}

	return student;
}


void SearchModify(STUDENT* student, const int studentNumber)
{
	char *name = (char*)malloc(sizeof(char) * 30);
	printf("찾을 이름 입력 (0 : 종료)\n");
	
	scanf("%s", name);

	if (_stricmp(name, "0") == 0)
		return;

	for (int i = 0; i < studentNumber; i++)
	{
		if (_stricmp(name, student[i].name) == 0)
		{
			printf("이름 나이 국어 수학\n");
			printf("%5s %5d %5d %5d\n", student[i].name, student[i].age, student[i].korScore, student[i].mathScore);

			printf("\n수정할 이름 : ");
			scanf("%s", &student[i].name);

			printf("\n수정할 나이 : ");
			scanf("%d", &student[i].age);


			printf("\n수정할 국어 점수 : ");
			scanf("%d", &student[i].korScore);


			printf("\n수정할 수학 점수 : ");
			scanf("%d", &student[i].mathScore);

			printf("\n%5s %5d %5d %5d\n", student[i].name, student[i].age, student[i].korScore, student[i].mathScore);
			printf("\n적용되었습니다\n ");

			break;
		}
	}

	


	free(name);

	_getche();

}

void WriteSampleData(STUDENT* student, const int studentNumber, OUT_ studentCapacityCount)
{
	if (student != NULL)
	{
		for (int i = 0; i < studentNumber; i++)
		{
			student[i].name[0] = rand() % 26 + 97;
			student[i].name[1] = rand() % 26 + 97;
			student[i].name[2] = rand() % 26 + 97;
			student[i].name[3] = '\0';
			student[i].age = rand() % 101 + 1;
			student[i].korScore = rand() % 100;
			student[i].mathScore = rand() % 100;
		}
		*studentCapacityCount = studentNumber;

		printf("작성 완료 \n");
		_getche();
	}
	else
	{
		printf("생성부터 하세요\n");
		_getche();
		return;
	}
}



void PrintData(const STUDENT* student, const int studentCapacity)
{
	printf("번호 이름   나이 국어점수 수학점수\n");
	
	for (int i = 1; i <= studentCapacity; i++)
	{
		printf("%2d %5s %7d %5d %8d\n", i,student[i-1].name ,student[i - 1].age, student[i - 1].korScore, student[i - 1].mathScore);
	}
	_getche();
}

FILE* CreateLoadFile(FILESTATUS status)
{
	FILE* fp = NULL;

	if (status == FILESTATUS::LOAD_)
	{
		fp = fopen("student.txt", "r+");
		if(!fp)
			printf("불러올 데이터가 없습니다!\n");
	}
	

	if (status == FILESTATUS::SAVE_)
	{
		fp = fopen("student.txt", "w+");
	}
	
	return fp;
}

void SaveData(STUDENT* student, const int studentNumber ,const int currentCapacity)
{
	FILESTATUS status = FILESTATUS::SAVE_;

	FILE *fp = CreateLoadFile(status);

	fprintf(fp, "%d %d\n", studentNumber ,currentCapacity); // 데이터 개수
	for (int i = 0; i < currentCapacity; i++)
	{
		fprintf(fp, "%s %d %d %d\n", student[i].name, student[i].age, student[i].korScore, student[i].mathScore);
	}
	fclose(fp);
	printf("저장 완료\n");
	_getche();

}

STUDENT* LoadData(OUT_ studentNumber, OUT_ studentCapacityCount)
{
	FILE *fp = CreateLoadFile(FILESTATUS::LOAD_);


	if (!fp)
	{
		_getche();
		return NULL;
	}
	else
	{
		fscanf(fp, "%d %d\n", studentNumber, studentCapacityCount);
		STUDENT* student = (STUDENT*)malloc(sizeof(STUDENT) * (*studentNumber));

		for (int i = 0; i < *studentCapacityCount ; i++)
		{
			fscanf(fp, "%s %d %d %d\n", &student[i].name, &student[i].age, &student[i].korScore, &student[i].mathScore);
		}

		printf("로드 완료\n");
		_getche();
		fclose(fp);
		return student;
	}

}


#endif