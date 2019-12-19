#ifdef TEST

#include <iostream>
#include <vector>

using namespace std;
#define MIN(a,b) ((a < b) ? (a) : (b))

long long int g_route = 1;
int d = 0;

void MapInit(vector<vector<int>>& arr, vector<vector<int>>& puddles, int x, int y)
{
	arr[0][0] = 0;

	for (int ii = 0; ii < y; ii++)
	{
		for (int jj = 0; jj < x; jj++)
		{
			if(ii > 0 && jj > 0)
				arr[ii][jj] = MIN(arr[ii - 1][jj], arr[ii][jj - 1]) + 1;
			else if (ii > 0)
				arr[ii][jj] = arr[ii - 1][jj] + 1;
			else if(jj > 0)
				arr[ii][jj] = arr[ii][jj - 1] + 1;
		}
	}

	for (int ii = 0; ii < puddles.size(); ii++)
	{
		//0부터 시작하므로 -1해줘야함
		arr[puddles[ii][1] - 1][puddles[ii][0] - 1] = 999;
	}

	arr[y - 1][x - 1] = 999;
}

bool IsDeadPos(vector<vector<int>>& arr, int x, int y)
{

	if (x >= 0 && y <= 0)
	{
		if (arr[y][x - 1] == 999)
			return false;
	}
	else if (x <= 0 && y >= 0)
	{
		if (arr[y - 1][x] == 999)
			return false;
	}
	else if ((arr[y][x - 1] == 0 || arr[y][x - 1] == 999) && (arr[y - 1][x] == 0 || arr[y - 1][x] == 999))
	{
		return false;
	}

	return true;
}

void Traceback(vector<vector<int>>& arr, int x, int y)
{
	//0,0일때
	if (x == 0 && y == 0)
	{
		return;
	}
	
	if (!IsDeadPos(arr, x, y))
	{
		g_route--;
		return;
	}

	if (x > 0 && y > 0)
	{
		//위, 옆이 같을 때
		if (arr[y][x - 1] == arr[y-1][x])
		{
			g_route++;
			Traceback(arr, x - 1, y);
			Traceback(arr, x, y - 1);
		}
		//왼쪽이 작음
		else if (MIN(arr[y][x - 1], arr[y-1][x]) == arr[y][x - 1])
		{
			//gotoleft
			Traceback(arr, x - 1, y);
		}
		//위쪽이 작음
		else
		{
			Traceback(arr, x, y -1);
		}
	}
	else if (x > 0)
	{
		Traceback(arr, x -1, 0);
	}
	else if (y > 0)
	{
		Traceback(arr, 0, y - 1);
	}

	
}

int solution(int m, int n, vector<vector<int>> puddles) {
	
	int& x = m;
	int& y = n;

	vector<vector<int>> arr;
	arr.resize(n);
	
	for (int ii = 0; ii < arr.size(); ii++)
	{
		arr[ii].resize(m);
	}


	MapInit(arr, puddles, x, y);

	Traceback(arr, x - 1, y - 1);//3,3

	
	return g_route % 1000000007;
}


int main()
{
	long long int x, y;
	x = 4;
	y = 3;
	vector<vector<int>> puddles;
	puddles.reserve(64);
	puddles.push_back({ 3,2 });
	puddles.push_back({ 3,3 });
	int ret = solution(4, 3, puddles);
	

#pragma region TEST
	//for (int ii = 0; ii < y; ii++)
	//{
	//	for (int jj = 0; jj < x; jj++)
	//		std::cout << arr[ii][jj] << " ";

	//	std::cout << std::endl;
	//}
#pragma endregion



	
	system("pause");

}


#endif