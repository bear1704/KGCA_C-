#include "LinkedList.h"

int LinkedList::index = 1;

LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	head = new Node;
	tail = new Node;
}


LinkedList::~LinkedList()
{
	delete head;
	delete tail;
}


Node* LinkedList::CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore) //index => ���� LL ��忡�� ������ �ε��� (+1�� ��)
{
	Node* node = new Node;

	node->data.age = age;
	node->data.korScore = korScore;
	node->data.mathScore = mathScore;
	node->data.index = index;
	strcpy(node->data.name, name);

	return node;

}


void LinkedList::InsertStudentNode(Node* node)
{
	/*���� ���Ḯ��Ʈ���� ���� ���� �����ϴ� �ڵ�*/
	Node* prevNode = tail->prev;
	Node* postNode = tail;

	node->prev = prevNode;
	prevNode->next = node;

	node->next = postNode;
	postNode->prev = node;


}

void LinkedList::InsertStudent()//data�� �������� parameter�� ���Դ�. func(int a)�� �Լ��� ������ ���� ����������, data�� ��������
{//LinkedList

	char name[25];
	int age, kor, math;


	printf("�Է� �̸� ���� ���� ����\n");
	scanf("%s %d %d %d", name, &age, &kor, &math);

	Node* node = CreateNode(index, name, age, kor, math); //����鼭 index ++
	(index)++;

	InsertStudentNode(node);

	printf("�Է� �Ϸ�\n");

	SortData(); //��¿�� ���� �Է� �ÿ��� ����..
	_getche();

}

void LinkedList::SortData()
{//LL
	index = 1;
	Node* startNode = head->next;
	Node* minNode = nullptr;
	for (Node* iterI = startNode; iterI != tail; iterI = iterI->next)
	{
		int min = 9999;

		for (Node* iterJ = iterI; iterJ != tail; iterJ = iterJ->next)
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

	IndexRearrange(); //�ε��� ������

}

Node* LinkedList::SwapStudent(Node* A, Node* B) //��ȯ������ ���ο� iterI�� �����ؾ� �Ѵ�. iterI�� delete�Ǹ鼭 iterJ�� ���� �ұ� ����.
{//LL
	Node* tempA = new Node;
	Node* tempB = new Node;

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

void LinkedList::DeleteStudent(Node* node)
{//LL
	Node* prevNode;
	Node* postNode;

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

void LinkedList::IndexRearrange()
{
	index = 1;
	Node* iterNode = head->next;

	while (iterNode->next != nullptr)
	{
		iterNode->data.index = index;
		index++;
		iterNode = iterNode->next;
	}

}

void LinkedList::PrintData()
{//LL

	
	printf("��ȣ �̸�   ���� ���� ����\n");


	if (head->next == tail)
	{
		printf("���̺� ������ �����ϴ�");
		_getche();
		return;
	}

	Node* iterNode = head->next;

	while (iterNode->next != nullptr)
	{
		printf("%2d %5s %5d %5d %5d\n", iterNode->data.index, iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);
		iterNode = iterNode->next;
	}
	_getche();
}


void LinkedList::SearchModify() //LinkdedList
{//LL
	char *name = new char[30];
	printf("ã�� �̸� �Է� (0 : ����)\n");

	scanf("%s", name);

	if (_stricmp(name, "0") == 0)
		return;

	Node* iterNode = new Node;


	iterNode = head;

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

			SortData();

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



void LinkedList::SearchDeleteTarget(char* name)
{ //LinkdedList
		Node* iterNode = head->next;
		while (iterNode->next != nullptr)
		{
			if (_stricmp(name, iterNode->data.name) == 0)
			{
				DeleteStudent(iterNode);
				printf("�����Ǿ����ϴ�\n");
				IndexRearrange();
				_getch();
				return;
			}
			iterNode = iterNode->next;

		}

	printf("Ÿ���� �����ϴ�\n");
	_getch();
}


void LinkedList::WriteSampleData()  //LinkdedList
{//LL
	int sampleDataCount;
	char randomName[4];


		if (head->next != nullptr) //Ȥ�� �̹� ������� ��� Ŭ����
		{
			AllFree(head->next);

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

			Node* node = CreateNode(index++, randomName, rand() % 115 +1, rand() % 100, rand() % 100);

			InsertStudentNode(node);
		}

		SortData(); //���� ������ ����(���̺�)

		printf("�ۼ� �Ϸ� \n");
		_getche();
}

void LinkedList::AllFree(Node* node)
{ //LinkedList

	Node* nextNode;
	Node* prevNode;

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