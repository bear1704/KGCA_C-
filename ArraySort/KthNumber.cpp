#include <iostream>
#include <vector>
#include <algorithm>

#define ARR_ARGUNUM 4

int Partition(int* arr, int start, int end);
void MyQuickSort(int* arr, int start, int end, int arrSize);
void PrintArr(int* arr, int size);

void MyQuickSort(int* arr, int start, int end, int arrSize)
{
	if (start < end) //i, j�� ��ġ�� ��������
	{
		int pivot = Partition(arr, start, end);
		MyQuickSort(arr, start, pivot - 1, arrSize);
		MyQuickSort(arr, pivot + 1, end, arrSize);
	}

}

int Partition(int* arr, int start, int end)
{
	int pivot, left, right, temp;
	pivot = end;   left = start;    right = end;


	while (left < right) //��ġ�ų�, left�� right�� �Ѵ� ��������
	{
		while (left < right && arr[left] < arr[pivot]) //pivot = 4 ,  arr[left] = 2�� ��Ȳ
			left++;
		while (left < right && arr[right] >= arr[pivot]) //left �̵� ��, �ٽ� üũ�ϰ� right �̵�, right pivot ���´ϱ� pivot������ �̵��ϰ� ������ ��
			right--;

		if (left < right) //i,j ����
		{
			temp = std::move(arr[left]);
			arr[left] = std::move(arr[right]);
			arr[right] = std::move(temp);
		}
		else
		{
			temp = std::move(arr[right]);
			arr[right] = std::move(arr[pivot]);
			arr[pivot] = std::move(temp);
		}

	}

	return right;

}

void PrintArr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << " " << arr[i];
	}
	std::cout << std::endl;
}



int main()
{
	std::vector<int> v{ 1,5,2,6,3,7,4 };
	std::vector<int> c1{ 2,5,3 };
	std::vector<int> c2{ 4,4,1 };
	std::vector<int> c3{ 1,7,3 };
	std::vector<int> answer;

	std::vector<std::vector<int>> commands;
	commands.push_back(c1);
	commands.push_back(c2);
	commands.push_back(c3);



	int arr[100];
	

	

	for (std::vector<int> it : commands)
	{
		int start = it[0] -1; //1~n�� 0~n-1(�迭�� ����� �� �ְ� ��ȯ)
		int end = it[1] -1 ; 
		int k = it[2];
		int size = end - start + 1;  //�迭�� ũ�⸦ ����
		

		std::copy(v.begin() + start, v.begin() + end + 1, arr);
		
		MyQuickSort(arr, 0, size - 1, size);
	
		answer.push_back(arr[k-1]);
	}

	return answer;

}

