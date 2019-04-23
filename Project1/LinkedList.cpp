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


Node* LinkedList::CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore) //index => 이전 LL 노드에서 가져온 인덱스 (+1할 것)
{
	Node* node = new Node;
	
	node->getData()->SetData(index, const_cast<char*>(name), age, korScore, mathScore);

	return node;

}


void LinkedList::InsertStudentNode(Node* node)
{
	/*이중 연결리스트에서 정렬 없이 삽입하는 코드*/
	Node* prevNode = tail->getPrev();
	Node* postNode = tail;

	node->SetNextAndPrev(postNode, prevNode);
	prevNode->SetNextAndPrev(node, nullptr);
	postNode->SetNextAndPrev(nullptr, node);
}

void LinkedList::InsertStudent()//data는 지역변수 parameter로 들어왔다. func(int a)가 함수가 끝나면 값이 없어지듯이, data도 마찬가지
{//LinkedList

	char name[25];
	int age, kor, math;


	printf("입력 이름 나이 국어 수학\n");
	scanf("%s %d %d %d", name, &age, &kor, &math);

	Node* node = CreateNode(index, name, age, kor, math); //만들면서 index ++
	(index)++;

	InsertStudentNode(node);

	printf("입력 완료\n");

	SortData(); //어쩔수 없이 입력 시에도 정렬..
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

		if (iterI != minNode) //최소인 노드와, 현재 스왑해야 할 노드가 같다면 이중해제 문제가 발생함
			iterI = SwapStudent(iterI, minNode);
	}

	IndexRearrange(); //인덱스 재정렬

}

Node* LinkedList::SwapStudent(Node* A, Node* B) //반환값으로 새로운 iterI를 리턴해야 한다. iterI가 delete되면서 iterJ가 길을 잃기 때문.
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
	//오버로딩이 제대로 작동하지 않는 것 같음

	tempA->SetData(A->getData());
	tempA->SetNextAndPrev(A->getNext(), A->getPrev());
	tempB->SetData(B->getData());
	tempB->SetNextAndPrev(B->getNext(), B->getPrev()); //오버로딩 대체 


	tempB->SetNextAndPrev(A, A->getPrev());
	A->SetAdressPrevToNext(A, tempB);
	A->SetNextAndPrev(nullptr, tempB);
	

	tempA->SetNextAndPrev(B, B->getPrev());
	B->SetAdressPrevToNext(B, tempA);
	B->SetNextAndPrev(nullptr, tempA);

	DeleteStudent(A);
	DeleteStudent(B); //아마 얕은 복사가 되면서.. IterI가 없어져버린 것 같은데.. 왜 그전엔 됐지...

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

	
	printf("번호 이름   나이 국어 수학\n");


	if (head->getNext() == tail)
	{
		printf("테이블에 내용이 없습니다");
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
	printf("찾을 이름 입력 (0 : 종료)\n");

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

			printf("이름 나이 국어 수학\n");
			printf("%5s %5d %5d %5d\n", iterNode->getData()->getStringInfo("name"), iterNode->getData()->getIntInfo("age"),
				iterNode->getData()->getIntInfo("korScore"), iterNode->getData()->getIntInfo("mathScore"));

			printf("\n수정할 이름 : ");
			scanf("%s", &name);

			printf("\n수정할 나이 : ");
			scanf("%d", &age);

			printf("\n수정할 국어 점수 : ");
			scanf("%d", &korScore);

			printf("\n수정할 수학 점수 : ");
			scanf("%d", &mathScore);

			iterNode->getData()->SetData(iterNode->getData()->getIntInfo("index"), name, age, korScore, mathScore);


			printf("\n%5s %5d %5d %5d\n", iterNode->getData()->getStringInfo("name"), iterNode->getData()->getIntInfo("age"), 
				iterNode->getData()->getIntInfo("korScore"), iterNode->getData()->getIntInfo("mathScore"));
			printf("\n적용되었습니다\n ");

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
	printf("\n타겟이 없습니다\n ");
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
				printf("삭제되었습니다\n");
				IndexRearrange();
				_getch();
				return;
			}
			iterNode = iterNode->getNext();

		}

	printf("타겟이 없습니다\n");
	_getch();
}


void LinkedList::WriteSampleData()  //LinkdedList
{//LL
	int sampleDataCount;
	char randomName[4];


		if (head->getNext() != nullptr) //혹시 이미 만들어진 경우 클리닝
		{
			AllFree(head->getNext());

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

			Node* node = CreateNode(index++, randomName, rand() % 115 +1, rand() % 100, rand() % 100);

			InsertStudentNode(node);
		}

		SortData(); //샘플 데이터 정렬(나이별)

		printf("작성 완료 \n");
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
		//prevNode->getNext() = node;//이전 노드의 후방 연결
		//node->getPrev() = prevNode; //전방 연결
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


