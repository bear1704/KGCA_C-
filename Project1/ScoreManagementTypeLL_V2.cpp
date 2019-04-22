/*
박수찬
*/

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
	NODE_* prev;

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
	NONE


};


//이식중

//이식완료
NODE* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore); //노드 만들기
void Init();
LinkedList* CreateInitialList(); //연결리스트 초기 생성
void InsertStudent(LinkedList* studentLL); //학생 정보 임의 입력
void InsertStudentNode(LinkedList* studentLL, NODE* node /*, int age*/);
void SortData(LinkedList* studentLL); //연결리스트 정렬
NODE* SwapStudent(NODE* A, NODE* B); //A와 B를 스왑
void DeleteStudent(NODE* node);
void IndexRearrange(LinkedList* studentLL); //인덱스 재정렬
void InsertStudentNode(LinkedList* studentLL, NODE* node /*, int age*/);
void SearchModify(LinkedList* LL);
void SearchDeleteTarget(char* name, LinkedList* studentLL); //삭제할 요소를 이름으로 검색
void WriteSampleData(LinkedList* studentLL); //샘플데이터 생성
void AllFree(NODE* node); //데이터 할당 해제
FILE* CreateLoadFile(FILESTATUS status);
void PrintData(const LinkedList* studentLL); //데이터 전부 출력
void SaveData(LinkedList* studentLL); //데이터 세이브
LinkedList* LoadData(); //데이터 로드



//
//int main()
//{
//	Init();
//
//	_getche();
//
//	return 0;
//}



void Init()
{//Manager
	char temp = NULL;
	SELECT inputData = NONE;

	STUDENT* student = NULL;


	/*patch*/
	LinkedList* studentList = nullptr;



	while (inputData != EXIT)
	{
		
		char name[25];

		system("cls");
		printf("\n1.생성\n2.데이터 삽입\n3.데이터 삭제\n4.데이터 검색 및 수정\n5.데이터 저장\n6.데이터 로드\n7.데이터 열람\n8.샘플 데이터 생성\n0.종료\n");

		scanf("%c", &temp);

		if (isdigit(temp))
			inputData = (SELECT)(temp - '0');
		else
		{
			continue;
		}

		switch (inputData)
		{
		case SELECT::CREATE:
			if (studentList)
			{
				delete studentList;
				studentList = nullptr;
			}
			studentList = CreateInitialList();
			break;
		case SELECT::INSERT:
			InsertStudent(studentList);
			break;
		case SELECT::DELETE:
			printf("삭제할 이름 입력 : ");
			scanf("%s", &name);
			SearchDeleteTarget(name, studentList);
			break;
		case SELECT::SEARCH_AND_MODIFY:
			SearchModify(studentList);
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
			delete student;
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
		delete student;
		student = NULL;
	}


}


void AllFree(NODE* node)
{ //LinkedList

	NODE* nextNode;
	NODE* prevNode;

	while (node->next != nullptr)
	{
		nextNode = node->next;
		prevNode = node->prev;
		printf("%s free\n", node->data.name);
		
		delete node;
		node = nextNode;

		prevNode->next = node;//이전 노드의 후방 연결
		node->prev = prevNode; //전방 연결



	}

}

LinkedList* CreateInitialList()
{ // Manager

	LinkedList* studentList = new LinkedList;

	/*Head, Tail 선언*/
	studentList->head = new NODE;
	studentList->tail = new NODE;

	studentList->head->next = studentList->tail; //Head의 다음 노드는 Tail로
	studentList->tail->prev = studentList->head; //Taill의 이전 노드는 head로
	studentList->head->prev = nullptr;
	studentList->tail->next = nullptr;

	index = 1;
	

	printf("\n테이블이 생성되었습니다\n");

	_getche();

	return studentList;

}


NODE* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore) //index => 이전 LL 노드에서 가져온 인덱스 (+1할 것)
{ // LinkedList
	NODE* node = new NODE;

	node->data.age = age;
	node->data.korScore = korScore;
	node->data.mathScore = mathScore;
	node->data.index = index;
	strcpy(node->data.name, name);


	return node;

}

