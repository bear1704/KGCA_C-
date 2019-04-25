#pragma once
#include "HeaderManager.h"
#include "Node.h"

template<typename T> class Node;

template<typename J>
class LinkedList
{
private:

	Node<J>* head;
	Node<J>* tail;
public:
	static int index;

public:
	LinkedList();
	~LinkedList();
	Node<J>* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore);
	void InsertStudent();
	void InsertStudentNode(Node<J>* node);
	void SortData();
	Node<J>* SwapStudent(Node<J>* A, Node<J>* B);
	void DeleteStudent(Node<J>* node);
	void IndexRearrange();
	void PrintData();
	void SearchModify();
	void SearchDeleteTarget(char* name);
	void WriteSampleData();
	void AllFree(Node<J>* node);
	Node<J>* getHead();
	Node<J>* getTail();
	void SetHeadAndTail(Node<J>* head_ = nullptr, Node<J>* tail_ = nullptr);
	


};


template<typename J>
int LinkedList<J>::index = 1;

template<typename J>
LinkedList<J>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	head = new Node<J>;
	tail = new Node<J>;
}

template<typename J>
LinkedList<J>::~LinkedList()
{

	delete head;
	delete tail;

}

template<typename J>
Node<J>* LinkedList<J>::CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore) //index => ���� LL ��忡�� ������ �ε��� (+1�� ��)
{
	Node<J>* node = new Node<J>;

	node->getData()->SetData(index, const_cast<char*>(name), age, korScore, mathScore);

	return node;

}

template<typename J>
void LinkedList<J>::InsertStudentNode(Node<J>* node)
{
	/*���� ���Ḯ��Ʈ���� ���� ���� �����ϴ� �ڵ�*/
	Node<J>* prevNode = tail->getPrev();
	Node<J>* postNode = tail;

	node->SetNextAndPrev(postNode, prevNode);
	prevNode->SetNextAndPrev(node, nullptr);
	postNode->SetNextAndPrev(nullptr, node);
}
template<typename J>
void LinkedList<J>::InsertStudent()//data�� �������� parameter�� ���Դ�. func(int a)�� �Լ��� ������ ���� ����������, data�� ��������
{//LinkedList

	char name[25];
	int age, kor, math;


	printf("�Է� �̸� ���� ���� ����\n");
	scanf("%s %d %d %d", name, &age, &kor, &math);

	Node<J>* node = CreateNode(index, name, age, kor, math); //����鼭 index ++
	(index)++;

	InsertStudentNode(node);

	printf("�Է� �Ϸ�\n");

	SortData(); //��¿�� ���� �Է� �ÿ��� ����..
	_getche();

}
template<typename J>
void LinkedList<J>::SortData()
{//LL
	index = 1;
	Node<J>* startNode = head->getNext();
	Node<J>* minNode = nullptr;
	for (Node<J>* iterI = startNode; iterI != tail; iterI = iterI->getNext())
	{
		int min = 9999;

		for (Node<J>* iterJ = iterI; iterJ != tail; iterJ = iterJ->getNext())
		{
			if (iterJ->getData()->getIntInfo("age") < min)
			{
				minNode = iterJ;
				min = iterJ->getData()->getIntInfo("age");
			}
		}

		if (iterI != minNode) //�ּ��� ����, ���� �����ؾ� �� ��尡 ���ٸ� �������� ������ �߻���
			iterI = SwapStudent(iterI, minNode);
	}

	IndexRearrange(); //�ε��� ������

}
template<typename J>
Node<J>* LinkedList<J>::SwapStudent(Node<J>* A, Node<J>* B) //��ȯ������ ���ο� iterI�� �����ؾ� �Ѵ�. iterI�� delete�Ǹ鼭 iterJ�� ���� �ұ� ����.
{//LL
	Node<J>* tempA = new Node<J>;
	Node<J>* tempB = new Node<J>;

	tempA->SetData(A->getData());
	tempA->SetNextAndPrev(A->getNext(), A->getPrev());
	tempB->SetData(B->getData());
	tempB->SetNextAndPrev(B->getNext(), B->getPrev()); //�����ε� ��ü 


	tempB->SetNextAndPrev(A, A->getPrev());
	A->SetAdressPrevToNext(A, tempB);
	A->SetNextAndPrev(nullptr, tempB);


	tempA->SetNextAndPrev(B, B->getPrev());
	B->SetAdressPrevToNext(B, tempA);
	B->SetNextAndPrev(nullptr, tempA);

	DeleteStudent(A);
	DeleteStudent(B); //�Ƹ� ���� ���簡 �Ǹ鼭.. IterI�� ���������� �� ������.. �� ������ ����...

	return tempB;

}
template<typename J>
void LinkedList<J>::DeleteStudent(Node<J>* node)
{//LL
	Node<J>* prevNode;
	Node<J>* postNode;

	prevNode = node->getPrev();
	postNode = node->getNext();



	if (node)
	{
		delete node->getData();
		delete node;
		node = nullptr;
	}

	prevNode->SetNextAndPrev(postNode, nullptr);
	postNode->SetNextAndPrev(nullptr, prevNode);

	//prevNode->getNext() = postNode;
	//postNode->getPrev() = prevNode;

}

