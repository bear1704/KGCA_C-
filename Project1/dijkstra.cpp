#include <iostream>

#ifdef TEST

//노드는 1부터 시작해야 한다.

const int INF = 999;
int** InitArr(int n);
void PrintArr(int** arr, int n);
void PrintArr(int* arr, int n);
void PrintArr(int* arr, char* cArr, int n); void PrintArr(char* arr, int n);
void findRoute(char* S, char* Q, int** arr, int* dist, int n, int shortestNode);
bool isArrEmpty(char* arr, int n);

int main()
{
	int n;
	int start, end, numberOfEdge;
	int currentNode;
	int shortestNode = 999;
	int min = 9999;
	
	std::cout << "노드갯수입력" << std::endl;
	std::cin >> n; //총 노드갯수
	std::cout << "시작노드, 도착노드, 간선개수입력" << std::endl;
	std::cin >> start >> end >> numberOfEdge; //시작노드 ,도착노드 ,간선개수

	int* dist = new int[n+1];

	char* S = new char[n+1]; //S : 이미 방문한 경로
	char* Q = new char[n+1]; //Q : 아직 방문하지 않은 경로
	char* nodeName = new char[n + 1]; //각 노드의 이름
	S[0] = NULL;
	Q[0] = NULL;
	nodeName[0] = NULL;
	int** arr = InitArr(n);

	std::fill(dist, dist + n+1, INF);

	for (int i = 1; i < n + 1; i++)
		Q[i] = 96 + i;
	for (int i = 1; i < n + 1; i++)
		nodeName[i] = 96 + i;

	std::cout << "간선입력 " << std::endl;
	for (int i = 1; i <= numberOfEdge; i++)
	{
		int from, to,  weight;
		std::cin >> from >> to >> weight;
		arr[from][to] = weight;	
	}

	dist[start] = 0; //스타트 노드 거리 초기화(나니까)

	//노드 선택, 선택된 노드와의 거리 탐색
	findRoute(S, Q, arr, dist, n, start); //처음엔 start 노드 탐색
	
	PrintArr(dist,nodeName, n);

	while (!isArrEmpty(Q, n) && shortestNode != end)
	{
		min = 999;

		for (int j = 1; j <= n; j++) //다음꺼 고르는거
		{
			if (Q[j] != NULL && dist[j] < min)
			{
				min = dist[j];
				shortestNode = j;
			}
		}

		findRoute(S, Q, arr, dist, n, shortestNode);
	
		std::cout << "-----거리 현황 ----" << std::endl << std::endl;
		PrintArr(dist,nodeName, n);
		std::cout << "-----Q(아직 안간)----" << std::endl;
		PrintArr(Q,n);
	}

	

	system("pause");
}
void findRoute(char* S, char* Q, int** arr, int* dist, int n, int shortestNode)
{
	int currentNode = shortestNode;

	S[currentNode] = Q[currentNode];
	Q[currentNode] = NULL;

	for (int i = 1; i <= n; i++)
	{
		if ((arr[currentNode][i] + dist[currentNode]) < dist[i])
		{
			dist[i] = arr[currentNode][i] + dist[currentNode];
		}
	}

}

bool isArrEmpty(char* arr, int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (arr[i] != NULL)
			return false;
	}

	return true;
}

int** InitArr(int n)
{

	int** arr = new int*[n+1];

	for (int i = 1; i < n+1; i++)
	{
		arr[i] = new int[n+1];

	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			arr[i][j] = INF;
		}
	}

	return arr;
}

void PrintArr(int** arr, int n)
{

for (int i = 1; i <= n; i++) // 테스트코드
{
	for (int j = 1; j <= n; j++)
	{
		std::cout << arr[i][j] << " ";
	}
	std::cout << std::endl;
}


}

void PrintArr(int* arr, int n)
{
	for (int i = 1; i <= n; i++)
	{
		std::cout << arr[i] << " ";

	}
	std::cout << std::endl;
}
void PrintArr(char* arr, int n)
{
	for (int i = 1; i <= n; i++)
	{
		std::cout << arr[i] << " ";

	}
	std::cout << std::endl;
}

void PrintArr(int* arr,char* cArr, int n)
{
	for (int i = 1; i <= n; i++)
	{
		std::cout << cArr[i] << " ";

	}
	std::cout << std::endl;
	for (int i = 1; i <= n; i++)
	{
		std::cout << arr[i] << " ";

	}
	std::cout << std::endl;
}

#endif