void InsertStudent(LinkedList* studentLL)//student는 지역변수 parameter로 들어왔다. func(int a)가 함수가 끝나면 값이 없어지듯이, student도 마찬가지
{//LinkedList

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

	InsertStudentNode(studentLL, node/*, age*/);

	printf("입력 완료\n");

	SortData(studentLL); //어쩔수 없이 입력 시에도 정렬..
	_getche();

}
void InsertStudentNode(LinkedList* studentLL, NODE* node /*, int age*/)
{//LL?NODE??
	

	/*이중 연결리스트에서 정렬 없이 삽입하는 코드*/
	NODE* prevNode = studentLL->tail->prev;
	NODE* postNode = studentLL->tail;

	node->prev = prevNode;
	prevNode->next = node;

	node->next = postNode;
	postNode->prev = node;

}



void SearchModify(LinkedList *LL) //LinkdedList
{//LL
	char *name = new char[30];
	printf("찾을 이름 입력 (0 : 종료)\n");

	scanf("%s", name);

	if (_stricmp(name, "0") == 0)
		return;

	NODE* iterNode = (NODE*)malloc(sizeof(NODE));

	if (LL == nullptr)
		return;

	iterNode = LL->head;

	if (iterNode == nullptr)
		return;


	while (iterNode != nullptr)
	{
		if (_stricmp(name, iterNode->data.name) == 0)
		{
			printf("이름 나이 국어 수학\n");
			printf("%5s %5d %5d %5d\n", iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);

			printf("\n수정할 이름 : ");
			scanf("%s", &iterNode->data.name);

			printf("\n수정할 나이 : ");
			scanf("%d", &iterNode->data.age);


			printf("\n수정할 국어 점수 : ");
			scanf("%d", &iterNode->data.korScore);


			printf("\n수정할 수학 점수 : ");
			scanf("%d", &iterNode->data.mathScore);

			printf("\n%5s %5d %5d %5d\n", iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);
			printf("\n적용되었습니다\n ");
			
			SortData(LL);
			
			iterNode = nullptr;
			delete name;

			_getche();
			return;
		}
		iterNode = iterNode->next;
	}



	iterNode = nullptr;
	delete name;
	printf("\n타겟이 없습니다\n ");
	_getche();

}

