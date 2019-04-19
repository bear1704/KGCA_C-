#define _CRT_SECURE_NO_WARNINGS
#define TEST
#ifdef TEST


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>



#define OUT_ int*
#define INDEX_ int*

static int index = 1;

typedef struct STUDENT_ {

	int index;
	char name[25];
	int age;
	int korScore;
	int mathScore;

} STUDENT;

typedef struct NODE_ {

	STUDENT data;
	NODE_* next;

} NODE;

typedef struct LL_ {
	NODE* head;
	NODE* tail;
} LinkedList;







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

FILE* CreateLoadFile(FILESTATUS status);

void DeleteStudent();
void SaveData(LinkedList* studentLL);
LinkedList* LoadData();
void PrintData(const LinkedList* studentLL);
void SearchModify(STUDENT* student, const int studentNumber);



/*patches*/
void AllFree(NODE* node);
NODE* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore);
void InsertStudent(LinkedList* studentLL);
void WriteSampleData(LinkedList* studentLL);
LinkedList* CreateInitialList();

int main()
{
	Init();
	//LinkedList* studentList = (LinkedList*)malloc(sizeof(LinkedList));
	//studentList->head = CreateNode(1, "첫째", 10, 10, 10);
	//studentList->tail = studentList->head;
	//studentList->tail->next = CreateNode(2, "둘째", 20, 20, 20);
	//studentList->tail = studentList->tail->next;
	//studentList->tail->next = CreateNode(3, "셋째", 30, 30, 30);
	//studentList->tail = studentList->tail->next;
	//studentList->tail->next = nullptr;

	//AllFree(studentList->head);
	_getche();

	return 0;
}
void Init()
{
	char temp = NULL;
	SELECT inputData = NONE;

	STUDENT* student = NULL;


	/*patch*/
	LinkedList* studentList = nullptr;


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

		switch (inputData)
		{
		case SELECT::CREATE:
			if (studentList)
			{
				free(studentList);
				studentList = nullptr;
			}
			studentList = CreateInitialList();
			break;
		case SELECT::INSERT:
			InsertStudent(studentList);
			break;
		case SELECT::SEARCH_AND_MODIFY:
			//SearchModify(student);
			break;
		case SELECT::SAVE:
			SaveData(studentList);
			break;
		case SELECT::LOAD:
			studentList = LoadData();
			break;
		case SELECT::PRINT:
			PrintData(studentList);
			break;
		case SELECT::SAMPLEDATA:
			WriteSampleData(studentList);
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

void AllFree(NODE* node)
{
	if (node->next != nullptr)
	{
		AllFree(node->next);
	}

	printf("Name : %s  ", node->data.name);
	printf("free 호출\n");
	free(node);
	node = nullptr;
	
}

LinkedList* CreateInitialList()
{

	LinkedList* studentList = (LinkedList*)malloc(sizeof(LinkedList));
	studentList->head = NULL;
	studentList->tail = NULL;

	printf("\n테이블이 생성되었습니다\n");

	_getche();

	return studentList;

}


NODE* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore) //index => 이전 LL 노드에서 가져온 인덱스 (+1할 것)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	
	node->data.age = age;
	node->data.korScore = korScore;
	node->data.mathScore = mathScore;
	node->data.index = index;
	strcpy(node->data.name, name);
	

	return node;

}

