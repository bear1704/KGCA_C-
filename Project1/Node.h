#pragma once
#include "HeaderManager.h"
#include "StudentData.h"

template<typename T>
class Node
{
	
private:
	T* data;
	NODE* next;
	NODE* prev;

public:
	Node(T*student_, NODE* next_, NODE* prev_);
	Node();
	~Node();
	NODE* getNext();
	NODE* getPrev();
	void SetNextAndPrev(NODE* next_ = nullptr, NODE* prev_ = nullptr);
	T* getData();
	void SetData(T* data_);
	void SetAdressPrevToNext(NODE* source, NODE* target);
	//StudentData** getDataAdr();
	NODE& operator=(const NODE& pt);


};


template <typename T>
NODE::Node(T *student_, NODE* next_, NODE* prev_)
{
	data = student_;
	next = next_;
	prev = prev_;
}

template <typename T>
NODE::Node() : data(new StudentData())
{
	next = nullptr;
	prev = nullptr;
}
template <typename T>
NODE::~Node()
{

}
template <typename T>
NODE * NODE::getNext()
{
	return next;
}
template <typename T>
NODE * NODE::getPrev()
{
	return prev;
}
template <typename T>
void NODE::SetNextAndPrev(NODE * next_, NODE * prev_)
{
	if (next_)
		next = next_;
	if (prev_)
		prev = prev_;


}

template<typename T>
T * NODE::getData()
{
	return data;
}



//StudentData** NODE::getDataAdr()
//{
//	return &data;
//}
template<typename T>
void NODE::SetData(T* data_)
{
	data->SetData(data_->getIntInfo("index"), data_->getStringInfo("name"), data_->getIntInfo("age"),
		data_->getIntInfo("korScore"), data_->getIntInfo("mathScore"));
}
template<typename T>
void NODE::SetAdressPrevToNext(NODE * source, NODE* target)
{
	source->prev->next = target;
}
template<typename T>
NODE& NODE::operator=(const NODE& pt) //사용불가능
{
	next = pt.next;
	prev = pt.prev;
	//*data = *pt.data;

	T* data_ = new StudentData(pt.data->getIntInfo("index"), pt.data->getStringInfo("name"),
		pt.data->getIntInfo("age"), pt.data->getIntInfo("korScore"), pt.data->getIntInfo("mathScore"));

	data = data_;

	std::cout << "operator overloading = " << std::endl;

	return *this;
}



