#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve);
int main()
{
	std::vector<int> lost{ 1,2 };
	std::vector<int> reserve{2,3};
	
	std::cout << solution(3, lost, reserve);
	system("pause");
}

int solution(int n, vector<int> lost, vector<int> reserve) 
{
	int successRent = 0;
	
	

	for (std::vector<int>::iterator it = lost.begin(); it != lost.end(); )
	{
		std::vector<int>::iterator rent = std::find(reserve.begin(), reserve.end(), *it);

		if (rent != reserve.end())
		{
			reserve.erase(rent);
			it = lost.erase(it); 
		}
		else
		{
			it++;
		}

	}
	
	
	for (int i = 0; i < lost.size(); i++)
	{
		std::vector<int>::iterator prev, next, rentable;  //빌려 줄 수 있는 사람들 모임
		prev = std::find(reserve.begin(), reserve.end(), lost[i]-1);
		
		next = std::find(reserve.begin(), reserve.end(), lost[i]+1);


		if (prev != reserve.end())
			rentable = prev;
		else if (next != reserve.end())
			rentable = next;
		else
			continue;  //못빌려요


		reserve.erase(rentable);
		successRent++;

	}

	return n - lost.size() + successRent;
}