void InsertStudent(LinkedList* studentLL)//student는 지역변수 parameter로 들어왔다. func(int a)가 함수가 끝나면 값이 없어지듯이, student도 마찬가지
{
	//중간생성 구현필요
	if (!studentLL)
	{
		printf("학생 테이블을 만드시오\n");
		_getche();
		return;
	}
	
	char name[25];
	int age, kor, math;


	printf("입력 이름 나이 국어 수학\n");
	scanf("%s %d %d %d", name, &age, &kor, &math);

	NODE* node = CreateNode(index, name, age, kor, math); //만들면서 index ++
	(index)++;

	if (studentLL->head == NULL)
	{
		studentLL->head = node;
		studentLL->tail = node;
		studentLL->tail->next = nullptr;
	}
	else
	{
		studentLL->tail->next = node;
		studentLL->tail = studentLL->tail->next;
		studentLL->tail->next = nullptr;
	}

	printf("입력 완료\n");
	_getche();

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

void WriteSampleData(LinkedList* studentLL)
{
	int sampleDataCount;
	char randomName[4];


	if(studentLL != nullptr)
	{
		if(studentLL->head != nullptr) //혹시 이미 만들어진 경우 클리닝
		{
			AllFree(studentLL->head);
			studentLL->head = nullptr;
			studentLL->tail = nullptr;
			index = 1;
		}
		

		printf("샘플 데이터 갯수? -> ");
		scanf("%d", &sampleDataCount);

	

		for (int i = 0; i < sampleDataCount; i++)
		{
			randomName[0] = rand() % 26 + 97;
			randomName[1] = rand() % 26 + 97;
			randomName[2] = rand() % 26 + 97;
			randomName[3] = '\0';

			if (studentLL->head == nullptr)
			{
				studentLL->head = CreateNode(index++, randomName, rand() % 115, rand() % 100, rand() % 100);
				studentLL->tail = studentLL->head;
				studentLL->tail->next = nullptr;
			}
			else
			{
				studentLL->tail->next = CreateNode(index++, randomName, rand() & 115, rand() % 100, rand() % 100);
				studentLL->tail = studentLL->tail->next;
				studentLL->tail->next = nullptr;
			}
		}
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



void PrintData(const LinkedList* studentLL)
{

	if (studentLL == nullptr)
	{
		printf("생성부터\n");
		_getch();
		return;
	}
	printf("번호 이름   나이 국어점수 수학점수\n");


	NODE* iterNode = studentLL->head;

	while (iterNode != nullptr)
	{
		printf("%2d %5s %5d %5d %5d\n", iterNode->data.index, iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);
		iterNode = iterNode->next;
	}
	_getche();
}

FILE* CreateLoadFile(FILESTATUS status)
{
	FILE* fp = NULL;

	if (status == FILESTATUS::LOAD_)
	{
		fp = fopen("student.txt", "r+");
		if (!fp)
			printf("불러올 데이터가 없습니다!\n");
	}


	if (status == FILESTATUS::SAVE_)
	{
		fp = fopen("student.txt", "w+");
	}

	return fp;
}



void SaveData(LinkedList* studentLL)
{
	FILESTATUS status = FILESTATUS::SAVE_;

	FILE *fp = CreateLoadFile(status);

	NODE* iterNode = studentLL->head;

	//fprintf("%d\n", index);
	while (iterNode != nullptr)
	{
		fprintf(fp, "%d %s %d %d %d\n", iterNode->data.index, iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);
		iterNode = iterNode->next;
	}
	fclose(fp);
	printf("저장 완료\n");
	_getche();

}

LinkedList* LoadData()
{
	FILE *fp = CreateLoadFile(FILESTATUS::LOAD_);
	char buffer[20];
	int index, age, kor, math;

	if (!fp)
	{
		_getche();
		return NULL;
	}
	else
	{
		LinkedList* newLL = (LinkedList*)malloc(sizeof(LinkedList));

		NODE* iterNode = (NODE*)malloc(sizeof(NODE));
		newLL->head = iterNode;
		newLL->tail = newLL->head;
		
		fscanf(fp,"%d %s %d %d %d\n", &iterNode->data.index, &iterNode->data.name, &iterNode->data.age, &iterNode->data.korScore, &iterNode->data.mathScore);
		
		
		
		while (!feof(fp))
		{	
			NODE* tailNode = (NODE*)malloc(sizeof(NODE));
			fscanf(fp, "%d %s %d %d %d\n", &tailNode->data.index, &tailNode->data.name, &tailNode->data.age, &tailNode->data.korScore, &tailNode->data.mathScore);

			newLL->tail->next = tailNode;
			newLL->tail = newLL->tail->next;

		
			newLL->tail->next = nullptr;

		}
		


		printf("로드 완료\n");
		_getche();
		fclose(fp);

		return newLL;
	}

}


#endif