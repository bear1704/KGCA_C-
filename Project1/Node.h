#pragma once
#include "HeaderManager.h"
#include "StudentData.h"

template<typename T>
class Node
{
	
private:
	T* data;
	Node<T>* next;
	Node<T>* prev;

public:
	Node(T*student_, Node<T>* next_, Node<T>* prev_);
	Node();
	~Node();
	Node<T>* getNext();
	Node<T>* getPrev();
	void SetNextAndPrev(Node<T>* next_ = nullptr, Node<T>* prev_ = nullptr);
	T* getData();
	void SetData(T* data_);
	void SetAdressPrevToNext(Node<T>* source, Node<T>* target);
};


template <typename T>
Node<T>::Node(T *student_, Node<T>* next_, Node<T>* prev_)
{
	data = student_;
	next = next_;
	prev = prev_;
}

template <typename T>
Node<T>::Node() : data(new StudentData())
{
	next = nullptr;
	prev = nullptr;
}
template <typename T>
Node<T>::~Node()
{

}
template <typename T>
Node<T> * Node<T>::getNext()
{
	return next;
}
template <typename T>
Node<T> * Node<T>::getPrev()
{
	return prev;
}
template <typename T>
void Node<T>::SetNextAndPrev(Node<T> * next_, Node<T> * prev_)
{
	if (next_)
		next = next_;
	if (prev_)
		prev = prev_;


}

template<typename T>
T * Node<T>::getData()
{
	return data;
}



template<typename T>
void Node<T>::SetData(T* data_)
{
	data->SetData(data_->getIntInfo("index"), data_->getStringInfo("name"), data_->getIntInfo("age"),
		data_->getIntInfo("korScore"), data_->getIntInfo("mathScore"));
}


template<typename T>
void Node<T>::SetAdressPrevToNext(Node<T> * source, Node<T>* target)
{
	source->prev->next = target;
}

