#include <iostream>

int index = 0;

int Fibonacci(int n)
{
	index++;

	if (n == 0)
		return 0;
	if (n == 1 || n == 2)
		return 1;

	return Fibonacci(n - 1) + Fibonacci(n - 2);
}


int main()
{
	std::cout << Fibonacci(6) << std::endl;
	std::cout << index << std::endl;

	system("pause");

	return 0;
}