void WriteSampleData(LinkedList* studentLL)  //LinkdedList
{//LL
	int sampleDataCount;
	char randomName[4];


	if (studentLL != nullptr)
	{
		if (studentLL->head != nullptr) //혹시 이미 만들어진 경우 클리닝
		{
			AllFree(studentLL->head->next);

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

			NODE* node = CreateNode(index++, randomName, rand() % 115, rand() % 100, rand() % 100);

			InsertStudentNode(studentLL, node/*, node->data.age*/);
		}

		SortData(studentLL); //샘플 데이터 정렬(나이별)

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
{//LL

	if (studentLL == nullptr)
	{
		printf("생성부터\n");
		_getch();
		return;
	}
	printf("번호 이름   나이 국어 수학\n");


	if (studentLL->head->next == studentLL->tail)
	{ 
		printf("테이블에 내용이 없습니다");
		_getche();
		return;
	}

	NODE* iterNode = studentLL->head->next;

	while (iterNode->next != nullptr)
	{
		printf("%2d %5s %5d %5d %5d\n", iterNode->data.index, iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);
		iterNode = iterNode->next;
	}
	_getche();
}

FILE* CreateLoadFile(FILESTATUS status)
{//IO
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
{//IO
	FILESTATUS status = FILESTATUS::SAVE_;

	FILE *fp = CreateLoadFile(status);

	NODE* iterNode = studentLL->head->next;

	//fprintf("%d\n", index);
	while (iterNode->next != nullptr) //next인 이유는 tail을 계산에서 빼기 위해
	{
		fprintf(fp, "%d %s %d %d %d\n", iterNode->data.index, iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);
		iterNode = iterNode->next;
	}
	fclose(fp);
	printf("저장 완료\n");
	_getche();

}

LinkedList* LoadData()
{//IO
	FILE *fp = CreateLoadFile(FILESTATUS::LOAD_);
	char buffer[20];
	int index, age, kor, math;

	if (!fp)
	{
		printf("파일이 없습니다\n");
		_getche();
		return NULL;
	}
	else
	{
		LinkedList* newLL = new LinkedList;

		newLL->head = new NODE;
		newLL->tail = new NODE;

		newLL->head->next = newLL->tail;
		newLL->tail->prev = newLL->head;

		newLL->head->prev = nullptr;
		newLL->tail->next = nullptr;


		while (!feof(fp))
		{
			NODE* node = new NODE;
			fscanf(fp, "%d %s %d %d %d\n", &node->data.index, &node->data.name, &node->data.age, &node->data.korScore, &node->data.mathScore);

			InsertStudentNode(newLL, node);
		}

		printf("로드 완료\n");
		_getche();
		fclose(fp);
		
		return newLL;
	}

}


void DeleteStudent(NODE* node)
{//LL
	NODE* prevNode;
	NODE* postNode;

	prevNode = node->prev;
	postNode = node->next;

	if (node)
	{
		delete node;
		node = nullptr;
	}

	prevNode->next = postNode;
	postNode->prev = prevNode;

}

void SortData(LinkedList* studentLL)
{//LL
	index = 1;
	NODE* startNode = studentLL->head->next;
	NODE* minNode = nullptr;
	for (NODE* iterI = startNode; iterI != studentLL->tail ;iterI = iterI->next)
	{
		int min = 9999;

		for (NODE* iterJ = iterI; iterJ != studentLL->tail; iterJ = iterJ->next)
		{
			if (iterJ->data.age < min)
			{
				minNode = iterJ;
				min = iterJ->data.age;
			}
		}

		
		if (iterI != minNode) //최소인 노드와, 현재 스왑해야 할 노드가 같다면 이중해제 문제가 발생함
			iterI = SwapStudent(iterI, minNode); 


	}
	
	IndexRearrange(studentLL); //인덱스 재정렬

}

NODE* SwapStudent(NODE* A, NODE* B) //반환값으로 새로운 iterI를 리턴해야 한다. iterI가 delete되면서 iterJ가 길을 잃기 때문.
{//LL
	NODE* tempA = new NODE;
	NODE* tempB = new NODE;

	tempA->data = A->data;
	tempA->prev = A->prev;
	tempA->next = A->next;

	tempB->data = B->data;
	tempB->prev = B->prev;
	tempB->next = B->next;

	tempB->prev = A->prev;
	tempB->next = A;
	A->prev->next = tempB;
	A->prev = tempB;

	tempA->prev = B->prev;
	tempA->next = B;
	B->prev->next = tempA;
	B->prev = tempA;

	DeleteStudent(A);
	DeleteStudent(B);

	return tempB;

}

void SearchDeleteTarget(char* name, LinkedList* studentLL)
{ //LinkdedList
	if (studentLL)
	{
		NODE* iterNode = studentLL->head->next;

		while (iterNode->next != nullptr)
		{
			if (_stricmp(name, iterNode->data.name) == 0)
			{
				DeleteStudent(iterNode);
				printf("삭제되었습니다\n");
				IndexRearrange(studentLL);
				_getch();
				return;
			}
			iterNode = iterNode->next;
			
		}
	}
	printf("타겟이 없습니다\n");
	_getch();
}

void IndexRearrange(LinkedList* studentLL)
{
	index = 1;
	NODE* iterNode = studentLL->head->next;

	while (iterNode->next != nullptr)
	{
		iterNode->data.index = index;
		index++;
		iterNode = iterNode->next;
	}

}

#endif