template<typename J>
void LinkedList<J>::IndexRearrange()
{
	index = 1;
	Node<J>* iterNode = head->getNext();

	while (iterNode->getNext() != nullptr)
	{
		iterNode->getData()->SetIndex(index);

		index++;
		iterNode = iterNode->getNext();
	}

}
template<typename J>
void LinkedList<J>::PrintData()
{//LL


	printf("��ȣ �̸�   ���� ���� ����\n");


	if (head->getNext() == tail)
	{
		printf("���̺� ������ �����ϴ�");
		_getche();
		return;
	}

	Node<J>* iterNode = head->getNext();

	while (iterNode->getNext() != nullptr)
	{
		printf("%2d %5s %5d %5d %5d\n", iterNode->getData()->getIntInfo("index"), iterNode->getData()->getStringInfo("name"),
			iterNode->getData()->getIntInfo("age"), iterNode->getData()->getIntInfo("korScore"), iterNode->getData()->getIntInfo("mathScore"));
		iterNode = iterNode->getNext();
	}
	_getche();
}

template<typename J>
void LinkedList<J>::SearchModify() //LinkdedList
{//LL
	char *name = new char[30];
	printf("ã�� �̸� �Է� (0 : ����)\n");

	scanf("%s", name);

	if (_stricmp(name, "0") == 0)
		return;

	Node<J>* iterNode = new Node<J>;


	iterNode = head;

	if (iterNode == nullptr)
		return;


	while (iterNode != nullptr)
	{
		if (_stricmp(name, iterNode->getData()->getStringInfo("name")) == 0)
		{
			char name[25];
			int age, korScore, mathScore;

			printf("�̸� ���� ���� ����\n");
			printf("%5s %5d %5d %5d\n", iterNode->getData()->getStringInfo("name"), iterNode->getData()->getIntInfo("age"),
				iterNode->getData()->getIntInfo("korScore"), iterNode->getData()->getIntInfo("mathScore"));

			printf("\n������ �̸� : ");
			scanf("%s", &name);

			printf("\n������ ���� : ");
			scanf("%d", &age);

			printf("\n������ ���� ���� : ");
			scanf("%d", &korScore);

			printf("\n������ ���� ���� : ");
			scanf("%d", &mathScore);

			iterNode->getData()->SetData(iterNode->getData()->getIntInfo("index"), name, age, korScore, mathScore);


			printf("\n%5s %5d %5d %5d\n", iterNode->getData()->getStringInfo("name"), iterNode->getData()->getIntInfo("age"),
				iterNode->getData()->getIntInfo("korScore"), iterNode->getData()->getIntInfo("mathScore"));
			printf("\n����Ǿ����ϴ�\n ");

			SortData();

			iterNode = nullptr;
			//delete name;

			_getche();
			return;
		}
		iterNode = iterNode->getNext();
	}


	delete iterNode;
	iterNode = nullptr;
	delete name;
	printf("\nŸ���� �����ϴ�\n ");
	_getche();

}


template<typename J>
void LinkedList<J>::SearchDeleteTarget(char* name)
{ //LinkdedList
	Node<J>* iterNode = head->getNext();
	while (iterNode->getNext() != nullptr)
	{
		if (_stricmp(name, iterNode->getData()->getStringInfo("name")) == 0)
		{
			DeleteStudent(iterNode);
			printf("�����Ǿ����ϴ�\n");
			IndexRearrange();
			_getch();
			return;
		}
		iterNode = iterNode->getNext();

	}

	printf("Ÿ���� �����ϴ�\n");
	_getch();
}

template<typename J>
void LinkedList<J>::WriteSampleData()  //LinkdedList
{//LL
	int sampleDataCount;
	char randomName[4];


	if (head->getNext() != nullptr) //Ȥ�� �̹� ������� ��� Ŭ����
	{
		AllFree(head->getNext());

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

		Node<J>* node = CreateNode(index++, randomName, rand() % 115 + 1, rand() % 100, rand() % 100);

		InsertStudentNode(node);
	}

	SortData(); //���� ������ ����(���̺�)

	printf("�ۼ� �Ϸ� \n");
	_getche();
}
template<typename J>
void LinkedList<J>::AllFree(Node<J>* node)
{ //LinkedList

	Node<J>* nextNode;
	Node<J>* prevNode;

	while (node->getNext() != nullptr)
	{
		nextNode = node->getNext();
		prevNode = node->getPrev();
		printf("%s free\n", node->getData()->getStringInfo("name"));

		delete node->getData(); //StudentData ����
		delete node;
		node = nextNode;

		prevNode->SetNextAndPrev(node, nullptr);
		node->SetNextAndPrev(nullptr, prevNode);
		//prevNode->getNext() = node;//���� ����� �Ĺ� ����
		//node->getPrev() = prevNode; //���� ����
	}

}
template<typename J>
Node<J>* LinkedList<J>::getHead()
{
	return head;
}
template<typename J>
Node<J>* LinkedList<J>::getTail()
{
	return tail;
}
template<typename J>
void LinkedList<J>::SetHeadAndTail(Node<J>* head_, Node<J>* tail_)
{

	if (head_)
		head = head_;
	if (tail_)
		tail = tail_;
}

