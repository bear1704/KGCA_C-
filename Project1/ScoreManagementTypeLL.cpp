/*

���Ḯ��Ʈ ���ı��?

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
	//����
	//���� ������ �߰� 
	NONE


};


//����
void Init();
FILE* CreateLoadFile(FILESTATUS status);
void DeleteStudent();


//��ġ �ʿ�




void SearchModify(STUDENT* student, LinkedList* LL);

LinkedList* CreateInitialList();
NODE* SearchPastStudentUsingAge(LinkedList* studentLL, const int inputAge);
void PrintData(const LinkedList* studentLL);
void SaveData(LinkedList* studentLL);
LinkedList* LoadData();
NODE* SearchPastStudentUsingNode(const LinkedList* const studentLL, const NODE* inputNode);
//��ġ��
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
		printf("\n1.����\n2.������ ����\n3.������ ����\n4.������ �˻� �� ����\n5.������ ����\n6.������ �ε�\n7.������ ����\n8.���� ������ ����\n0.����\n");

		scanf("%c", &temp);

		if (isdigit(temp))
			inputData = (SELECT)(temp - '0');
		else
		{
			continue;
		}

		//getchar(); // scanf���������� \n�� �����ϱ� ����

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
		
		prevNode->next = node;//���� ����� �Ĺ� ����
		node->prev = prevNode; //���� ����



	}
	/*printf("%s free\n", node->data.name);
	free(node);
	node = nullptr;*/
	//�� �ڵ�� Head,Tail�� �����尡 �ƴҶ� ���

}

LinkedList* CreateInitialList()
{

	LinkedList* studentList = (LinkedList*)malloc(sizeof(LinkedList));
	
	/*Head, Tail ����*/
	studentList->head = new NODE;
	studentList->tail = new NODE;

	studentList->head->next = studentList->tail; //Head�� ���� ���� Tail��
	studentList->tail->prev = studentList->head; //Taill�� ���� ���� head��
	studentList->head->prev = nullptr;
	studentList->tail->next = nullptr;

	printf("\n���̺��� �����Ǿ����ϴ�\n");

	_getche();

	return studentList;

}


NODE* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore) //index => ���� LL ��忡�� ������ �ε��� (+1�� ��)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	
	node->data.age = age;
	node->data.korScore = korScore;
	node->data.mathScore = mathScore;
	node->data.index = index;
	strcpy(node->data.name, name);
	

	return node;

}

void InsertStudent(LinkedList* studentLL)//student�� �������� parameter�� ���Դ�. func(int a)�� �Լ��� ������ ���� ����������, student�� ��������
{

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
	_getche();

}
void InsertStudentNode(LinkedList* studentLL, NODE* node /*, int age*/)
{
	/* ���� ���Ḯ��Ʈ���� ���� �� �����ϴ� �ڵ�  */
	//if (studentLL->head == nullptr) //������ LL.
	//{
	//	studentLL->head = node;
	//	studentLL->tail = node;
	//	studentLL->tail->next = nullptr;
	//}
	//else
	//{
	//	NODE* pastNode = SearchPastStudentUsingAge(studentLL, age);
	//	NODE* tempNodeNext;

	//	if (pastNode == nullptr) //���� ó���� ���� �� ���, node�� head�� ����� head �����͸� �ش� ��ġ�� �̵�
	//	{
	//		node->next = studentLL->head; //node->next�� �� ����ּ� �Է�
	//		studentLL->head = node; //���ο� ����		
	//	}
	//	else if (pastNode == studentLL->tail) //pastNode�� LL�� ���� ���ڶ��� ���� ���
	//	{//tail�� pastNode�� ���� ���, next->next == �޸� ħ�� (�ǳ��ڸ��� pastNode�� ���)
	//		pastNode->next = node;
	//		node->next = nullptr;
	//		studentLL->tail = node;
	//	}
	//	else
	//	{
	//		tempNodeNext = pastNode->next;
	//		pastNode->next = node;
	//		node->next = tempNodeNext;
	//		//���� ��!
	//	}
	//}

	/*���� ���Ḯ��Ʈ���� ���� ���� �����ϴ� �ڵ�*/
	NODE* prevNode = studentLL->tail->prev;
	NODE* postNode = studentLL->tail;

	node->prev = prevNode;
	prevNode->next = node;

	node->next = postNode;
	postNode->prev = node;

}

NODE* SearchPastStudentUsingNode(const LinkedList* const studentLL, const NODE* inputNode)
{
	if (inputNode == studentLL->head) //����� ���, �翬�� pastNode�� �����Ƿ� �˷��ֱ� ���� nullptr ����
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
		return nullptr; //head�� age�� ���� ó���� ���� null�� �����Ͽ� head���� �˸���.


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


	while(iterNode != nullptr)
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
		if(studentLL->head != nullptr) //Ȥ�� �̹� ������� ��� Ŭ����
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
{

	if (studentLL == nullptr)
	{
		printf("��������\n");
		_getch();
		return;
	}
	printf("��ȣ �̸�   ���� �������� ��������\n");


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
{
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
{
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
{
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
		


		printf("�ε� �Ϸ�\n");
		_getche();
		fclose(fp);

		return newLL;
	}

}


#endif