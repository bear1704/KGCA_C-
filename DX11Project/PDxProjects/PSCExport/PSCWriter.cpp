#include "pch.h"
#include "PSCWriter.h"

PSCWriter::PSCWriter()
{
}

PSCWriter::~PSCWriter()
{
}

void PSCWriter::Set(const TCHAR* name, Interface* interface_max)
{
	interface_max_ = interface_max;
	filename_ = name;
	rootnode_ = interface_max_->GetRootNode();
	PreProcess(rootnode_);
}

void PSCWriter::PreProcess(INode* node)
{
	if (node == NULL) return;
	AddObject(node);
	int numberof_children = node->NumberOfChildren();
	for (int i = 0; i < numberof_children; i++)
	{
		INode* child = node->GetChildNode(i);
		PreProcess(child);
	}

}

void PSCWriter::AddObject(INode* node)
{
	ObjectState os = node->EvalWorldState(0);

}
