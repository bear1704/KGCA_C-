#include <iostream>

constexpr int getArraySize() { return 32; }

int main()
{
	const int n = getArraySize();
	int myarr[n];

	int myarr2[getArraySize()];
}