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

	node->data.age = age;
	node->data.korScore = korScore;
	node->data.mathScore = mathScore;
	node->data.index = index;
	strcpy(node->data.name, name);

	return node;

}


void LinkedList::InsertStudentNode(Node* node)
{
	/*이중 연결리스트에서 정렬 없이 삽입하는 코드*/
	Node* prevNode = tail->prev;
	Node* postNode = tail;

	node->prev = prevNode;
	prevNode->next = node;

	node->next = postNode;
	postNode->prev = node;


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


		if (iterI != minNode) //최소인 노드와, 현재 스왑해야 할 노드가 같다면 이중해제 문제가 발생함
			iterI = SwapStudent(iterI, minNode);


	}

	IndexRearrange(); //인덱스 재정렬

}

Node* LinkedList::SwapStudent(Node* A, Node* B) //반환값으로 새로운 iterI를 리턴해야 한다. iterI가 delete되면서 iterJ가 길을 잃기 때문.
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

	
	printf("번호 이름   나이 국어 수학\n");


	if (head->next == tail)
	{
		printf("테이블에 내용이 없습니다");
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
	printf("\n타겟이 없습니다\n ");
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
				printf("삭제되었습니다\n");
				IndexRearrange();
				_getch();
				return;
			}
			iterNode = iterNode->next;

		}

	printf("타겟이 없습니다\n");
	_getch();
}


void LinkedList::WriteSampleData()  //LinkdedList
{//LL
	int sampleDataCount;
	char randomName[4];


		if (head->next != nullptr) //혹시 이미 만들어진 경우 클리닝
		{
			AllFree(head->next);

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