#include <iostream>
#include "Heap.h"


int main()
{
	Heap heap;

	heap.insert(10);
	heap.insert(30);
	heap.insert(9);
	heap.insert(7);
	heap.insert(5);
	heap.insert(8);
	heap.insert(3);
	heap.display();


	heap.remove(); heap.display();
	heap.remove(); heap.display();
	std::cout << std::endl;

	system("pause");



}