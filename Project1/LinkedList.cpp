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
	
	node->getData()->SetData(index, const_cast<char*>(name), age, korScore, mathScore);

	return node;

}


void LinkedList::InsertStudentNode(Node* node)
{
	/*���� ���Ḯ��Ʈ���� ���� ���� �����ϴ� �ڵ�*/
	Node* prevNode = tail->getPrev();
	Node* postNode = tail;

	node->SetNextAndPrev(postNode, prevNode);
	prevNode->SetNextAndPrev(node, nullptr);
	postNode->SetNextAndPrev(nullptr, node);
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
	Node* startNode = head->getNext();
	Node* minNode = nullptr;
	for (Node* iterI = startNode; iterI != tail; iterI = iterI->getNext())
	{
		int min = 9999;

		for (Node* iterJ = iterI; iterJ != tail; iterJ = iterJ->getNext())
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

Node* LinkedList::SwapStudent(Node* A, Node* B) //��ȯ������ ���ο� iterI�� �����ؾ� �Ѵ�. iterI�� delete�Ǹ鼭 iterJ�� ���� �ұ� ����.
{//LL
	Node* tempA = new Node;
	Node* tempB = new Node;

	//tempA->data = A->data;
	//tempA->getPrev() = A->getPrev();
	//tempA->getNext() = A->getNext();

	//tempB->data = B->data;
	//tempB->getPrev() = B->getPrev();
	//tempB->getNext() = B->getNext();

	//tempB->getPrev() = A->getPrev();
	//tempB->getNext() = A;
	//A->getPrev()->getNext() = tempB;
	//A->getPrev() = tempB;

	//tempA->getPrev() = B->getPrev();
	//tempA->getNext() = B;
	//B->getPrev()->getNext() = tempA;
	//B->getPrev() = tempA;

	/*tempA = A;
	tempB = B;
		*/
	//�����ε��� ����� �۵����� �ʴ� �� ����

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

void LinkedList::DeleteStudent(Node* node)
{//LL
	Node* prevNode;
	Node* postNode;

	prevNode = node->getPrev();
	postNode = node->getNext();

	if (node)
	{
		delete node;
		node = nullptr;
	}

	prevNode->SetNextAndPrev(postNode, nullptr);
	postNode->SetNextAndPrev(nullptr, prevNode);

	//prevNode->getNext() = postNode;
	//postNode->getPrev() = prevNode;

}

void LinkedList::IndexRearrange()
{
	index = 1;
	Node* iterNode = head->getNext();

	while (iterNode->getNext() != nullptr)
	{
		iterNode->getData()->SetIndex(index);
		
		index++;
		iterNode = iterNode->getNext();
	}

}

void LinkedList::PrintData()
{//LL

	
	printf("��ȣ �̸�   ���� ���� ����\n");


	if (head->getNext() == tail)
	{
		printf("���̺� ������ �����ϴ�");
		_getche();
		return;
	}

	Node* iterNode = head->getNext();

	while (iterNode->getNext() != nullptr)
	{
		printf("%2d %5s %5d %5d %5d\n", iterNode->getData()->getIntInfo("index"), iterNode->getData()->getStringInfo("name"),
			iterNode->getData()->getIntInfo("age"), iterNode->getData()->getIntInfo("korScore"), iterNode->getData()->getIntInfo("mathScore"));
		iterNode = iterNode->getNext();
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



	iterNode = nullptr;
	delete name;
	printf("\nŸ���� �����ϴ�\n ");
	_getche();

}



void LinkedList::SearchDeleteTarget(char* name)
{ //LinkdedList
		Node* iterNode = head->getNext();
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


void LinkedList::WriteSampleData()  //LinkdedList
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

	while (node->getNext() != nullptr)
	{
		nextNode = node->getNext();
		prevNode = node->getPrev();
		printf("%s free\n", node->getData()->getStringInfo("name"));

		delete node;
		node = nextNode;

		prevNode->SetNextAndPrev(node, nullptr);
		node->SetNextAndPrev(nullptr, prevNode);
		//prevNode->getNext() = node;//���� ����� �Ĺ� ����
		//node->getPrev() = prevNode; //���� ����
	}

}

Node* LinkedList::getHead()
{
	return head;
}
Node* LinkedList::getTail()
{
	return tail;
}

void LinkedList::SetHeadAndTail(Node* head_, Node* tail_)
{
	if (head_)
		head = head_;
	if (tail_)
		tail = tail_; 
}


