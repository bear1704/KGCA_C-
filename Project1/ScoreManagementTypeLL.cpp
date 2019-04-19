/*

연결리스트 정렬기능?

*/

#define SAFE_NEW(A, B) {if (!A) A = new B;}

#define _CRT_SECURE_NO_WARNINGS
//#define TEST
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
	//수정
	//샘플 데이터 추가 
	NONE


};


//보류
void Init();
FILE* CreateLoadFile(FILESTATUS status);
void DeleteStudent();


//패치 필요




void SearchModify(STUDENT* student, LinkedList* LL);

LinkedList* CreateInitialList();
NODE* SearchPastStudentUsingAge(LinkedList* studentLL, const int inputAge);
void PrintData(const LinkedList* studentLL);
void SaveData(LinkedList* studentLL);
LinkedList* LoadData();
NODE* SearchPastStudentUsingNode(const LinkedList* const studentLL, const NODE* inputNode);
//패치됨
NODE* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore);
void InsertStudent(LinkedList* studentLL);
void InsertStudentNode(LinkedList* studentLL, NODE* node /*, int age*/);
void WriteSampleData(LinkedList* studentLL);
void AllFree(NODE* node);
int main()
{
	Init();

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
			SearchModify(student, studentList);
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
	
	NODE* nextNode;
	NODE* prevNode;

	while (node->next != nullptr)
	{
		nextNode = node->next;
		prevNode = node->prev;
		printf("%s free\n", node->data.name);
		free(node);
		node = nextNode;
		
		prevNode->next = node;//이전 노드의 후방 연결
		node->prev = prevNode; //전방 연결



	}
	/*printf("%s free\n", node->data.name);
	free(node);
	node = nullptr;*/
	//이 코드는 Head,Tail이 가상노드가 아닐때 사용

}

LinkedList* CreateInitialList()
{

	LinkedList* studentList = (LinkedList*)malloc(sizeof(LinkedList));
	
	/*Head, Tail 선언*/
	studentList->head = new NODE;
	studentList->tail = new NODE;

	studentList->head->next = studentList->tail; //Head의 다음 노드는 Tail로
	studentList->tail->prev = studentList->head; //Taill의 이전 노드는 head로
	studentList->head->prev = nullptr;
	studentList->tail->next = nullptr;

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

	InsertStudentNode(studentLL, node/*, age*/);

	printf("입력 완료\n");
	_getche();

}
void InsertStudentNode(LinkedList* studentLL, NODE* node /*, int age*/)
{
	/* 단일 연결리스트에서 정렬 후 삽입하는 코드  */
	//if (studentLL->head == nullptr) //깨끗한 LL.
	//{
	//	studentLL->head = node;
	//	studentLL->tail = node;
	//	studentLL->tail->next = nullptr;
	//}
	//else
	//{
	//	NODE* pastNode = SearchPastStudentUsingAge(studentLL, age);
	//	NODE* tempNodeNext;

	//	if (pastNode == nullptr) //제일 처음에 들어가야 할 경우, node를 head로 만들고 head 포인터를 해당 위치로 이동
	//	{
	//		node->next = studentLL->head; //node->next에 현 헤드주소 입력
	//		studentLL->head = node; //새로운 헤드로		
	//	}
	//	else if (pastNode == studentLL->tail) //pastNode가 LL의 제일 끝자락에 있을 경우
	//	{//tail과 pastNode가 같을 경우, next->next == 메모리 침범 (맨끝자리가 pastNode일 경우)
	//		pastNode->next = node;
	//		node->next = nullptr;
	//		studentLL->tail = node;
	//	}
	//	else
	//	{
	//		tempNodeNext = pastNode->next;
	//		pastNode->next = node;
	//		node->next = tempNodeNext;
	//		//연결 끝!
	//	}
	//}

	/*이중 연결리스트에서 정렬 없이 삽입하는 코드*/
	NODE* prevNode = studentLL->tail->prev;
	NODE* postNode = studentLL->tail;

	node->prev = prevNode;
	prevNode->next = node;

	node->next = postNode;
	postNode->prev = node;

}

NODE* SearchPastStudentUsingNode(const LinkedList* const studentLL, const NODE* inputNode)
{
	if (inputNode == studentLL->head) //헤드일 경우, 당연히 pastNode는 없으므로 알려주기 위해 nullptr 리턴
		return nullptr;
	else
	{
		NODE* iterNode = studentLL->head;
		NODE* pastNode = studentLL->head;
		while (iterNode != nullptr)
		{
			if (iterNode == inputNode)
				return pastNode;

			pastNode = iterNode;
			iterNode = iterNode->next;
		}

		return nullptr;

	}


}


NODE* SearchPastStudentUsingAge(LinkedList* studentLL, const int inputAge)
{
	NODE* iterNode = nullptr;
	NODE* pastNode = nullptr; 
	iterNode = studentLL->head;

	
	if (inputAge < iterNode->data.age)
		return nullptr; //head의 age가 제일 처음일 때는 null을 리턴하여 head임을 알린다.


	while (iterNode != nullptr)
	{
		if (inputAge < iterNode->data.age)
			return pastNode;

		pastNode = iterNode;
		iterNode = iterNode->next;
	}

	return pastNode; 

}


void SearchModify(STUDENT* student, LinkedList *LL)
{
	char *name = (char*)malloc(sizeof(char) * 30);
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


	while(iterNode != nullptr)
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

			break;
		}
		iterNode = iterNode->next;
	}



	iterNode = nullptr;
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


		/*	if (studentLL->head == nullptr)
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
			}*/
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
{
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