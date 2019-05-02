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
	int i = size; //Insert�Ͽ����� Size�� �ϳ� �ø���

	while (i != 1 && key > getParent(i).GetKey()) //��ü Ʈ�� ũ�Ⱑ 1�� �ƴϸ鼭, �ڽ��� Ű�� �θ𺸴� Ŭ ��(�θ�� �ڸ��ٲٱ�)
	{
		//��ü Ʈ�� ũ�Ⱑ 1�� ��, �ڽ��� ��Ʈ�� �ȴٴ� ���̹Ƿ� �� ��Ͽ� ������ �� �ȴ�.

		node[i] = getParent(i); //�θ�� �ڽ��� �ڸ��� �¹ٲ۴�.
		i /= 2; //i�� �θ��� ��ġ��
	}

	//���������� �� �̻� �ö��� �� �ϰų�, �θ��� ũ�Ⱑ �ڽź��� ũ�ٸ� ���� ��ġ�� �ڽ��� ���Ե� ��ġ�̴�.
	node[i].SetKey(key);

}

HeapNode Heap::remove()
{
	if (isEmpty()) return NULL;

	HeapNode item = node[1]; //������ ��Ʈ ���
	HeapNode last = node[size--]; //��ġ ���Ŀ� ����� ������ ���

	int parent = 1; //�� ���� ���� ���
	int child = 2; //�� �ؾ��� �ڽ� ���(����, �������� ���� ����. ����Ʈ�� ����)

	while (child <= size) //Ʈ���� ������ �Ѿ�� �ʴ� �ѿ���
	{
		if (child < size && getLeft(parent).GetKey() < getRight(parent).GetKey())
			child++;   //������ �ڽ� ���ϵ尡, ���� �ڽ� ���ϵ庸�� ũ�ٸ�, ������ �ڽ� ���ϵ�� ��� ��带 ���ؾ� �Ѵ�.
						//�׷��Ƿ� ������ �ִ� child �迭 ��ġ���� 1�� ���Ͽ� ������ �ִ� ���ϵ� ����� �迭 ��ġ������ �ٲ۴�.
						//(���� ��� ������ -1, +1�� ���� �Űܴٴ� �� ����)

		if (last.GetKey() >= node[child].GetKey()) //��� ����� Ű���� ���Ϸ��� ��ǥ �ڽ� ���ϵ庸�� ũ�ٸ�, �űⰡ ��� ���ϵ��� ��ġ�̴�.
			break;

		//�ƴϸ�, 1���� �Ʒ��� �̵��Ѵ�.
		node[parent] = node[child]; //��� ����, �ڱ⺸�� ū �ڽ� ���ϵ��� ���� ����
		parent = child; //��� ��� ���� �� ĭ �Ʒ���
		child *= 2; //��� ����� ���� ���ϵ� ��ġ�� �̵�(parent * 2)

	}

	node[parent] = last; //���� ��ġ�� ����
	return item; //�̾Ƴ��� ��Ʈ ��� ��ȯ

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
