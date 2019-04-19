#include <vector>
#include <algorithm>
#include <iostream>


#ifdef TEST
int nCount = 31;

int function(std::vector<int>& Array)
{
	std::vector<int> temp_v1(Array.size());

	for (int i = 0; i < Array.size(); i++)

	{
		temp_v1[i] = Array[i];
	}

	int nTemp = 0;

	static int idx = 0;

	if (Array.size() == 1)
	{

		int abc = Array[0];
		return abc;
	}

	idx += 2;

	nTemp = temp_v1[idx % temp_v1.size()];
	Array.erase(std::find(Array.begin(), Array.end(), nTemp));
	return function(Array);

}



int main()

{
	std::vector<int> v;
	for (int i = 1; i <= nCount; i++)
	{
		v.push_back(i);
	}
	int a = function(v);


	std::cout << a << std::endl;
	std::cout << v[0] << std::endl;

	system("pause");

}

#endif