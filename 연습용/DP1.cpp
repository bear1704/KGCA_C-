#ifdef TEST

#include <vector>
#include <iostream>

using namespace std;
#define MIN(a,b) ((a < b) ? (a) : (b))

long long int MapInit(vector<vector<int>>& arr, vector<vector<int>>& puddles, int x, int y)
{


	for (int ii = 0; ii < puddles.size(); ii++)
	{
		arr[puddles[ii][0]][puddles[ii][1]] = 999;
	}

	for (int ii = 0; ii <= x; ii++)
		arr[ii][0] = 0;
	for (int ii = 0; ii <= y; ii++)
		arr[0][ii] = 0;

	arr[1][1] = 1;

	for (int ii = 1; ii <= x; ii++)
	{
		for (int j = 1; j <= y; j++)
		{
			if (ii == 1 && j == 1)
				continue;

			if (arr[ii][j] == 999)
			{
				arr[ii][j] = 0;
				continue;
			}
				
			arr[ii][j] = (arr[ii - 1][j] + arr[ii][j - 1]) % 1000000007;
		}

	}


	return arr[x][y] % 1000000007;
}

int solution(int m, int n, vector<vector<int>> puddles) {

	int& x = m;
	int& y = n;

	vector<vector<int>> arr;
	arr.resize(x + 1);

	for (int ii = 0; ii < arr.size(); ii++)
	{
		arr[ii].resize(y + 1);
	}


	long long int ret = MapInit(arr, puddles, x, y);

	return ret;
}


int main()
{
	long long int x, y;
	x = 4;
	y = 3;
	vector<vector<int>> puddles;
	puddles.reserve(64);
	//puddles.push_back({ 3,2 });
	//puddles.push_back({ 3,3 });
	puddles.push_back({ 2,2 });
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