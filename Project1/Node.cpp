#include "Node.h"



Node::Node(StudentData *student_, Node* next_, Node* prev_)
{
	data = student_;
	next = next_;
	prev = prev_;
}

Node::Node() : data(new StudentData())
{
	//data = new StudentData();
	next = nullptr;
	prev = nullptr;
}

Node::~Node()
{

}

Node * Node::getNext()
{
	return next;
}

Node * Node::getPrev()
{
	return prev;
}

void Node::SetNextAndPrev(Node * next_, Node * prev_)
{
	if (next_)
		next = next_;
	if (prev_)
		prev = prev_;

	
}

StudentData* Node::getData()
{
	return data;
}

void Node::SetData(StudentData* data_)
{
	data->SetData(data_->index, data_->name, data_->age, data_->korScore, data_->mathScore);
}

void Node::SetAdressPrevToNext(Node * source, Node* target)
{
	source->prev->next = target;
}

Node& Node::operator=(const Node & pt)
{
	next = pt.next;
	prev = pt.prev;
	//*data = *pt.data;

	StudentData* data_ = new StudentData(pt.data->getIntInfo("index"), pt.data->getStringInfo("name"),
		pt.data->getIntInfo("age"), pt.data->getIntInfo("korScore"), pt.data->getIntInfo("mathScore"));

	data = data_;

	return *this;
}



