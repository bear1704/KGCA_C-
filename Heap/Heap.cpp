#include "Heap.h"


Heap::Heap() : size(0)
{
	
}


Heap::~Heap()
{
}

void Heap::insert(int key)
{
	if (isFull())
		return;

	size++;
	int i = size; //Insert하였으니 Size를 하나 올리고

	while (i != 1 && key > getParent(i).GetKey()) //전체 트리 크기가 1이 아니면서, 자신의 키가 부모보다 클 때(부모랑 자리바꾸기)
	{
		//전체 트리 크기가 1일 땐, 자신이 루트가 된다는 뜻이므로 이 블록에 들어오면 안 된다.

		node[i] = getParent(i); //부모와 자신의 자리를 맞바꾼다.
		i /= 2; //i를 부모의 위치로
	}

	//최종적으로 더 이상 올라가지 못 하거나, 부모의 크기가 자신보다 크다면 현재 위치가 자신이 삽입될 위치이다.
	node[i].SetKey(key);

}

HeapNode Heap::remove()
{
	if (isEmpty()) return NULL;

	HeapNode item = node[1]; //리턴할 루트 노드
	HeapNode last = node[size--]; //위치 정렬에 사용할 마지막 노드

	int parent = 1; //비교 중인 현재 노드
	int child = 2; //비교 해야할 자식 노드(왼쪽, 오른쪽은 차후 지정. 디폴트는 왼쪽)

	while (child <= size) //트리의 영역을 넘어서지 않는 한에서
	{
		if (child < size && getLeft(parent).GetKey() < getRight(parent).GetKey())
			child++;   //오른쪽 자식 차일드가, 왼쪽 자식 차일드보다 크다면, 오른쪽 자식 차일드와 대상 노드를 비교해야 한다.
						//그러므로 좌측에 있는 child 배열 위치값에 1을 더하여 우측에 있는 차일드 노드의 배열 위치값으로 바꾼다.
						//(형제 노드 끼리는 -1, +1을 통해 옮겨다닐 수 있음)

		if (last.GetKey() >= node[child].GetKey()) //대상 노드의 키값이 비교하려는 대표 자식 차일드보다 크다면, 거기가 대상 차일드의 위치이다.
			break;

		//아니면, 1레벨 아래로 이동한다.
		node[parent] = node[child]; //대상 노드와, 자기보다 큰 자식 차일드의 값을 스왑
		parent = child; //대상 노드 또한 한 칸 아래로
		child *= 2; //대상 노드의 좌측 차일드 위치로 이동(parent * 2)

	}

	node[parent] = last; //최종 위치에 저장
	return item; //뽑아놨던 루트 노드 반환

}

void Heap::display()
{
	for (int i = 1, level = 1; i <= size; i++)
	{
		if (i == level)
		{
			std::cout << std::endl;
			level *= 2;
		}
		node[i].DisplayKey();
	}
	std::cout << "\n----------------------------";
}
