#include <iostream>
#include <vector>

using namespace std;


struct Node {
	int key;
	int value;

	Node* next;

};

struct HashTable {
	int table_size; //해시테이블의 전체 메모리 크기
	Node** table; //해시테이블 노드로 구성된 일종의 배열
};

void SetHashTable(HashTable* HT, int key, int value);
int GetHashTable(HashTable* HT, int key);
int HashFunction(int key, int table_size);

int main()
{
	HashTable* HT = new HashTable;
	HT->table_size = 100;
	HT->table = new Node*[HT->table_size];

	std::fill(HT->table, HT->table + HT->table_size, nullptr);


	system("pause");
}


void SetHashTable(HashTable* HT, int key, int value)
{

	int address = HashFunction(key, HT->table_size);
	Node* node = new Node();
	node->key = key;   node->value = value;

	if (HT->table[address] == nullptr)
	{
		HT->table[address] = node;
	}
	else
	{
		Node* current_node = HT->table[address];
		node->next = current_node;
		HT->table[address] = node;
		std::cout << "collision occured" << std::endl;
	}
}

int GetHashTable(HashTable* HT, int key)
{
	int address = HashFunction(key, HT->table_size);
	Node* search_node = HT->table[address];

	while (1)
	{
		if (search_node == nullptr)
			return -1;  // -1 : 탐색 실패
		else if (search_node->key != key)
			search_node = search_node->next;
		else
			return search_node->value;
	}
}


int HashFunction(int key, int table_size)
{
	return key % table_size;
}