#pragma once
#include <iostream>

template <typename T>
class Grid
{
public:
	template<typename E>
	Grid(const Grid<E>& src);
	~Grid() {};

	template<typename E>
	Grid<T>& operator=(const Grid<E>& rhs);

};

template<typename T>
template<typename E>
Grid<T>::Grid(const Grid<E>& src)
{
	//...
}

template <>
class Grid<const char*>
{
public:
	void DeepCopy(const char* elem);
};