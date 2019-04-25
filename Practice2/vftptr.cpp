#include <iostream>
using namespace std;

template <typename J, typename C>
class templateClass {

private:
	J* pData;

public:
	J voidF();

};

template <typename T, typename J>
class aaa {



};


class Base {

protected:
	int fff;
public:
	void pa(int a) { fff = a;   std::cout << fff << std::endl; }
	void print() { cout << "i'm base!" << endl; }
};

class Derived : public Base {

private:
	int fff = 22;
public:
	void print() { ///<-¿©±â
		cout << "i'm Derived!" << endl;
		pa(444);
		std::cout << fff << std::endl;
		
	}
};
#define TEST3

#ifdef TEST3

template <typename J>
class LinkedList_J {
public:
	LinkedList_J();
	J<J>* head;
	J<J>* tail;
};

template<typename J>
class TNode_J
{
public:
	TNode_J();
	TNode_J<J>* next;
	TNode_J<J>* prev;
	J* data;
};


int main()
{
	/*LinkedList_J<int>* LL = new LinkedList_J<int>();
	int* node;
	LL->head = node;

	TNode_J<int>* JJ = new TNode_J<int>();
	JJ->next = node;
	*(JJ->data) = 4;
	*/
	LinkedList_J<TNode_J<int>>* LL = new LinkedList_J<TNode_J<int>>();
	TNode_J<int>* aa = new TNode_J<int>();
	LL->head = aa;


	system("pause");
}
#endif
/*		---------		*/

#define TEST2

#ifdef TEST1
template <typename T>
class TNode
{
public:
	T* data;
	T* next;
	T* prev;
};
#endif
#ifdef TEST2
template <typename T>
class TNode
{
public:
	T* data;
	TNode<T>* next;
	TNode<T>* prev;
};
#endif



template <typename T>
class LinkedList
{
public:
	LinkedList();
	TNode<T>* head;
	TNode<T>* tail;
	
};

#ifndef TEST3
int main()
{
	LinkedList<int>* LL = new LinkedList<int>();
	
	TNode<int>* node1 = new TNode<int>();
	TNode<int>* node2 = new TNode<int>();
	TNode<int>* node3 = new TNode<int>();

	LL->head = node1;
	node1->next = node2;

	
	system("pause");
}

#endif

template<typename J>
TNode_J<J>::TNode_J()
{
}
