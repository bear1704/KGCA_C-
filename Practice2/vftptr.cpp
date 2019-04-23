#include <iostream>

class A
{
public:
	int n1 = 1;

	void func1() { n1++; }

	virtual void vfunc1() { }
};

class BonA : A
{
public:
	int n2 = 2;

	void func2() { n2++; }

	virtual void vfunc2() { }
};

class ConBonA : BonA
{
public:
	int n3 = 2;

	void func3() { n3++; }

	virtual void vfunc3() { }
};

int main()
{
	ConBonA *table1 = new ConBonA();
	ConBonA *table2 = new ConBonA();

	return 0;
}