#include <iostream>
#include <array>
#include <vector>
#include <string>
using namespace std;

#ifdef TEST

int main()
{
	int n;
	
	vector<string> vec{ "first", "second" };

	vec.emplace_back("final");
	vec.push_back(std::string("ffinal"));
	for (auto iter : vec)
	{
		std::cout << " " << iter;
	}
	std::cout << std::endl;
	vec.emplace(std::end(vec), 2, 'A');
	vec.emplace(vec.cbegin() + 2, "ffff");
	for (auto iter : vec)
	{
		std::cout << " " << iter;
	}

	vec.assign(12, "ccc");
	std::cout << std::endl;
	for (auto iter : vec)
	{
		std::cout << " " << iter;
	}

	system("pause");
}

#endif