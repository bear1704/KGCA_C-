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
Node<J>* LinkedList<J>::CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore) //index => 이전 LL 노드에서 가져온 인덱스 (+1할 것)
{
	Node<J>* node = new Node<J>;

	node->getData()->SetData(index, const_cast<char*>(name), age, korScore, mathScore);

	return node;

}

template<typename J>
void LinkedList<J>::InsertStudentNode(Node<J>* node)
{
	/*이중 연결리스트에서 정렬 없이 삽입하는 코드*/
	Node<J>* prevNode = tail->getPrev();
	Node<J>* postNode = tail;

	node->SetNextAndPrev(postNode, prevNode);
	prevNode->SetNextAndPrev(node, nullptr);
	postNode->SetNextAndPrev(nullptr, node);
}
template<typename J>
void LinkedList<J>::InsertStudent()//data는 지역변수 parameter로 들어왔다. func(int a)가 함수가 끝나면 값이 없어지듯이, data도 마찬가지
{//LinkedList

	char name[25];
	int age, kor, math;


	printf("입력 이름 나이 국어 수학\n");
	scanf("%s %d %d %d", name, &age, &kor, &math);

	Node<J>* node = CreateNode(index, name, age, kor, math); //만들면서 index ++
	(index)++;

	InsertStudentNode(node);

	printf("입력 완료\n");

	SortData(); //어쩔수 없이 입력 시에도 정렬..
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

		if (iterI != minNode) //최소인 노드와, 현재 스왑해야 할 노드가 같다면 이중해제 문제가 발생함
			iterI = SwapStudent(iterI, minNode);
	}

	IndexRearrange(); //인덱스 재정렬

}
template<typename J>
Node<J>* LinkedList<J>::SwapStudent(Node<J>* A, Node<J>* B) //반환값으로 새로운 iterI를 리턴해야 한다. iterI가 delete되면서 iterJ가 길을 잃기 때문.
{//LL
	Node<J>* tempA = new Node<J>;
	Node<J>* tempB = new Node<J>;

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


	printf("번호 이름   나이 국어 수학\n");


	if (head->getNext() == tail)
	{
		printf("테이블에 내용이 없습니다");
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
	printf("찾을 이름 입력 (0 : 종료)\n");

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


	delete iterNode;
	iterNode = nullptr;
	delete name;
	printf("\n타겟이 없습니다\n ");
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

template<typename J>
void LinkedList<J>::WriteSampleData()  //LinkdedList
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

		Node<J>* node = CreateNode(index++, randomName, rand() % 115 + 1, rand() % 100, rand() % 100);

		InsertStudentNode(node);
	}

	SortData(); //샘플 데이터 정렬(나이별)

	printf("작성 완료 \n");
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

		delete node->getData(); //StudentData 해제
		delete node;
		node = nextNode;

		prevNode->SetNextAndPrev(node, nullptr);
		node->SetNextAndPrev(nullptr, prevNode);
		//prevNode->getNext() = node;//이전 노드의 후방 연결
		//node->getPrev() = prevNode; //전방 연결
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

