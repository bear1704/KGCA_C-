/*
�ڼ���
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


//�̽���

//�̽ĿϷ�
NODE* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore); //��� �����
void Init();
LinkedList* CreateInitialList(); //���Ḯ��Ʈ �ʱ� ����
void InsertStudent(LinkedList* studentLL); //�л� ���� ���� �Է�
void InsertStudentNode(LinkedList* studentLL, NODE* node /*, int age*/);
void SortData(LinkedList* studentLL); //���Ḯ��Ʈ ����
NODE* SwapStudent(NODE* A, NODE* B); //A�� B�� ����
void DeleteStudent(NODE* node);
void IndexRearrange(LinkedList* studentLL); //�ε��� ������
void InsertStudentNode(LinkedList* studentLL, NODE* node /*, int age*/);
void SearchModify(LinkedList* LL);
void SearchDeleteTarget(char* name, LinkedList* studentLL); //������ ��Ҹ� �̸����� �˻�
void WriteSampleData(LinkedList* studentLL); //���õ����� ����
void AllFree(NODE* node); //������ �Ҵ� ����
FILE* CreateLoadFile(FILESTATUS status);
void PrintData(const LinkedList* studentLL); //������ ���� ���
void SaveData(LinkedList* studentLL); //������ ���̺�
LinkedList* LoadData(); //������ �ε�



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
		printf("\n1.����\n2.������ ����\n3.������ ����\n4.������ �˻� �� ����\n5.������ ����\n6.������ �ε�\n7.������ ����\n8.���� ������ ����\n0.����\n");

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
			printf("������ �̸� �Է� : ");
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

		prevNode->next = node;//���� ����� �Ĺ� ����
		node->prev = prevNode; //���� ����



	}

}

LinkedList* CreateInitialList()
{ // Manager

	LinkedList* studentList = new LinkedList;

	/*Head, Tail ����*/
	studentList->head = new NODE;
	studentList->tail = new NODE;

	studentList->head->next = studentList->tail; //Head�� ���� ���� Tail��
	studentList->tail->prev = studentList->head; //Taill�� ���� ���� head��
	studentList->head->prev = nullptr;
	studentList->tail->next = nullptr;

	index = 1;
	

	printf("\n���̺��� �����Ǿ����ϴ�\n");

	_getche();

	return studentList;

}


NODE* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore) //index => ���� LL ��忡�� ������ �ε��� (+1�� ��)
{ // LinkedList
	NODE* node = new NODE;

	node->data.age = age;
	node->data.korScore = korScore;
	node->data.mathScore = mathScore;
	node->data.index = index;
	strcpy(node->data.name, name);


	return node;

}

void InsertStudent(LinkedList* studentLL)//student�� �������� parameter�� ���Դ�. func(int a)�� �Լ��� ������ ���� ����������, student�� ��������
{//LinkedList

	//�߰����� �����ʿ�
	if (!studentLL)
	{
		printf("�л� ���̺��� ����ÿ�\n");
		_getche();
		return;
	}

	char name[25];
	int age, kor, math;


	printf("�Է� �̸� ���� ���� ����\n");
	scanf("%s %d %d %d", name, &age, &kor, &math);

	NODE* node = CreateNode(index, name, age, kor, math); //����鼭 index ++
	(index)++;

	InsertStudentNode(studentLL, node/*, age*/);

	printf("�Է� �Ϸ�\n");

	SortData(studentLL); //��¿�� ���� �Է� �ÿ��� ����..
	_getche();

}
void InsertStudentNode(LinkedList* studentLL, NODE* node /*, int age*/)
{//LL?NODE??
	

	/*���� ���Ḯ��Ʈ���� ���� ���� �����ϴ� �ڵ�*/
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
	printf("ã�� �̸� �Է� (0 : ����)\n");

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
			printf("�̸� ���� ���� ����\n");
			printf("%5s %5d %5d %5d\n", iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);

			printf("\n������ �̸� : ");
			scanf("%s", &iterNode->data.name);

			printf("\n������ ���� : ");
			scanf("%d", &iterNode->data.age);


			printf("\n������ ���� ���� : ");
			scanf("%d", &iterNode->data.korScore);


			printf("\n������ ���� ���� : ");
			scanf("%d", &iterNode->data.mathScore);

			printf("\n%5s %5d %5d %5d\n", iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);
			printf("\n����Ǿ����ϴ�\n ");
			
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
	printf("\nŸ���� �����ϴ�\n ");
	_getche();

}

void WriteSampleData(LinkedList* studentLL)  //LinkdedList
{//LL
	int sampleDataCount;
	char randomName[4];


	if (studentLL != nullptr)
	{
		if (studentLL->head != nullptr) //Ȥ�� �̹� ������� ��� Ŭ����
		{
			AllFree(studentLL->head->next);

			index = 1;
		}


		printf("���� ������ ����? -> ");
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

		SortData(studentLL); //���� ������ ����(���̺�)

		printf("�ۼ� �Ϸ� \n");
		_getche();
	}
	else
	{
		printf("�������� �ϼ���\n");
		_getche();
		return;
	}
}



void PrintData(const LinkedList* studentLL)
{//LL

	if (studentLL == nullptr)
	{
		printf("��������\n");
		_getch();
		return;
	}
	printf("��ȣ �̸�   ���� ���� ����\n");


	if (studentLL->head->next == studentLL->tail)
	{ 
		printf("���̺� ������ �����ϴ�");
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
			printf("�ҷ��� �����Ͱ� �����ϴ�!\n");
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
	while (iterNode->next != nullptr) //next�� ������ tail�� ��꿡�� ���� ����
	{
		fprintf(fp, "%d %s %d %d %d\n", iterNode->data.index, iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);
		iterNode = iterNode->next;
	}
	fclose(fp);
	printf("���� �Ϸ�\n");
	_getche();

}

LinkedList* LoadData()
{//IO
	FILE *fp = CreateLoadFile(FILESTATUS::LOAD_);
	char buffer[20];
	int index, age, kor, math;

	if (!fp)
	{
		printf("������ �����ϴ�\n");
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

		printf("�ε� �Ϸ�\n");
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

		
		if (iterI != minNode) //�ּ��� ����, ���� �����ؾ� �� ��尡 ���ٸ� �������� ������ �߻���
			iterI = SwapStudent(iterI, minNode); 


	}
	
	IndexRearrange(studentLL); //�ε��� ������

}

NODE* SwapStudent(NODE* A, NODE* B) //��ȯ������ ���ο� iterI�� �����ؾ� �Ѵ�. iterI�� delete�Ǹ鼭 iterJ�� ���� �ұ� ����.
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
				printf("�����Ǿ����ϴ�\n");
				IndexRearrange(studentLL);
				_getch();
				return;
			}
			iterNode = iterNode->next;
			
		}
	}
	printf("Ÿ���� �����ϴ�\n");
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

