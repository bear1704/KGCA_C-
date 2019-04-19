#include <stdio.h>
#include <stdlib.h>
#ifdef TEST

typedef struct LL {

	struct Node_* head;
	struct Node_* tail;
}LinkedList;

typedef struct Node_ {

	int data;
	struct Node_* next = NULL;
}Node;


void CreateNode(LinkedList* list, int data);
void DeleteTailNode(LinkedList* list);
void DeleteNthNode(LinkedList* list, int n);
void PrintNode(LinkedList* list);
void DeleteIterNextNode(LinkedList* list, Node* iter);
Node* SearchNode(LinkedList* list, int num);




int main()
{
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

	list->head = NULL;
	list->tail = NULL;

	CreateNode(list, 1);
	CreateNode(list, 2);
	CreateNode(list, 3);
	CreateNode(list, 4);
	CreateNode(list, 5); 
	CreateNode(list, 6);
	CreateNode(list, 7);
	CreateNode(list, 8);
	CreateNode(list, 9);
	CreateNode(list, 10);

	int josephCount = 4;
	list->tail->next = list->head; //환형
	
	Node* it = list->head;

	while (it != it->next)
	{
	
		for (int i = 0; i < 2; i++)
		{
			DeleteIterNextNode(list, it);
			it = it->next;
		}
		PrintNode(list);
	}




	getchar();
	


}



void CreateNode(LinkedList* list, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));

	node->data = data;

	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = list->tail->next;
		list->tail->next = NULL;
		
		//list->tail->node;
	}

}

Node* SearchNode(LinkedList* list, int num)
{
	Node* it = list->head;
	int count = num - 1;
	for (int i = 0; i < count; i++)
	{
		it = it->next;
	}
	return it;
}

void DeleteTailNode(LinkedList* list)
{
	Node *it = list->head;

	if (list->head == NULL)
		return;
	
	while (it->next != list->tail)
	{
		it = it->next;
	}

	free(it->next);
	list->tail = it;
	list->tail->next = NULL;

}

void DeleteNthNode(LinkedList* list, int n)
{
	int nodeCount = 1;

	Node *it = list->head;

	if (list->head == NULL)
		return;

	if (n == 1)
	{
		Node* temp = list->head->next;
		free(list->head);
		list->head = temp;
	}
	else
	{
		while (nodeCount < n-1) // 삭제할 노드 전 노드로 가야함
		{
			if (it->next == NULL)
				return;

			it = it->next;
			nodeCount++;
		}
		if (it->next == NULL)
			DeleteTailNode(list);
		else
		{
			Node* temp = it->next->next;
			free(it->next);
			it->next = temp;

			
		}
	}

}

void DeleteIterNextNode(LinkedList* list, Node* iter)
{
	Node* temp = iter->next;
	iter->next = iter->next->next;
	free(temp);

}

void PrintNode(LinkedList* list)
{
	Node* it = list->head;
	Node* headSave = list->head;
	int count = 1;
	printf("%dth Node : %d  ->  ", count, it->data);
	count++;

	while (it->next != NULL)
	{

		if (it->next == headSave)
			return;

		it = it->next;
		printf("%dth Node : %d  ->  ", count, it->data);
		count++;


	}

	
}

#endif